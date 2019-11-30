package main

// 010 https://leetcode-cn.com/problems/regular-expression-matching/

// Russ Cox 的博客的 Golang 语言实现
// https://medium.com/@phanindramoganti/regex-under-the-hood-implementing-a-simple-regex-compiler-in-go-ef2af5c6079
// https://github.com/phanix5/Simple-Regex-Complier-in-Go/blob/master/regex.go

// Russ Cox 的博客
// Regular Expression Matching Can Be Simple And Fast
// (but is slow in Java, Perl, PHP, Python, Ruby, ...)
// https://swtch.com/~rsc/regexp/regexp1.html
// Russ Cox 说这是 Golang 的实现
// https://godoc.org/rsc.io/binaryregexp

// 题目解答 Ross Cox 的方案
// https://leetcode.com/problems/regular-expression-matching/discuss/393324/State-machine-solution-easy-to-follow

// 题目解答 Ross Cox 的方案
// https://leetcode.com/problems/regular-expression-matching/discuss/5951/C-solution-based-on-NFA-without-backtracking-only-4ms.-From-Russ-Cox.
//

// 中国人的翻译正则表达式和 NFA - luobo tang的文章 - 知乎
// https://zhuanlan.zhihu.com/p/45954880

// 缺点，原版本不支持 regex 中的 . 匹配，我根据 leetcode 解答学习过来

// Ken Thompson's multi-state simulation

type StateType int

const (
	Default StateType = 0 // out used
	Split   StateType = 1 // out & out1 used
	Match   StateType = 2
)

func (t StateType) String() string {
	switch t {
	case Split:
		return "Split"
	case Match:
		return "Match"
	default:
		return "Default"
	}
}

type State struct {
	Type StateType // type identifier
	Ch   rune      // char
	Out  *State
	Out1 *State
	ListID int
}

func addState(l []*State, s *State, listid int) []*State {
	if s.ListID == listid {
		return l
	}
	if s.Type == Split {
		l = addState(l, s.Out, listid)
		l = addState(l, s.Out1, listid)
	} else {
		l = append(l, s)
	}
	return l
}

func step(clist []*State, ch rune, nlist []*State, listid * int) []*State {
	(*listid) += 1
	for _, s := range clist {
		if s.Ch == '.' && s.Out != nil {
			nlist = addState(nlist, s.Out, *listid)
		} else if ch == s.Ch && s.Out != nil {
			nlist = addState(nlist, s.Out, *listid)
		}
	}
	return nlist
}

func makeState(ch, nextch rune) (*State, int) {
	if nextch == '*' {
		split := &State{
			Type: Split, Ch: 0,
		}
		s := &State{
			Type: Default, Ch: ch,
		}
		split.Out1 = s
		s.Out = split
		return split, 2
	} else {
		s := &State{
			Type: Default, Ch: ch,
		}
		return s, 1
	}
}

func build(runep []rune, matchState *State) *State {
	var start *State
	start = &State{
		Type: Default, Ch: 0,
	}
	i := 0
	if len(runep) > 1 {
		start, i = makeState(runep[0], runep[1])
	} else if len(runep) > 0 {
		start, i = makeState(runep[0], '$')
	}
	curState := start
	for i < len(runep) {
		ch := runep[i]
		var nextch rune
		if i+1 >= len(runep) {
			nextch = '$'
		} else {
			nextch = runep[i+1]
		}
		newState, off := makeState(ch, nextch)
		curState.Out = newState
		curState = newState
		i += off
	}
	curState.Out = matchState
	return start
}

func hasMatch(l []*State, matchState *State) bool {
	for _, s := range l {
		if s == matchState {
			return true
		}
	}
	return false
}

func isMatch(s string, p string) bool {
	if len(p) == 0 {
		return len(s) == 0
	}
	matchState := &State{
		Type: Match,
	}
	runep := []rune(p)
	start := build(runep, matchState)

	clist := make([]*State, 0, len(runep)+1)
	nlist := make([]*State, 0, len(runep)+1)

	// 原版本的称呼，作用是减少 clist 中重复的状态
	listid := 1
	clist = addState(clist, start, listid)
	for _, ch := range s {
		nlist = nlist[:0]
		nlist = step(clist, ch, nlist)
		clist, nlist = nlist, clist
	}
	return hasMatch(clist, matchState)
}
