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
	assert.Equal(t, missingNumber([]int{3, 0, 1}), 2)
}

func Test2(t *testing.T) {
	assert.Equal(t, missingNumber([]int{9, 6, 4, 2, 3, 5, 7, 0, 1}), 8)
}

func Test3(t *testing.T) {
	assert.Equal(t, missingNumber([]int{0, 1, 3, 4}), 2)
}
