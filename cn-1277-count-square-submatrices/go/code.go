package leetcode

import (
	"fmt"
)

// 1277 https://leetcode-cn.com/problems/count-square-submatrices-with-all-ones/

// 纠结死了 我得到了结论是 T[i][j] = T[i-1][j] + T[i][j-1] - T[i-1][j-1] +
//   以当前格子为结尾 长度1的个数 长度2的个数 长度3的个数 ...  不知道这个怎么得来

// 看来是动态规划状态我找错定位了

func countSquares(matrix [][]int) int {
	N := len(matrix)
	if N < 1 {
		return 0
	}
	M := len(matrix[0])
	if M < 1 {
		return 0
	}
	T := make([][]int, N)
	for i := range T {
		T[i] = make([]int, M)
	}
	sum := 0
	T[0][0] = matrix[0][0]
	sum += T[0][0]
	for i := 1; i < N; i++ {
		T[i][0] = matrix[i][0]
		sum += T[i][0]
	}
	for j := 1; j < M; j++ {
		T[0][j] = matrix[0][j]
		sum += T[0][j]
	}
	for i := 1; i < N; i++ {
		for j := 1; j < M; j++ {
			if matrix[i][j] == 1 {
				T[i][j] = minInts(T[i-1][j], T[i][j-1], T[i-1][j-1]) + 1
				sum += T[i][j]
			}
		}
	}
	//dump(T, matrix)
	return sum
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

func dump(T [][]int, matrix [][]int) {
	f := func(A [][]int) {
		fmt.Printf("%3v |", "")
		for i := 0; i < len(A[0]); i++ {
			fmt.Printf("%3v |", i)
		}
		fmt.Printf("\n")
		for i := 0; i < len(A); i++ {
			fmt.Printf("%3v |", i)
			for j := 0; j < len(A[i]); j++ {
				fmt.Printf("%3v |", A[i][j])
			}
			fmt.Printf("\n")
		}
		fmt.Printf("\n")
	}
	f(matrix)
	fmt.Printf("------------------------\n\n")
	f(T)
}
