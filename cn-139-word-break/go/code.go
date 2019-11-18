package leetcode

// 139 https://leetcode-cn.com/problems/word-break/

type Node struct {
	C        byte
	Parent   *Node
	NextList []*Node
	NextMap  [0x100]*Node
	Ended    bool
}

type Trie struct {
	Root  *Node
	Chars [0x100]bool
}

func NewTrie() *Trie {
	return &Trie{
		Root: &Node{
			NextMap:  [256]*Node{},
			NextList: make([]*Node, 0),
		},
		Chars: [256]bool{},
	}
}

func (t *Trie) insert(words []byte) {
	p := t.Root
	for _, c := range words {
		i := int(c)
		if p.NextMap[i] == nil {
			q := &Node{
				C:        c,
				Parent:   p,
				NextMap:  [256]*Node{},
				NextList: make([]*Node, 0),
			}
			p.NextMap[i] = q
			p.NextList = append(p.NextList, q)
		}
		p = p.NextMap[i]
		t.Chars[c] = true
	}
	p.Ended = true
}

func (t *Trie) search(target []byte, endsCache []int, first int, last int) bool {
	if endsCache[first] == 1 {
		return true
	} else if endsCache[first] == -1 {
		return false
	}
	starts := make([]int, 0)
	p := t.Root
	for idx := first; idx < last; idx += 1 {
		c := target[idx]
		if p.NextMap[c] == nil {
			break
		}
		p = p.NextMap[c]
		if p.Ended {
			if idx+1 >= last {
				return true
			}
			starts = append([]int{idx + 1}, starts...)
		}
	}
	if len(starts) <= 0 {
		return false
	}
	for _, start := range starts {
		ret := t.search(target, endsCache, start, last)
		if ret {
			endsCache[start] = 1
			return true
		} else {
			endsCache[start] = -1
		}
	}
	return false
}

// Test4 Test5 Time too long
func wordBreak(s string, wordDict []string) bool {
	t := NewTrie()
	for _, str := range wordDict {
		t.insert([]byte(str))
	}
	sBytes := []byte(s)
	for _, c := range sBytes {
		if !t.Chars[c] {
			return false
		}
	}
	// 因为是试探尾巴，防止尾巴重复计算
	// 缓存 [x, last) 是否构成单词的结果
	endsCache := make([]int, len(sBytes))
	return t.search(sBytes, endsCache, 0, len(sBytes))
}
