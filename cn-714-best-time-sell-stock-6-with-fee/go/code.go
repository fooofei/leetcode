package leetcode

// 714 https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/

func maxInt(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func minInt(a, b int) int {
	if a < b {
		return a
	}
	return b
}

// 学习动态规划 看了视频学到的
// Tushar Roy
// https://www.youtube.com/watch?v=oDhu5uGq_ic
// T[i][j] = max(T[i][j-1],
//  T[i-1][0] + A[j]-A[0],
//  T[i-1][1] + A[j]-A[1],
//  T[i-1][2] + A[j]-A[2],
// ....
//  T[i-1][j-1] + A[j]-A[j-1],
// )

func sumSubArray(nums []int) int {
	sum := 0
	for i := 0; i < len(nums); i += 1 {
		sum += maxInt(nums[i], 0)
	}
	return sum
}

func maxProfitInf(prices []int) int {
	if len(prices) < 2 {
		return 0
	}
	diff := make([]int, len(prices)-1)
	for i := 0; i < len(prices)-1; i += 1 {
		diff[i] = prices[i+1] - prices[i]
	}
	return sumSubArray(diff)
}

func maxProfitK(prices []int, K int) int {
	if len(prices) < 2 {
		return 0
	}
	if K > len(prices)/2 {
		// 这一招是在这里学习的 https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/tuan-mie-gu-piao-wen-ti
		// 我是这样打算的 K = minInt(K, len(prices))  可是这还不够
		return maxProfitInf(prices)
	}
	T := make([][]int, K+1)
	for i := range T {
		T[i] = make([]int, len(prices))
	}
	// Golang 语言默认初始化 0 ，可以不给初值
	//for i := range T[0] {
	//	T[0][i] = 0
	//}
	//for i := range T {
	//	T[i][0] = 0
	//}
	for i := 1; i < K+1; i++ {
		maxDiff := T[i][0] - prices[0]
		for j := 1; j < len(prices); j++ {
			// 化简 降低维度
			//maxHere := math.MinInt32
			//for k := 0; k < j; k++ {
			//	maxHere = maxInt(T[i-1][k]+prices[j]-prices[k], maxHere)
			//}
			T[i][j] = maxInt(T[i][j-1], prices[j]+maxDiff)
			maxDiff = maxInt(maxDiff, T[i-1][j]-prices[j])
		}
	}
	return T[K][len(prices)-1]
}

func maxProfit(k int, prices []int) int {
	return maxProfitK(prices, k)
}
