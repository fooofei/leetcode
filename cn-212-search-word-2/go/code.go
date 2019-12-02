package leetcode

// 212 https://leetcode-cn.com/problems/word-search-ii/

// 用不到 AC自动机
// 题意需要反复理解：是从任意点开始向上下左右方向步进

// a-z
const CHILDS_MAX_SIZE = 27

type Node struct {
	C         byte
	Parent    *Node
	NextMap   [CHILDS_MAX_SIZE]*Node
	NextList  []*Node
	Ended     bool
	SubString []byte
}

func addWord(root *Node, word []byte) {
	p := root
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
	p.SubString = append([]byte{}, word...)
}

// 抛弃我自己的没拐弯的解决方案了，原来测试用例是可能拐弯的
// 学习了这里的解决方案 https://leetcode-cn.com/problems/word-search-ii/solution/cqian-zhui-shu-ju-ta-ma-rong-yi-dong-by-chashao/
// 连 Fail 指针都用不上

func traverse(node *Node, board [][]byte, i, j int) []string {
	ret := make([]string, 0)
	if i >= len(board) || i < 0 {
		return ret
	}
	if j >= len(board[0]) || j < 0 {
		return ret
	}
	c := board[i][j]
	idx := c - 'a'
	if node.NextMap[idx] == nil {
		return ret
	}
	node = node.NextMap[idx]
	if node.Ended {
		ret = append(ret, string(node.SubString))
		node.Ended = false // 标记为使用过了，这样不会重复，巧妙啊
	}
	// 错误点：矩阵里的字符不能重复使用
	// 置换为其他字符后，就表示遍历过了
	board[i][j] = '{' // = 'z'+1
	ret1 := traverse(node, board, i, j+1)
	ret = append(ret, ret1...)
	ret1 = traverse(node, board, i, j-1)
	ret = append(ret, ret1...)
	ret1 = traverse(node, board, i+1, j)
	ret = append(ret, ret1...)
	ret1 = traverse(node, board, i-1, j)
	ret = append(ret, ret1...)
	board[i][j] = c
	return ret
}

func findWords(board [][]byte, words []string) []string {
	root := &Node{
		NextMap:  [CHILDS_MAX_SIZE]*Node{},
		NextList: make([]*Node, 0),
	}
	for _, w := range words {
		wbs := []byte(w)
		addWord(root, wbs)
	}
	ret := make([]string, 0)
	for i := 0; i < len(board); i++ {
		for j := 0; j < len(board[i]); j++ {
			ret1 := traverse(root, board, i, j)
			ret = append(ret, ret1...)
		}
	}
	return ret
}
