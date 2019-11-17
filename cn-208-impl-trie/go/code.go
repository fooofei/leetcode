package leetcode

// 208 https://leetcode-cn.com/problems/implement-trie-prefix-tree/

// a-z
const CHILDS_MAX_SIZE = 27

type Node struct {
	C       byte
	Parent  *Node
	Next    [CHILDS_MAX_SIZE]*Node
	NextCnt int
	Ended   bool
}

type Trie struct {
	Root   *Node
	StrCnt int
}

/** Initialize your data structure here. */
func Constructor() Trie {
	return Trie{
		Root: &Node{
			Next: [CHILDS_MAX_SIZE]*Node{},
		},
	}
}

/** Inserts a word into the trie. */
func (this *Trie) Insert(word string) {
	words := []byte(word)
	p := this.Root
	for _, c := range words {
		i := c - 'a'
		if p.Next[int(i)] == nil {
			q := &Node{
				C:      c,
				Parent: p,
				Next:   [CHILDS_MAX_SIZE]*Node{},
			}
			p.Next[int(i)] = q
			p.NextCnt += 1
		}
		p = p.Next[int(i)]
	}
	p.Ended = true
	this.StrCnt += 1
}

/** Returns if the word is in the trie. */
func (this *Trie) Search(word string) bool {
	words := []byte(word)
	if len(words) <= 0 {
		return false
	}
	if this.StrCnt <= 0 {
		return false
	}
	i := words[0] - 'a'
	if this.Root.Next[i] == nil {
		return false
	}

	p := this.Root
	for _, c := range words {
		i := c - 'a'
		if p == nil {
			return false
		}
		p = p.Next[i]
	}
	if p == nil {
		return false
	}
	return p.Ended
}

/** Returns if there is any word in the trie that starts with the given prefix. */
func (this *Trie) StartsWith(prefix string) bool {
	words := []byte(prefix)
	if len(words) <= 0 {
		return true
	}
	if this.StrCnt <= 0 {
		return false
	}
	i := words[0] - 'a'
	if this.Root.Next[i] == nil {
		return false
	}

	p := this.Root
	for _, c := range words {
		i := c - 'a'
		if p == nil {
			return false
		}
		p = p.Next[i]
	}
	return p != nil
}

/**
 * Your Trie object will be instantiated and called as such:
 * obj := Constructor();
 * obj.Insert(word);
 * param_2 := obj.Search(word);
 * param_3 := obj.StartsWith(prefix);
 */
