package leetcode

// 263 https://leetcode-cn.com/problems/ugly-number/

// 丑数就是只包含质因数 2, 3, 5 的正整数。
// 质因数是什么：因数是质数
func isUgly(num int) bool {
	if num < 1 {
		return false
	}
	if num < 6 {
		return true
	}
	for num > 0 && num % 5 == 0 {
		num = num / 5
	}
	for num > 0 && num % 3 == 0 {
		num = num / 3
	}
	for num > 0 && num % 2 == 0 {
		num = num / 2
	}
	return num == 1
}