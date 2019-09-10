package nqueens

import (
	prmt "github.com/gitchander/permutation"
)

func isValid(cols []int, N int, leftDown, rightDown []int) bool {
	// 已经保证同行 同列不存在冲突
	// 只计算对角线的就可以了
	for row, col := range cols {
		v0 := &leftDown[row+col]
		v1 := &rightDown[row-col+N]
		if *v0 != 0 || *v1 != 0 {
			return false
		}
		*v0 = 1
		*v1 = 1
	}
	return true
}

func zeroSlice(a []int) {
	for i := 0; i < len(a); i++ {
		a[i] = 0
	}
}

func Sum(N int) int {

	// 对角线参考 multi-array 目录
	allCols := make([]int, N)
	for i := 0; i < N; i++ {
		allCols[i] = i
	}
	leftDown := make([]int, 2*N)
	rightDown := make([]int, 2*N)
	per := prmt.New(prmt.IntSlice(allCols))
	r := 0

	for per.Next() {
		zeroSlice(leftDown)
		zeroSlice(rightDown)
		if isValid(allCols, N, leftDown, rightDown) {
			r += 1
		}
	}
	return r
}

// 太长了
// allPerCount = 24 of 4
//allPerCount = 120 of 5
//allPerCount = 720 of 6
//allPerCount = 5040 of 7
//allPerCount = 40320 of 8
//allPerCount = 362880 of 9
//allPerCount = 3628800 of 10
//allPerCount = 39916800 of 11
//allPerCount = 479001600 of 12
//allPerCount = 6227020800 of 13
