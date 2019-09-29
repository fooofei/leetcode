package leetcode

import (
	"math"
)

// 焦点一 遇到相等的值 是否要出栈
// 焦点二 出栈时的高度是当前出栈的值，宽度怎么计算
//       应该是找最大宽度

// 如果是 相等出栈，则满足栈中的值一定比出栈的值小，
// 因此如果出栈， 则 width = width1 + width2
//   width1 = 出栈的索引 - 出栈后栈顶的索引(没有就是 -1)
//   width2 = 曾经出过栈的宽度 = 当前索引 - 出栈索引 - 1
//   综述 ：width = 当前索引 - 出栈后栈顶索引 -1
//   如果当前索引的值与出栈的值相等  width 不加上当前索引的宽度 1
//   这个宽度在当前索引入栈后会计算到

// 如果是 相等不出栈 满足栈中的值 <= 出栈的值
// width = width1 + width2
//  width1 = 出栈索引 - 出栈后栈顶的索引（默认-1）
//  width2 = 当前索引 - 出栈索引 - 1
// 与上面一致

func largestRectangleAreaMonoStack2(heights []int) int {

	if len(heights) <= 0 {
		return 0
	}
	heights = append(heights, -1)

	maxArea := 0
	// stack save index
	stack := make([]int, 0)

	for i := 0; i < len(heights); i++ {

		for len(stack) > 0 {
			last := stack[len(stack)-1]
			height := heights[last]
			if heights[i] > height {
				break
			}
			// pop
			stack = stack[:len(stack)-1]
			left := -1
			if len(stack) > 0 {
				left = stack[len(stack)-1]
			}
			// 想不明白 宽度是怎么计算的
			area := height * (i - left - 1)
			maxArea = int(math.Max(float64(maxArea), float64(area)))
		}
		stack = append(stack, i)
	}
	return maxArea
}
