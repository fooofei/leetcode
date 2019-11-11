package leetcode

import (
	"sort"
)

// 217 https://leetcode-cn.com/problems/contains-duplicate/

func containsDuplicate(nums []int) bool {
	if len(nums) < 2 {
		return false
	}
	sort.Slice(nums, func(i, j int) bool {
		return nums[i] < nums[j]
	})
	last := nums[0]
	for i := 1; i < len(nums); i++ {
		if nums[i] == last {
			return true
		}
		last = nums[i]
	}
	return false
}
