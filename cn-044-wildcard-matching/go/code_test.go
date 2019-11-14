package code

import "testing"
import "gotest.tools/assert"

func Test1(t *testing.T) {
	ret := isMatch("aa", "a")
	assert.Equal(t, ret, false)
}

func Test2(t *testing.T) {
	ret := isMatch("aa", "*")
	assert.Equal(t, ret, true)
}

func Test3(t *testing.T) {
	ret := isMatch("cb", "?a")
	assert.Equal(t, ret, false)
}

func Test4(t *testing.T) {
	ret := isMatch("adceb", "a*b")
	assert.Equal(t, ret, true)
}

func Test5(t *testing.T) {
	ret := isMatch("acdcb", "a*c?b")
	assert.Equal(t, ret, false)
}

func Test6(t *testing.T) {
	ret := isMatch("", "*")
	assert.Equal(t, ret, true)
}

func Test7(t *testing.T) {
	ret := isMatch("ho", "ho**")
	assert.Equal(t, ret, true)
}

func Test8(t *testing.T) {
	ret := isMatch("aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba", "a*******b")
	assert.Equal(t, ret, false)
}

func Test9(t *testing.T) {
	ret := isMatch("babbbbaabababaabbababaababaabbaabababbaaababbababaaaaaabbabaaaabababba"+
		"bbababbbaaaababbbabbbbbbbbbbaabbb",
		"b**bb**a**bba*b**a*bbb**aba***babbb*aa****aabb*bbb***a")
	assert.Equal(t, ret, false)
}
