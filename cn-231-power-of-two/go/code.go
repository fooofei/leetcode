package leetcode

// 231 https://leetcode-cn.com/problems/power-of-two/

func isPowerOfTwo(n int) bool {
	if n < 1 {
		return false
	}
	return n & (n-1) == 0
}
