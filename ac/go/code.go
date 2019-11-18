package main

import (
	"log"
)

type Node struct {
	C       byte
	Parent  *Node
	NextCnt int
	Next    [0x100]*Node
	Fail    *Node
	Off     int // off from root, start from 0
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
	for off, c := range words {
		i := int(c)
		if p.Next[i] == nil {
			q := &Node{
				C:      c,
				Parent: p,
				Next:   [256]*Node{},
				Off:    off,
			}
			p.Next[i] = q
			p.NextCnt += 1
		}
		p = p.Next[i]
		t.Chars[c] = true
	}
	p.Ended = true
}

func (t *Trie) build() {
	root := t.Root
	queue := make([]*Node, 0)
	for _, p := range root.Next {
		if p == nil {
			continue
		}
		p.Fail = root
		queue = append(queue, p)
	}
	for len(queue) > 0 {
		parent := queue[0]
		queue = queue[1:]
		if parent.NextCnt <= 0 {
			continue
		}
		for idx, p := range parent.Next {
			if p == nil {
				continue
			}
			fail := parent.Fail
			for fail != nil {
				if fail.Next[idx] != nil {
					p.Fail = fail.Next[idx]
					break
				}
				fail = fail.Fail
			}
			if fail == nil {
				p.Fail = t.Root
			}
			queue = append(queue, p)
		}
	}
}

// callback for tell matched [first, last)
// callback return true for not continue match
//    return false for continue match
func (t *Trie) search(target []byte, callback func(first int, last int) bool) {
	p := t.Root
	for idx, c := range target {
		for p.Next[c] == nil && p != t.Root {
			p = p.Fail
		}
		if p.Next[c] == nil {
			continue
		}
		p = p.Next[c]
		if p.Ended {
			if callback(idx-p.Off, idx+1) {
				break
			}
		}
	}
}

func ahoCorasick(s string, wordDict []string) bool {
	t := NewTrie()
	for _, str := range wordDict {
		t.insert([]byte(str))
	}
	t.build()
	sBytes := []byte(s)
	matched := false
	t.search(sBytes, func(first int, last int) bool {
		log.Printf("matched at [%v, %v) %v", first, last, string(sBytes[first:last]))
		matched = true
		return false
	})
	return matched
}

func main() {

	ret := ahoCorasick("leetleetcode", []string{
		"leet",
		"code",
	})
	_ = ret
}
