package leetcode

// 121 https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/

// 区别与其他的教程 我们这里分开写，先构造 diff 数组，然后转化为求最大子序列和
// 在最大子序列和的两端买入卖出 这样价值最大
// 最后要做要一个特殊处理 不可以为负数

func maxSubArray(nums []int) int {
	sum := nums[0]
	maxSofar := nums[0]
	for i := 1; i < len(nums); i += 1 {
		sum = maxInt(sum+nums[i], nums[i])
		maxSofar = maxInt(maxSofar, sum)
	}
	return maxInt(maxSofar, 0)
}

func maxProfit(prices []int) int {
	if len(prices) < 2 {
		return 0
	}
	diff := make([]int, len(prices)-1)
	for i := 0; i < len(prices)-1; i += 1 {
		diff[i] = prices[i+1] - prices[i]
	}
	return maxSubArray(diff)
}

func maxInt(a, b int) int {
	if a > b {
		return a
	}
	return b
}
