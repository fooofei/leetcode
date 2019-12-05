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
	assert.Equal(t, numSquares(12), 3)
}

func Test2(t *testing.T) {
	assert.Equal(t, numSquares(13), 2)
}

func Test3(t *testing.T) {
	assert.Equal(t, numSquares(10), 2)
}

func Test4(t *testing.T) {
	assert.Equal(t, numSquares(1), 1)
}

func Test5(t *testing.T) {
	assert.Equal(t, numSquares(48), 3)
}

func Test6(t *testing.T) {
	assert.Equal(t, numSquares(22), 3)
}

func Test7(t *testing.T) {
	assert.Equal(t, numSquares(23), 4)
}

func Test8(t *testing.T) {
	assert.Equal(t, numSquares(4), 1)
}
