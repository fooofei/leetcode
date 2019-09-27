package leetcode

import (
	"math"
)

func minMaxIndex(a []int) (int, int) {
	if len(a) <= 0 {
		return len(a), len(a)
	}
	minIndex := 0
	maxIndex := 0
	for i := 1; i < len(a); i++ {
		if a[i] < a[minIndex] {
			minIndex = i
		}
		if a[i] > a[maxIndex] {
			maxIndex = i
		}
	}
	return minIndex, maxIndex
}

//这样要找的最大矩形区域就是三种情况了。
//
//最大矩形区域在不包含选定柱子的左半区域当中。
//最大矩形区域在不包含选定柱子的右半区域当中。
//最大矩形区域包含选定柱子的区域。

func largestRectangleAreaDivision(heights []int) int {
	min, _ := minMaxIndex(heights)
	if min >= len(heights) {
		return 0
	}

	areaMax := heights[min] * len(heights)
	areaLeft := largestRectangleAreaDivision(heights[0:min])
	areaMax = int(math.Max(float64(areaMax), float64(areaLeft)))
	if min < len(heights)-1 {
		areRight := largestRectangleAreaDivision(heights[min+1:])
		areaMax = int(math.Max(float64(areaMax), float64(areRight)))
	}
	return areaMax
}
