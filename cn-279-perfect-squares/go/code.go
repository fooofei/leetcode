package leetcode

import (
	"math"
)

// 279 https://leetcode-cn.com/problems/perfect-squares/

// 题目解答里也是这种遍历

func minInts(nums ...int) int {
	a := nums[0]
	for i := 1; i < len(nums); i++ {
		if nums[i] < a {
			a = nums[i]
		}
	}
	return a
}

func dp(n int) int {
	T := make([]int, n+1)
	T[1] = 1
	for i := 2; i < n+1; i++ {
		max := int(math.Sqrt(float64(i)))
		min := i + 2
		for ; max > 0; max -= 1 {
			j := i - max*max
			if j < 1 {
				min = minInts(min, 1)
			} else {
				min = minInts(min, T[i-max*max]+1)
			}
		}
		T[i] = min
	}
	return T[n]
}

func numSquares(n int) int {
	//cache := make([]int, n+1)
	//cache[1] = 1
	//return counts(n, cache)
	return dp(n)
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
		count = minInts(count, count2)
	}
	count += 1
	cache[n] = count
	return count
}