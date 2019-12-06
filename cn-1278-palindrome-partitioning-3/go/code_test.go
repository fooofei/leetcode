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
	assert.Equal(t, palindromePartition("abc", 2), 1)
}

//    |  a |  a |  b |  b |  c |
//    |  0 |  1 |  2 |  3 |  4 |
//  0 |  0 |  0 |  0 |  0 |  0 |
//  1 |  0 |  0 |  1 |  2 |  2 |
//  2 |  0 |  0 |  0 |  0 |  1 |
//  3 |  0 |  0 |  0 |  0 |  0 |
//  4 |  0 |  0 |  0 |  0 |  0 |
//  5 |  0 |  0 |  0 |  0 |  0 |
func Test2(t *testing.T) {
	assert.Equal(t, palindromePartition("aabbc", 3), 0)
}

//    |  l |  e |  e |  t |  c |  o |  d |  e |
//    |  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |
//  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |
//  1 |  0 |  1 |  1 |  1 |  2 |  3 |  3 |  4 |
//  2 |  0 |  0 |  0 |  1 |  1 |  2 |  2 |  2 |
//  3 |  0 |  0 |  0 |  0 |  1 |  1 |  2 |  2 |
//  4 |  0 |  0 |  0 |  0 |  0 |  1 |  1 |  2 |
//  5 |  0 |  0 |  0 |  0 |  0 |  0 |  1 |  1 |
//  6 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  1 |
//  7 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |
//  8 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |
func Test3(t *testing.T) {
	assert.Equal(t, palindromePartition("leetcode", 8), 0)
}
