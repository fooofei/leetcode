package leetcode

// 122 https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/
// 学习了 121 子序列和的解法 之后 就好做了

func sumSubArray(nums []int) int {
	sum := 0
	for i := 0; i < len(nums); i += 1 {
		sum += maxInt(nums[i], 0)
	}
	return sum
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

func maxInt(a, b int) int {
	if a > b {
		return a
	}
	return b
}
