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
	ret := maxProfit([]int{1, 2, 3, 0, 2})
	assert.Equal(t, ret, 3)
}

func Test2(t *testing.T) {
	ret := maxProfit([]int{1, 4, 2})
	assert.Equal(t, ret, 3)
}

func Test3(t *testing.T) {
	ret := maxProfit([]int{4, 2, 7, 1, 11})
	assert.Equal(t, ret, 10)
}

func Test4(t *testing.T) {
	ret := maxProfit([]int{6, 1, 6, 4, 3, 0, 2})
	assert.Equal(t, ret, 7)
}
