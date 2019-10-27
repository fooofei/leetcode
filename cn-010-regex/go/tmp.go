package main

import (
	"fmt"
	"strings"
)

// 来自 https://leetcode-cn.com/problems/regular-expression-matching/solution/yi-bu-dao-wei-zhi-jie-an-zheng-ze-biao-da-shi-de-s/
// 没有好感 没继续研究

func debug(v ...interface{}) {
	//log.Println(v...)
}

func toString(i interface{}) string {
	switch i.(type) {
	case int:
		return fmt.Sprintf("%v", i)
	case string:
		return fmt.Sprintf("%v", i)
	case bool:
		return fmt.Sprintf("%v", i)
	default:
		return fmt.Sprintf("%p", i)
	}
}

func isMatch(s string, p string) bool {
	begin := new(Node)
	begin.C = '>'
	begin.Size = generatePattern(begin, p)
	debug(begin.String())
	return check(begin, s, 0)
}

type Node struct {
	C        byte
	Parent   *Node
	Children map[byte][]*Node
	End      bool
	Size     int
}

func (n *Node) String() string {
	return n.StringLevel(0, make(map[*Node]bool))
}

func (n *Node) StringLevel(level int, finishNodes map[*Node]bool) string {
	r := make([]string, 0)
	if n.End {
		r = append(r, fmt.Sprintf("  id%s{%v};", toString(n), string(n.C)))
	} else {
		r = append(r, fmt.Sprintf("  id%s(%v);", toString(n), string(n.C)))
	}
	finishNodes[n] = true
	for k, v := range n.Children {
		for _, c := range v {
			if _, ok := finishNodes[c]; !ok {
				r = append(r, c.StringLevel(level+1, finishNodes))
			}
			r = append(r, fmt.Sprintf("  id%s -- %s --> id%s;", toString(n), string(k), toString(c)))
		}
	}
	return strings.Join(r, "\n")
}

func (n *Node) Append(child *Node) {
	m := n.Children
	if m == nil {
		m = make(map[byte][]*Node)
		n.Children = m
	}
	list := m[child.C]
	if list == nil {
		list = make([]*Node, 0)
	}
	for _, v := range list {
		if v == child {
			return
		}
	}
	list = append(list, child)
	m[child.C] = list
}

func generatePattern(parent *Node, str string) int {
	if len(str) <= 0 {
		parent.End = true
		return parent.Size
	}
	vnow := parent
	switch str[0] {
	case '*':
		parent.Size = 0
		parent.Append(parent)
	default:
		node := new(Node)
		node.C = str[0]
		parent.Append(node)
		node.Parent = parent
		node.Size = 1
		vnow = node
	}
	ret := generatePattern(vnow, str[1:])
	if ret == 0 {
		parent.End = true
	}
	addParent := parent
	for addParent.Parent != nil {
		if addParent.Size == 0 {
			debug(toString(vnow), " -> ", toString(addParent.Parent))
			addParent.Parent.Append(vnow)
			addParent = addParent.Parent
		} else {
			break
		}
	}
	return parent.Size + ret
}

func check(now *Node, str string, idx int) bool {
	if len(str) <= idx {
		return now.End
	}
	list := now.Children['.']
	for _, v := range now.Children[str[idx]] {
		list = append(list, v)
	}
	for _, v := range list {
		r := check(v, str, idx+1)
		if r {
			return true
		}
	}
	return false
}
