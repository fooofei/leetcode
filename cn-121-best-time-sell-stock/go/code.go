package leetcode

import (
	"math"
)

// 121 https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/

// 区别与其他的教程 我们这里分开写，先构造 diff 数组，然后转化为求最大子序列和
// 在最大子序列和的两端买入卖出 这样价值最大
// 最后要做要一个特殊处理 不可以为负数

func maxSubArray(nums []int) int {
	sum := nums[0]
	maxSofar := nums[0]
	for i := 1; i < len(nums); i += 1 {
		sum = maxInts(sum+nums[i], nums[i])
		maxSofar = maxInts(maxSofar, sum)
	}
	return maxInts(maxSofar, 0)
}

func maxProfit1(prices []int) int {
	if len(prices) < 2 {
		return 0
	}
	diff := make([]int, len(prices)-1)
	for i := 0; i < len(prices)-1; i += 1 {
		diff[i] = prices[i+1] - prices[i]
	}
	return maxSubArray(diff)
}

func maxInts(nums ...int) int {
	a := nums[0]
	for i := 1; i < len(nums); i++ {
		if nums[i] > a {
			a = nums[i]
		}
	}
	return a
}

func maxProfit(prices []int) int {
	if len(prices) < 2 {
		return 0
	}
	T := make([][]int, 2)
	for i := range T {
		T[i] = make([]int, len(prices)+1)
	}
	// 0=不持有 1=持有
	T[1][0] = math.MinInt32
	for i := range prices {
		j := i + 1
		// 不持有
		// T[0][j][k] = maxInts(T[0][j-1][k], T[1][j-1][k] + prices[i])
		T[0][j] = maxInts(T[0][j-1], T[1][j-1]+prices[i])
		// 持有 T[1][j][k] = maxInts(T[1][j-1][k], T[0][j-1][k-1] - prices[i])
		T[1][j] = maxInts(T[1][j-1], -prices[i])
	}
	return T[0][len(prices)]
}
