package leetcode

// 212 https://leetcode-cn.com/problems/word-search-ii/

// a-z
const CHILDS_MAX_SIZE = 27

type Node struct {
	C        byte
	Parent   *Node
	NextMap  [CHILDS_MAX_SIZE]*Node
	NextList []*Node
	Fail     *Node
	Ended    bool
}

type Trie struct {
	Root   *Node
	StrCnt int
}

func reverse(s []byte) []byte {
	if len(s) < 2 {
		return s
	}
	i := 0
	j := len(s) - 1
	for i < j {
		s[i], s[j] = s[j], s[i]
		i++
		j--
	}
	return s
}

func (t *Trie) add(word []byte) {
	p := t.Root
	for _, c := range word {
		idx := c - 'a'
		if p.NextMap[idx] == nil {
			q := &Node{
				C:        c,
				Parent:   p,
				NextMap:  [CHILDS_MAX_SIZE]*Node{},
				NextList: make([]*Node, 0),
			}
			p.NextMap[idx] = q
			p.NextList = append(p.NextList, q)
		}
		p = p.NextMap[idx]
	}
	p.Ended = true
	t.StrCnt += 1
}

func (t *Trie) build() {
	queue := make([]*Node, 0)
	root := t.Root
	for _, n := range root.NextList {
		n.Fail = root
		queue = append(queue, n)
	}
	for len(queue) > 0 {
		parent := queue[0]
		queue = queue[1:]
		for _, p := range parent.NextList {
			fail := parent.Fail
			idx := p.C - 'a'
			for fail != nil {
				if fail.NextMap[idx] != nil {
					p.Fail = fail.NextMap[idx]
					break
				}
				fail = fail.Fail
			}
			if fail == nil {
				p.Fail = root
			}
			queue = append(queue, p)
		}
	}
}

func traverse(root *Node, node *Node, board [][]byte, i, j int, visited [][]bool) []string {
	ret := make([]string, 0)
	if node.Ended {
		n := node
		s := make([]byte, 0)
		for n != root {
			s = append(s, n.C)
			n = n.Parent
		}
		ret = append(ret, string(reverse(s)))
	}
	if i >= len(board) {
		return ret
	}
	if j >= len(board[0]) {
		return ret
	}
	c := board[i][j]
	idx := c - 'a'
	for node.NextMap[idx] == nil && node != root {
		node = node.Fail
	}
	if node == root {
		if visited[i][j] {
			return ret
		}
		visited[i][j] = true
	}
	node = node.NextMap[idx]
	if node == nil {
		node = root
	}
	ret1 := traverse(root, node, board, i, j+1, visited)
	ret = append(ret, ret1...)
	ret2 := traverse(root, node, board, i+1, j, visited)
	ret = append(ret, ret2...)
	return ret
}

func findWords(board [][]byte, words []string) []string {
	trie := &Trie{
		Root: &Node{
			NextMap:  [CHILDS_MAX_SIZE]*Node{},
			NextList: make([]*Node, 0),
		},
	}
	for _, w := range words {
		wbs := []byte(w)
		trie.add(wbs)
		trie.add(reverse(wbs))
	}
	trie.build()
	// 以某点为起始点 是否查询过
	visited := make([][]bool, len(board))
	for i := range visited {
		visited[i] = make([]bool, len(board[0]))
	}
	return traverse(trie.Root, trie.Root, board, 0, 0, visited)
}
