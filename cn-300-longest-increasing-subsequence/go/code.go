package leetcode

import (
	"sort"
)

// 300 https://leetcode-cn.com/problems/longest-increasing-subsequence/

func maxInt(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func lengthOfLIS2(nums []int) int {
	if len(nums) <= 0 {
		return 0
	}
	dp := make([]int, len(nums))
	for i := range dp {
		dp[i] = 1
	}
	maxSofar := 1
	for i := 1; i < len(nums); i++ {
		for j := 0; j < i; j++ {
			if nums[i] > nums[j] {
				dp[i] = maxInt(dp[i], dp[j]+1)
			}
		}
		maxSofar = maxInt(maxSofar, dp[i])
	}
	return maxSofar
}

// 从这里学习来的 patience game 扑克算法
// https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/dong-tai-gui-hua-she-ji-zui-chang-di-zeng-zi-xu-lie#er-er-fen-cha-zhao-jie-fa

func lengthOfLIS(nums []int) int {
	if len(nums) <= 0 {
		return 0
	}
	// 从小到大的排列
	mins := make([]int, 0)
	for i := 0; i < len(nums); i++ {
		firstNotLess := sort.Search(len(mins), func(j int) bool {
			return mins[j] >= nums[i]
		})
		if firstNotLess >= len(mins) {
			mins = append(mins, nums[i])
		} else {
			mins[firstNotLess] = nums[i]
		}
	}
	return len(mins)
}

// Test3 证明这个栈的解法是错误的方向
func lengthOfLIS1(nums []int) int {
	stack := make([]int, 0)
	maxSubLen := 0
	if len(nums) < 1 {
		return 0
	}
	for i := 0; i < len(nums); i++ {
		for len(stack) > 0 && nums[i] <= stack[0] {
			maxSubLen = maxInt(len(stack), maxSubLen)
			stack = stack[1:]
		}
		stack = append([]int{nums[i]}, stack...)
	}
	maxSubLen = maxInt(len(stack), maxSubLen)
	return maxSubLen
}
