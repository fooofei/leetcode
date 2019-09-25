package leetcode

import (
	"encoding/json"
	"fmt"
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

func largestRectangleAreaMonoStack(heights []int) int {

	indexStack := make([]*indexVal, 0)

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

	for len(indexStack) > 0 {
		popVal := indexStack[len(indexStack)-1]
		indexStack = indexStack[0 : len(indexStack)-1]
		newArea := popVal.value * (len(heights) - popVal.index)
		maxArea = int(math.Max(float64(maxArea), float64(newArea)))
	}
	return maxArea
}
