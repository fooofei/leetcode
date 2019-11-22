package leetcode

// 309 https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/

func maxInt(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func sumSubArray(nums []int) int {
	T := make([]int, len(nums)+3)
	for i := 0; i < len(nums); i += 1 {
		j := i + 3
		T[j] = maxInt(T[j-1]+nums[i], T[j-3]+nums[i])
		T[j] = maxInt(T[j], nums[i])
		T[j] = maxInt(T[j], T[j-1])
	}
	// 不要忘记消除负数
	return maxInt(0, T[len(T)-1])
}

func maxProfit(prices []int) int {
	if len(prices) < 2 {
		return 0
	}
	diff := make([]int, len(prices)-1)
	for i := 0; i < len(prices)-1; i += 1 {
		diff[i] = prices[i+1] - prices[i]
	}
	return sumSubArray(diff)
}
