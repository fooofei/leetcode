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
	assert.Equal(t, containsDuplicate([]int{1, 2, 3, 1}), true)
}

func Test2(t *testing.T) {
	assert.Equal(t, containsDuplicate([]int{1, 2, 3, 4}), false)
}

func Test3(t *testing.T) {
	assert.Equal(t, containsDuplicate([]int{1, 1, 1, 3, 3, 4, 3, 2, 4, 2}), true)
}
