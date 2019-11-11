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
	assert.Equal(t, isIsomorphic("egg", "add"), true)
}

func Test2(t *testing.T) {
	assert.Equal(t, isIsomorphic("foo", "bar"), false)
}

func Test3(t *testing.T) {
	assert.Equal(t, isIsomorphic("paper", "title"), true)
}

func Test4(t *testing.T) {
	assert.Equal(t, isIsomorphic("ab", "aa"), false)
}
