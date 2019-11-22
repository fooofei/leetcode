package leetcode

// 300 https://leetcode-cn.com/problems/longest-increasing-subsequence/

func maxInt(a, b int) int {
	if a > b {
		return a
	}
	return b
}

// Test3 证明这个栈的解法是错误的方向
func lengthOfLIS(nums []int) int {
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
