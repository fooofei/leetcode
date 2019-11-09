package leetcode

import (
	"gotest.tools/assert"
	"testing"
)

func assertEqualInts(t *testing.T, a []int, b []int) {
	assert.Equal(t, len(a), len(b))
	for i := 0; i < len(a); i++ {
		assert.Equal(t, a[i], b[i])
	}
}

func Test1(t *testing.T) {
	input := []int{2, 1, 1, 2}
	expect := 4
	assert.Equal(t, rob(input), expect)
}

func Test2(t *testing.T) {
	input := []int{2, 7, 9, 3, 1}
	expect := 12
	assert.Equal(t, rob(input), expect)
}

func Test3(t *testing.T) {
	input := []int{1, 2, 3, 1}
	expect := 4
	assert.Equal(t, rob(input), expect)
}
