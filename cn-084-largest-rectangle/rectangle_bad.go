package leetcode

// 看我这个失败的思路
/*
func largestRectangleArea1(heights []int) int {

	withIndexs := make(withIndexSlice, 0, len(heights))
	allAreas := make([]int,0,3)

	for index, value := range heights {
		withIndexs = append(withIndexs, &withIndex{value: value, index: index})
	}
	sort.Stable(withIndexs)
	if len(withIndexs)<=0 {
		return 0
	}
	// 竖方向最大
	allAreas = append(allAreas, withIndexs[0].value)
	// 横方向的最大值
	last := withIndexs[len(withIndexs)-1]
	if last.value>0 {
		allAreas = append(allAreas, last.value*len(withIndexs))
	}
	neighbors := make(withIndexSlice,0,len(heights))

	for index,value := range withIndexs[:len(withIndexs)-1] {
		neighbors = neighbors[:0]
		if value.sumed {
			continue
		}
		neighbors = append(neighbors, value)
		value.sumed = true
		for _,value2 := range withIndexs[index+1:] {
			hasNeighbor := false
			for _,neighbor := range neighbors{
				if math.Abs(float64(neighbor.index-value2.index)) <2{
					hasNeighbor = true
					break
				}
			}
			if hasNeighbor{
				neighbors = append(neighbors, value2)
				value2.sumed = true
				last = neighbors[len(neighbors)-1]
				allAreas = append(allAreas, last.value*len(neighbors))
			}
		}
	}
	sort.Ints(allAreas)
	return allAreas[len(allAreas)-1]
}

*/
