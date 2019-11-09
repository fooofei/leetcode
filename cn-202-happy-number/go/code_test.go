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
	assert.Equal(t, isHappy(19), true)
}

func Test2(t *testing.T) {
	assert.Equal(t, isHappy(9), false)
}

func Test3(t *testing.T) {
	assert.Equal(t, isHappy(7), true)
}

func Test4(t *testing.T) {
	assert.Equal(t, isHappy(1111111), true)
}
