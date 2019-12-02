package main

// 010 https://leetcode-cn.com/problems/regular-expression-matching/

// Russ Cox 的博客的 Golang 语言实现
// https://medium.com/@phanindramoganti/regex-under-the-hood-implementing-a-simple-regex-compiler-in-go-ef2af5c6079
// https://github.com/phanix5/Simple-Regex-Complier-in-Go/blob/master/regex.go

// Russ Cox 的博客
// Regular Expression Matching Can Be Simple And Fast
// (but is slow in Java, Perl, PHP, Python, Ruby, ...)
// https://swtch.com/~rsc/regexp/regexp1.html
// https://swtch.com/~rsc/regexp/nfa.c.txt
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
	Default StateType = 0 // `out` used
	Split   StateType = 1 // `out` & `out1` used
	Match   StateType = 2 // the final state
)

// String() add convenient string for debug or print StateType
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
	Mark int // 用 stepCount 去除步进状态集中的重复状态 真是秒
}

func addState(l []*State, s *State, stepCount int) []*State {
	queue := make([]*State, 0, 16)
	queue = append(queue, s)
	for len(queue) > 0 {
		s = queue[0]
		queue = queue[1:]
		if s.Mark == stepCount {
			continue
		}
		s.Mark = stepCount
		if s.Type == Split {
			queue = append(queue, s.Out)
			queue = append(queue, s.Out1)
		} else {
			l = append(l, s)
		}
	}
	return l
}

func step(clist []*State, ch rune, nlist []*State, stepCount int) []*State {
	for _, s := range clist {
		if s.Ch == '.' && s.Out != nil {
			nlist = addState(nlist, s.Out, stepCount)
		} else if ch == s.Ch && s.Out != nil {
			nlist = addState(nlist, s.Out, stepCount)
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

	i := 0
	if len(runep) > 1 {
		start, i = makeState(runep[0], runep[1])
	} else if len(runep) > 0 {
		start, i = makeState(runep[0], '$')
	} else {
		return nil
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
		// 这个题目只支持连接 不支持或(|)
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

	stepCount := 1
	clist = addState(clist, start, stepCount)
	for _, ch := range s {
		nlist = nlist[:0]
		stepCount += 1
		nlist = step(clist, ch, nlist, stepCount)
		clist, nlist = nlist, clist
	}
	return hasMatch(clist, matchState)
}
