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
	input := uint32(0b00000010100101000001111010011100)
	expect := uint32(0b00111001011110000010100101000000)
	assert.Equal(t, reverseBits(input), expect)
}

func TestReverseBits2(t *testing.T) {
	input := uint32(0b11111111111111111111111111111101)
	expect := uint32(0b10111111111111111111111111111111)
	assert.Equal(t, reverseBits(input), expect)
}
