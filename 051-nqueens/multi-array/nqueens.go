package nqueens

// 跟位数组的解决方案理解起来很像
//
//
//  0  1  2  3  4  5  6  7
//  1  2  3  4  5  6  7  8
//  2  3  4  5  6  7  8  9
//  3  4  5  6  7  8  9  10
//  4  5  6  7  8  9  10 11
//  5  6  7  8  9  10 11 12
//  6  7  8  9  10 11 12 13
//  7  8  9  10 11 12 13 14

//  8  7  6  5  4  3  2  1
//  9  8  7  6  5  4  3  2
//  10 9  8  7  6  5  4  3
//  11 10 9  8  7  6  5  4
//  12 11 10 9  8  7  6  5
//  13 12 11 10 9  8  7  6
//  14 13 12 11 10 9  8  7
//  15 14 13 12 11 10 9  8

// 根据上面的阵列图
// 同一列的判定，就是判断 col[col] 就行了
// 左下对角线方向 row+col 都是一个数字，因此 col[row+col] 设置好以后，
//    直接应用到下一层递归
// 右对角线方向 row-col+N 是同一个数字，因此 col[row-col+N] 设置好以后，
//   直接应用到下一层递归

func trace(col, leftDown, rightDown []int, row, maxRow int) int {

	if row >= maxRow {
		return 1
	}
	r := 0
	for c := 0; c < maxRow; c++ {
		v0 := &col[c]
		v1 := &leftDown[row+c]
		v2 := &rightDown[row-c+maxRow]
		if *v0 == 0 && *v1 == 0 && *v2 == 0 {
			*v0 = 1
			*v1 = 1
			*v2 = 1
			r += trace(col, leftDown, rightDown, row+1, maxRow)
			*v0 = 0
			*v1 = 0
			*v2 = 0
		}

	}
	return r
}

func Sum(N int) int {

	col := make([]int, N)
	left := make([]int, 2*N)
	right := make([]int, 2*N)
	return trace(col, left, right, 0, N)
}
