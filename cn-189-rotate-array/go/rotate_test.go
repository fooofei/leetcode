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

func TestRotate1(t *testing.T) {
	a := []int{1, 2, 3, 4, 5, 6, 7}

	rotate(a, 3)
	expect := []int{5, 6, 7, 1, 2, 3, 4}
	assertEqualInts(t, a, expect)
}

func TestRotate2(t *testing.T) {
	a := []int{1, 2, 3, 4, 5, 6}

	rotate(a, 2)
	expect := []int{5, 6, 1, 2, 3, 4}
	assertEqualInts(t, a, expect)
}
