package leetcode

// 123 https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/

func reverseInts(nums []int) []int {
	dummy := make([]int, len(nums))
	copy(dummy, nums)
	i := 0
	j := len(dummy) - 1
	for i < j {
		dummy[i], dummy[j] = dummy[j], dummy[i]
		i++
		j--
	}
	return dummy
}

func subArray(nums []int) []int {
	sub := make([]int, len(nums)-1)
	sum := nums[0]
	maxSofar := nums[0]
	sub[0] = nums[0]
	for i := 1; i < len(nums)-1; i++ {
		sum = maxInt(sum+nums[i], nums[i])
		maxSofar = maxInt(maxSofar, sum)
		sub[i] = maxSofar
	}
	return sub
}

func maxProfit(prices []int) int {
	if len(prices) < 2 {
		return 0
	}
	diff := make([]int, len(prices)-1)
	for i := 0; i < len(prices)-1; i += 1 {
		diff[i] = prices[i+1] - prices[i]
	}
	if len(diff) < 2 {
		return maxInt(0, diff[0])
	}
	// 假想为有1条分解线，求左右两边最大连续子序列和，
	// 如果这个最大连续子序列挨着，就合并为 1 个了
	left := subArray(diff)
	right := subArray(reverseInts(diff))
	right = reverseInts(right)
	maxSofar := 0
	for i := 0; i < len(left); i++ {
		maxSofar = maxInt(maxSofar, left[i])
		maxSofar = maxInt(maxSofar, right[i])
		maxSofar = maxInt(maxSofar, left[i]+right[i])
	}
	return maxSofar
}

func maxInt(a, b int) int {
	if a > b {
		return a
	}
	return b
}
