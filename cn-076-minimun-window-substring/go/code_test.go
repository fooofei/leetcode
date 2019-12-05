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
	assert.Equal(t, minWindow("ADOBECODEBANC", "ABC"), "BANC")
}

func Test2(t *testing.T) {
	assert.Equal(t, minWindow("a", "aa"), "")
}

func Test3(t *testing.T) {
	assert.Equal(t, minWindow("aa", "aa"), "aa")
}

func Test4(t *testing.T) {
	assert.Equal(t, minWindow("aaa", "aa"), "aa")
}
