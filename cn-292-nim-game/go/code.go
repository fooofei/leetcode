package leetcode

import (
	"log"
)

// 292 https://leetcode-cn.com/problems/nim-game/

// 这道题目太模糊了 是要所有可能的情况下，
// 自己是赢的么 还是说有赢的就算赢了

// 有个测试用例不过， 才知道自己的解决方案是错误的
// 6  1 1 1 3 失败
//    1 1 2 2 失败
//    1 1 3 1 失败
//    1 2 3 成功

// 这题目太没意思了 完全考察数学

func isInCache(cache []int, n int) bool {
	return cache[n] != 0
}

func cacheAt(cache []int, n int) bool {
	if cache[n] == 1 {
		return true
	}
	return false
}

func updateCache(cache []int, n int, f bool) {
	if f {
		cache[n] = 1
	} else {
		cache[n] = 2
	}
}

// 加上 cache 不对
func nim(n int, times *int, cache []int) bool {
	if n < 4 {
		f := (*times)%2 == 0
		log.Printf("%v %v", n, f)
		return f
	}
	*times += 1
	if nim(n-1, times, cache) {
		return true
	}
	if nim(n-2, times, cache) {
		return true
	}
	if nim(n-3, times, cache) {
		return true
	}
	*times -= 1
	log.Printf("%v %v", n, false)
	return false
}

func canWinNim(n int) bool {
	if n < 4 {
		return true
	}
	//cache := make([]int, n+1)
	//times := 0
	//return nim(n, &times, cache)
	if n%4 == 0 {
		return false
	}
	return true
}
