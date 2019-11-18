package leetcode

import (
	"testing"

	"gotest.tools/assert"
)

func assertEqualInts(t *testing.T, a []int, b []int) {
	assert.Equal(t, len(a), len(b))
	for i := 0; i < len(a); i++ {
		assert.Equal(t, a[i], b[i])
	}
}

func Test1(t *testing.T) {
	ret := wordBreak("leetcode", []string{
		"leet",
		"code",
	})
	assert.Equal(t, ret, true)
}

func Test2(t *testing.T) {
	ret := wordBreak("leetcode", []string{
		"leet",
		"leetco",
		"code",
	})
	assert.Equal(t, ret, true)
}

func Test3(t *testing.T) {
	ret := wordBreak("leetcocode", []string{
		"leet",
		"leetco",
		"code",
	})
	assert.Equal(t, ret, true)
}

func Test4(t *testing.T) {
	ret := wordBreak("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"+
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab",
		[]string{"a", "aa", "aaa", "aaaa",
			"aaaaa", "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa",
			"aaaaaaaaaa"})
	assert.Equal(t, ret, false)
}

func Test5(t *testing.T) {
	ret := wordBreak("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"+
		"abaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		[]string{"aa", "aaa", "aaaa", "aaaaa", "aaaaaa",
			"aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa", "ba"})
	assert.Equal(t, ret, true)
}
