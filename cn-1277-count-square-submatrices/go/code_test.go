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

//    |  0 |  1 |  2 |  3 |
//  0 |  0 |  1 |  1 |  1 |
//  1 |  1 |  1 |  1 |  1 |
//  2 |  0 |  1 |  1 |  1 |
//
//------------------------
//
//    |  0 |  1 |  2 |  3 |
//  0 |  0 |  1 |  1 |  1 |
//  1 |  1 |  1 |  2 |  2 |
//  2 |  0 |  1 |  2 |  3 |
func Test1(t *testing.T) {
	matrix := [][]int {
		{0,1,1,1,},
		{1,1,1,1,},
		{0,1,1,1,},
	}
	assert.Equal(t, countSquares(matrix), 15)
}

//    |  0 |  1 |  2 |
//  0 |  1 |  0 |  1 |
//  1 |  1 |  1 |  0 |
//  2 |  1 |  1 |  0 |
//
//------------------------
//
//    |  0 |  1 |  2 |
//  0 |  1 |  0 |  1 |
//  1 |  1 |  1 |  0 |
//  2 |  1 |  2 |  0 |
func Test2(t *testing.T) {
	matrix := [][]int {
		{1,0,1,},
		{1,1,0,},
		{1,1,0,},
	}
	assert.Equal(t, countSquares(matrix), 7)
}

