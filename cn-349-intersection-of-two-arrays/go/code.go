package leetcode

import (
	"sort"
)

// 349 https://leetcode-cn.com/problems/intersection-of-two-arrays/

func uniqInsert(nums []int, n int) []int {
	firstTrue := sort.Search(len(nums), func(i int) bool {
		return n <= nums[i]
	})
	if firstTrue < len(nums) {
		if nums[firstTrue] != n {
			ret := append([]int{}, nums[0:firstTrue]...)
			ret = append(ret, n)
			return append(ret, nums[firstTrue:]...)
		}
		return nums
	}
	return append(nums, n)
}

func isInSlice(nums []int, n int) bool {
	firstTrue := sort.Search(len(nums), func(i int) bool {
		return n <= nums[i]
	})
	return firstTrue < len(nums) && nums[firstTrue] == n
}

func intersection(nums1 []int, nums2 []int) []int {
	if len(nums1) > len(nums2) {
		return intersection(nums2, nums1)
	}
	sort.Slice(nums1, func(i, j int) bool {
		return nums1[i] < nums1[j]
	})
	section := make([]int, 0)
	for _, n := range nums2 {
		if isInSlice(nums1, n) {
			section = uniqInsert(section, n)
		}
	}
	return section
}
