package leetcode

// 211 https://leetcode-cn.com/problems/add-and-search-word-data-structure-design/

// a-z
const CHILDS_MAX_SIZE = 27

type Node struct {
	C        byte
	Parent   *Node
	NextMap  [CHILDS_MAX_SIZE]*Node
	NextList []*Node
	Ended    bool
}

type WordDictionary struct {
	Root   *Node
	StrCnt int
}

/** Initialize your data structure here. */
func Constructor() WordDictionary {
	return WordDictionary{
		Root: &Node{
			NextMap:  [CHILDS_MAX_SIZE]*Node{},
			NextList: make([]*Node, 0),
		},
	}
}

/** Adds a word into the data structure. */
func (this *WordDictionary) AddWord(word string) {
	words := []byte(word)

	p := this.Root
	for _, c := range words {
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
}

func dotSelectChild(node *Node, words []byte) bool {
	for _, p := range node.NextList {
		if searchAt(p, words) {
			return true
		}
	}
	return false
}

func searchAt(node *Node, words []byte) bool {
	if node.Ended {
		return len(words) == 0
	}
	for i, c := range words {
		idx := c - 'a'
		if c == '.' {
			if len(node.NextList) == 1 {
				node = node.NextList[0]
			} else {
				return dotSelectChild(node, words[i+1:])
			}
		} else if node.NextMap[idx] == nil {
			return false
		} else {
			node = node.NextMap[idx]
		}
	}
	return node.Ended
}

/** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
func (this *WordDictionary) Search(word string) bool {
	return searchAt(this.Root, []byte(word))
}
