package leetcode

// 258 https://leetcode-cn.com/problems/add-digits/

// 38 = 2
// 40 = 4
// 19 = 1
// 99 = 9
// 98 = 8
// 55 = 1
func addDigits(num int) int {
	if num < 0 {
		return 0
	}
	for num > 9 {
		tmp := num
		num = 0
		for tmp > 0 {
			num += tmp % 10
			tmp = tmp / 10
		}
	}
	return num
}

// num = 1000*a + 100*b + 10*c + d
// num2 = a+b+c+d
// num-num2 = 999*a + 99*b + 9*c
//          =9 * (111*a + 11*b + c)
// 这个值必定是 9 的倍数
// 因此 num % 9 剩下的就是所求
