package nqueens

import (
	"math"
)

//
// 最一般的方法
// 递归逻辑：
//    从 0,1,2，... 行开始算起，每一行都在哪一列放置皇后
//

func isNeighbor(row0, col0, row1, col1 int) bool {
	// 肯定不在同一行
	// 是否在同一列需要判断
	if col0 == col1 {
		return true
	}

	// 是否在对角线
	x := int(math.Abs(float64(row0 - row1)))
	y := int(math.Abs(float64(col0 - col1)))
	return x == y
}

// 对已经放置的所有皇后进行冲突对比
func anyNeighbor(locate []int, maxRow int, curCol int) bool {
	for row := 0; row < maxRow; row++ {
		if isNeighbor(row, locate[row], maxRow, curCol) {
			return true
		}
	}
	return false
}

// locate 每一行的皇后放在了哪一列
func trace(locate []int, row int) int {

	maxRow := len(locate)
	maxCol := len(locate)

	if row >= maxRow {
		return 1
	}
	r := 0
	for i := 0; i < maxCol; i++ {
		// 判断 即将摆放的 [row, i] 是否有 neighbor
		if !anyNeighbor(locate, row, i) {
			locate[row] = i
			r += trace(locate, row+1)
			// 是否清除足迹 对结果没影响
			locate[row] = -1
		}
	}
	return r
}

func Sum(nq int) int {

	array := make([]int, nq)
	for i, _ := range array {
		array[i] = -1
	}
	return trace(array, 0)
}
