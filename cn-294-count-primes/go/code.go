package leetcode

import (
	"math"
)

// 204 https://leetcode-cn.com/problems/count-primes/

// 学习 https://blog.csdn.net/afei__/article/details/80638460
// 如何更有效的辨别一个数是不是质数
func isPrime(n int) bool {
	if n == 2 {
		return true
	}
	if n == 3 {
		return true
	}
	if n%6 != 5 && n%6 != 1 {
		return false
	}
	square := math.Sqrt(float64((n)))
	for i := 5; i <= int(square); i += 6 {
		if n%i == 0 {
			return false
		}
		if n%(i+2) == 0 {
			return false
		}
	}
	return true
}

func countPrimes1(n int) int {
	if n < 3 {
		return 0
	}
	if n == 3 {
		return 1
	}
	count := 2
	for i := 4; i < n; i++ {
		if isPrime(i) {
			count += 1
		}
	}
	return count
}

// 时间上并没有快
func countPrimes(n int) int {
	if n < 3 {
		return 0
	}
	if n == 3 {
		return 1
	}
	// 0 = true 1 = false
	arrays := make([]byte, n)
	for i := 2; i < n; i++ {
		if !isPrime(i) {
			arrays[i] = 1
		} else {
			for j := i * i; j < n; j += i {
				arrays[j] = 1
			}
		}
	}
	count := n - 2
	for i := 2; i < n; i++ {
		count -= int(arrays[i])
	}
	return count
}
