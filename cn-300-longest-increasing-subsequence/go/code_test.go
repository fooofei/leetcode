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
	assert.Equal(t, lengthOfLIS([]int{10,9,2,5,3,7,101,18}), 4)
}

func Test2(t *testing.T) {
	assert.Equal(t, lengthOfLIS([]int{0}), 1)
}

func Test3(t *testing.T) {
	assert.Equal(t, lengthOfLIS([]int{1,3,6,7,9,4,10,5,6}), 6)
}


