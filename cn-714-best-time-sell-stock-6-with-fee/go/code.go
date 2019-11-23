package leetcode

import (
	"math"
)

// 714 https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/

func maxInts(nums ...int) int {
	a := nums[0]
	for i:=1; i<len(nums); i++ {
		if nums[i] > a {
			a = nums[i]
		}
	}
	return a
}

// 同样是不限次数交易，122 可以求和，这道题目不可以求和了
// 学习了这里 https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/tuan-mie-gu-piao-wen-ti
// 得到的 ，第一次没看懂，后来看了 Tushar Roy 的解说才有点入门
func maxProfit(prices []int, fee int) int {
	// T[i][k][0] = max(T[i-1][k][0], T[i-1][k-1][1]+prices[i])
	// T[i][k][1] = max(T[i-1][k][1], T[i-1][k-1][0]-prices[i])

	if len(prices) < 2 {
		return 0
	}
	T := make([][]int, len(prices)+1)
	for i := range T {
		T[i] = make([]int, 2)
	}
	T[0][1] = math.MinInt32
	for i := range prices {
		j := i+1
		T[j][0] = maxInts(T[j-1][0], T[j-1][1]+prices[i])
		T[j][1] = maxInts(T[j-1][1], T[j-1][0]-prices[i] - fee)
	}
	return T[len(prices)][0]
}