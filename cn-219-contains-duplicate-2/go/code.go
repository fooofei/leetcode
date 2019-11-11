package leetcode

import (
	"sort"
)

// 219 https://leetcode-cn.com/problems/contains-duplicate-ii/

type withIndex struct {
	Index int
	Val   int
}

func nearbyIndex(i int, j int, k int) bool {
	if i < j {
		return j-i <= k
	} else {
		return i-j <= k
	}
}
func containsNearbyDuplicate(nums []int, k int) bool {
	if len(nums) < 2 {
		return false
	}
	values := make([]withIndex, 0, len(nums))
	for index, val := range nums {
		values = append(values, withIndex{
			Index: index,
			Val:   val,
		})
	}
	sort.SliceStable(values, func(i, j int) bool {
		return values[i].Val < values[j].Val
	})

	last := values[0]
	for i := 1; i < len(values); i++ {
		if values[i].Val == last.Val &&
			nearbyIndex(values[i].Index, last.Index, k) {
			return true
		}
		last = values[i]
	}
	return false
}
