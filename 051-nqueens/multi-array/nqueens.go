package nqueens

func trace(colLocate, rightUp, leftUp, queen []int, row int) int {

	N := len(queen) - 1
	if row > N {
		return 1
	}
	r := 0
	for col := 1; col <= N; col++ {
		v0 := &colLocate[col]
		v1 := &rightUp[row+col]
		v2 := &leftUp[row-col+N]
		if *v0 == 0 && *v1 == 0 && *v2 == 0 {
			*v0 = 1
			*v1 = 1
			*v2 = 1
			r += trace(colLocate, rightUp, leftUp, queen, row+1)
			*v0 = 0
			*v1 = 0
			*v2 = 0
		}

	}
	return r
}

func Sum(N int) int {

	colLocate := make([]int, N+1)
	rightUp := make([]int, 2*N+1)
	leftUp := make([]int, 2*N+1)
	queen := make([]int, N+1)
	return trace(colLocate, rightUp, leftUp, queen, 1)
}
