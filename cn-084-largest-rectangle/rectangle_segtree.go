package leetcode

import (
	"leetcode/segtree"
	"math"
)

type intSlice []int

func (s intSlice) Len() int {
	return len(s)
}

// Oper ... 实现 Oper，返回最小值的索引
func (s intSlice) Oper(left int, right int) int {
	if s[left] < s[right] {
		return left
	}
	return right
}

func largestRectangleAreaDivisionSegmentTree(heights []int) int {

	if len(heights) <= 0 {
		return 0
	}

	st := segtree.New(intSlice(heights))

	return largestRectangleAreaDivisionSt(st, heights, 0, len(heights)-1)
}

func largestRectangleAreaDivisionSt(st *segtree.SegmentTree, heights []int, start int, end int) int {

	idx := 0
	if start < end {
		idx = st.Search(start, end, intSlice(heights))
	} else {
		// 只有 1 个值，不进行搜索了，加速
		idx = start
	}

	minValue := heights[idx]

	areaMax := minValue * (end - start + 1)
	if idx > start {
		areaLeft := largestRectangleAreaDivisionSt(st, heights, start, idx-1)
		areaMax = int(math.Max(float64(areaMax), float64(areaLeft)))
	}
	if idx < end {
		areRight := largestRectangleAreaDivisionSt(st, heights, idx+1, end)
		areaMax = int(math.Max(float64(areaMax), float64(areRight)))
	}
	return areaMax
}
