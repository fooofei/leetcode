package leetcode

import (
	"math"
)

// 279 https://leetcode-cn.com/problems/perfect-squares/

func minInt(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func counts(n int, cache []int) int {
	if n <= 0 {
		return 0
	}
	if cache[n] > 0 {
		return cache[n]
	}
	max := int(math.Sqrt(float64(n)))
	count := counts(n-max*max, cache)
	for max -= 1; max > 0; max -= 1 {
		count2 := counts(n-max*max, cache)
		count = minInt(count, count2)
	}
	count += 1
	cache[n] = count
	return count
}

func numSquares(n int) int {
	cache := make([]int, n+1)
	cache[1] = 1
	return counts(n, cache)
}
