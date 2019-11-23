package leetcode

import (
	"math"
)

// 309 https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/

func maxInts(nums ...int) int {
	a := nums[0]
	for i := 1; i < len(nums); i++ {
		if nums[i] > a {
			a = nums[i]
		}
	}
	return a
}

func sumSubArray(nums []int) int {
	T := make([]int, len(nums)+3)
	preMax := T[0]
	maxSofar := 0
	for i := 0; i < len(nums); i += 1 {
		j := i + 3
		preMax = maxInts(preMax, T[j-3])
		T[j] = maxInts(T[j-1]+nums[i], preMax+nums[i], nums[i])
		maxSofar = maxInts(T[j], maxSofar)
	}
	// 不要忘记消除负数
	// T[-1] 不是最终值 T[-2] 也是需要比较的
	return maxSofar
}

func maxProfit1(prices []int) int {
	if len(prices) < 2 {
		return 0
	}
	diff := make([]int, len(prices)-1)
	for i := 0; i < len(prices)-1; i += 1 {
		diff[i] = prices[i+1] - prices[i]
	}
	return sumSubArray(diff)
}

// 上面的解决方案是学习了 Tushar Roy 的视频 猜出来的
// 下面再写另一个动态规划的解决方案

func maxProfit(prices []int) int {
	if len(prices) < 2 {
		return 0
	}
	T := make([][]int, 2)
	for i := range T {
		T[i] = make([]int, len(prices)+2)
	}
	T[1][0] = math.MinInt32
	T[1][1] = math.MinInt32
	for i := range prices {
		j := i + 2
		T[0][j] = maxInts(T[0][j-1], T[1][j-1]+prices[i])
		T[1][j] = maxInts(T[1][j-1], T[0][j-2]-prices[i])
	}
	return T[0][len(prices)+1]
}
