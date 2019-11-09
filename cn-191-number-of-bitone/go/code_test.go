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

func TestReverseBits1(t *testing.T) {
	input := uint32(0b00000000000000000000000000001011)
	expect := 3
	assert.Equal(t, hammingWeight(input), expect)
}
