package leetcode

// 053 https://leetcode-cn.com/problems/maximum-subarray/

// 学习了 kadane 算法后 默写出来的
func maxSubArray1(nums []int) int {
	if len(nums) <= 0 {
		return 0
	}
	maxSofar := nums[0]
	sum := nums[0]
	for i := 1; i < len(nums); i++ {
		sum = maxInt(sum+nums[i], nums[i])
		maxSofar = maxInt(sum, maxSofar)
	}
	return maxSofar
}

func maxInt(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func maxSubArray(nums []int) int {
	if len(nums) < 1 {
		return 0
	}
	T := make([]int, len(nums))
	max := nums[0]
	T[0] = nums[0]
	for i := 1; i < len(nums); i++ {
		T[i] = maxInt(T[i-1]+nums[i], nums[i])
		max = maxInt(max, T[i])
	}
	return max
}
