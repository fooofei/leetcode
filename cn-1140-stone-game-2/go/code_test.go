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
	assert.Equal(t, stoneGameII([]int{2, 7, 9, 4, 4}), 10)
}

func Test2(t *testing.T) {
	assert.Equal(t, stoneGameII([]int{1, 2, 3, 4, 5, 100}), 104)
}
