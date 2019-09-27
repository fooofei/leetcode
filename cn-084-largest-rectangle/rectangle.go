package leetcode

import (
	"encoding/json"
	"fmt"
	"leetcode/segtree"
	"math"
)

type indexVal struct {
	value int
	index int
}

func (w *indexVal) String() string {
	out, _ := json.Marshal(w)
	return string(out)
}

func (w *indexVal) GoString() string {
	return fmt.Sprintf("withIndex %p %v", w, w.String())
}

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
