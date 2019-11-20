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
	ret := maxProfit([]int{3,3,5,0,0,3,1,4})
	assert.Equal(t, ret, 6)
}

func Test2(t *testing.T) {
	ret := maxProfit([]int{7,6,4,3,1})
	assert.Equal(t, ret, 0)
}

func Test3(t *testing.T) {
	ret := maxProfit([]int{1,2,3,4,5,})
	assert.Equal(t, ret, 4)
}

func Test4(t *testing.T) {
	ret := maxProfit([]int{1,4,2})
	assert.Equal(t, ret, 3)
}