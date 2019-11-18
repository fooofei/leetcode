package leetcode

import (
	"log"
)

// 139 https://leetcode-cn.com/problems/word-break/

type Node struct {
	C       byte
	Parent  *Node
	NextCnt int
	Next    [0x100]*Node
	Ended   bool
}

type Trie struct {
	Root  *Node
	Chars [0x100]bool
}

func NewTrie() *Trie {
	return &Trie{
		Root: &Node{
			Next: [256]*Node{},
		},
		Chars: [256]bool{},
	}
}

func (t *Trie) insert(words []byte) {
	p := t.Root
	for _, c := range words {
		i := int(c)
		if p.Next[i] == nil {
			q := &Node{
				C:      c,
				Parent: p,
				Next:   [256]*Node{},
			}
			p.Next[i] = q
			p.NextCnt += 1
		}
		p = p.Next[i]
		t.Chars[c] = true
	}
	p.Ended = true
}

func (t *Trie) search(target []byte) bool {
	log.Printf("search %v", len(target))
	ends := make([]int,0)
	p := t.Root
	for idx, c := range target {
		if p.Next[c] == nil {
			break
		}
		p = p.Next[c]
		if p.Ended {
			if idx+1 >= len(target) {
				return true
			}
			ends = append([]int{idx+1}, ends...)
		}
	}
	if len(ends) <=0 {
		return false
	}
	for _,end := range ends {
		if t.search(target[end:]) {
			return true
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
	return t.search(sBytes)
}

// 先放弃，先去学习 AC 自动机了