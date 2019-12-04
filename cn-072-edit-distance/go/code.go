package leetcode

import "fmt"

// 072 https://leetcode-cn.com/problems/edit-distance/

func minDistance(word1 string, word2 string) int {
	s := word1
	p := word2
	// s-> p
	T := make([][]int, len(s)+1)
	for i := range T {
		T[i] = make([]int, len(p)+1)
	}
	// 第一行
	for j := 0; j < len(p); j++ {
		T[0][j+1] = j + 1
	}
	// 第一列
	for i := 0; i < len(s); i++ {
		T[i+1][0] = i + 1
	}
	for i := 0; i < len(s); i++ {
		for j := 0; j < len(p); j++ {
			if s[i] == p[j] {
				T[i+1][j+1] = T[i][j]
			} else {
				T[i+1][j+1] = minInts(T[i][j], T[i+1][j], T[i][j+1]) + 1
			}
		}
	}
	return T[len(s)][len(p)]
}

func minInts(nums ...int) int {
	a := nums[0]
	for i := 1; i < len(nums); i++ {
		if nums[i] < a {
			a = nums[i]
		}
	}
	return a
}

func dump(T [][]int, s, p string) {
	fmt.Printf("   |")
	fmt.Printf("%2v |", "\"\"")
	for i := 0; i < len(p); i++ {
		fmt.Printf("%2v |", string(p[i]))
	}
	fmt.Printf("\n")
	sb := []byte(s)
	sb = append([]byte{'"'}, sb...)
	for i := 0; i < len(T); i++ {
		fmt.Printf("%2v |", string(sb[i]))
		for j := 0; j < len(T[i]); j++ {
			fmt.Printf("%2v |", T[i][j])
		}
		fmt.Printf("\n")
	}
	fmt.Printf("\n")
}
