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
	T := []int{0, 1, 0, 3, 12, }
	moveZeroes(T)
	assertEqualInts(t, T, []int{1, 3, 12, 0, 0, })
}