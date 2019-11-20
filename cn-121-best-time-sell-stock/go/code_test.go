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
	ret := maxProfit([]int{7,1,5,3,6,4})
	assert.Equal(t, ret, 5)
}

func Test2(t *testing.T) {
	ret := maxProfit([]int{7,6,4,3,1})
	assert.Equal(t, ret, 0)
}