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
	assert.Equal(t, stoneGame([]int{5, 3, 4, 5}), true)
}

func Test2(t *testing.T) {
	assert.Equal(t, stoneGame([]int{3, 9, 1, 2}), true)
}
