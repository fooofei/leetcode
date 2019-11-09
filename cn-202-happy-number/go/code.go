package leetcode

// 202 https://leetcode-cn.com/problems/happy-number/

func isHappy(n int) bool {
	if n < 2 {
		return true
	}
	last := n
	for {
		sum := 0
		for last > 0 {
			sum += (last % 10) * (last % 10)
			last = last / 10
		}
		if sum <= 1 {
			return true
		}
		if sum == 4 || sum == 9 {
			break
		}
		last = sum
	}
	return false
}
