package leetcode

import (
	"testing"

	"gotest.tools/assert"
)

type result struct {
	Input  []int
	Expect int
}

// 2   1   5   6   2   3
// 排序没用
// 3,6 2,5 5,3 0,2 4,2 1,1
// 3   2   5   0   4   1

// (2,1) (1,5) (5,5) (5,2) (2,3)  // 2=10
// 1  1  5  5  2  2  // 3=6
// 1  1  2  2  2  2  // 4=8
// 1  1  1  1  1  1      // 5 = 5

func testTempl(t *testing.T, fn func([]int) int) {
	cases := []result{
		{[]int{2, 1, 5, 6, 2, 3}, 10},
		{[]int{4, 2, 0, 3, 2, 5}, 6},
	}

	for _, v := range cases {
		out := fn(v.Input)
		assert.Equal(t, out, v.Expect)
	}
}

func TestDivision(t *testing.T) {
	testTempl(t, largestRectangleAreaDivision)
}

func TestMonoStack(t *testing.T) {
	testTempl(t, largestRectangleAreaMonoStack)
}

func TestSegmentTree(t *testing.T) {
	testTempl(t, largestRectangleAreaDivisionSegmentTree)
}
