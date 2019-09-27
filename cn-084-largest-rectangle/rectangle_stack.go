package  leetcode

import (
	"math"
)

// 单调栈的性质
// 单调递增栈可以找到左起第一个比当前数字小的元素。
// 单调递减栈可以找到左起第一个比当前数字大的元素。

func largestRectangleAreaMonoStack(heights []int) int {

	indexStack := make([]*indexVal, 0)
	// trick 在尾部放 1 个0，就归一化了处理流程，无须最后判断栈是否空
	heights = append(heights, 0)

	maxArea := 0
	for i := 0; i < len(heights); i++ {

		var last *indexVal
		for len(indexStack) > 0 {
			popVal := indexStack[len(indexStack)-1]
			if popVal.value <= heights[i] {
				break
			}
			last = popVal
			indexStack = indexStack[0 : len(indexStack)-1]
			newArea := last.value * (i - last.index)
			maxArea = int(math.Max(float64(maxArea), float64(newArea)))
		}
		pushVal := &indexVal{index: i, value: heights[i]}
		if last != nil {
			pushVal.index = last.index
		}
		indexStack = append(indexStack, pushVal)
	}

	// 这回就用不到尾巴的判断了
	//for len(indexStack) > 0 {
	//	popVal := indexStack[len(indexStack)-1]
	//	indexStack = indexStack[0 : len(indexStack)-1]
	//	newArea := popVal.value * (len(heights) - popVal.index)
	//	maxArea = int(math.Max(float64(maxArea), float64(newArea)))
	//}
	return maxArea
}
