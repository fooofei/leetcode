package leetcode

import (
	"sort"
)

// 290 https://leetcode-cn.com/problems/word-pattern/

func hashStr(target []byte, first, end int) uint64 {
	var h uint64
	for i := first; i < end; i++ {
		h += uint64(target[i] * 233)
	}
	return h
}

func wordPattern(pattern string, str string) bool {
	hashMap := make([]uint64, 0x100)
	strBytes := []byte(str)
	pattBytes := []byte(pattern)
	nextWord := 0
	for _, p := range pattBytes {
		f := nextWord
		for ; nextWord < len(strBytes) && strBytes[nextWord] != ' '; nextWord++ {
		}
		if nextWord <= f {
			return false
		}
		h := hashStr(strBytes, f, nextWord)
		if hashMap[p] == 0 {
			hashMap[p] = h
		} else if hashMap[p] != h {
			return false
		}
		nextWord += 1
	}
	if nextWord < len(strBytes) {
		return false
	}
	// 上面只验证了 以 pattern 为基准 str 符合要求
	// 但是 str 中的重复对应没校验出来
	// 比如 abba 对应 dog dog dog dog 没校验出来
	hashs := make([]uint64, 0)
	for _, h := range hashMap {
		if h != 0 {
			hashs = append(hashs, h)
		}
	}
	sort.Slice(hashs, func(i, j int) bool {
		return hashs[i] < hashs[j]
	})
	// uniq 找到重复的就报错
	if len(hashs) > 0 {
		last := hashs[0]
		for i := 1; i < len(hashs); i++ {
			if hashs[i] == last {
				return false
			}
			last = hashs[i]
		}
	}
	return true
}
