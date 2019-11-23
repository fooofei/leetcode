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
	assert.Equal(t, isAnagram("anagram", "nagaram"), true)
}

func Test2(t *testing.T) {
	assert.Equal(t, isAnagram("rat", "car"), false)
}
