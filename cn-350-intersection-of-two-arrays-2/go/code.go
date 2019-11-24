package leetcode

import (
	"sort"
)

// 350 https://leetcode-cn.com/problems/intersection-of-two-arrays-ii/

type CountItem struct {
	Val   int
	Count int
}

func isInSlice(nums []CountItem, n int) bool {
	firstTrue := sort.Search(len(nums), func(i int) bool {
		return n <= nums[i].Val
	})
	if firstTrue < len(nums) && nums[firstTrue].Val == n {
		if nums[firstTrue].Count > 0 {
			nums[firstTrue].Count -= 1
			return true
		}
	}
	return false
}

func intersect(nums1 []int, nums2 []int) []int {
	if len(nums1) > len(nums2) {
		return intersect(nums2, nums1)
	}
	sort.Slice(nums1, func(i, j int) bool {
		return nums1[i] < nums1[j]
	})
	counts := make([]CountItem, 0, len(nums1))
	for _, n := range nums1 {
		if len(counts) > 0 && counts[len(counts)-1].Val == n {
			counts[len(counts)-1].Count += 1
		} else {
			counts = append(counts, CountItem{
				Val:   n,
				Count: 1,
			})
		}
	}

	section := make([]int, 0)
	for _, n := range nums2 {
		if isInSlice(counts, n) {
			section = append(section, n)
		}
	}
	return section
}
