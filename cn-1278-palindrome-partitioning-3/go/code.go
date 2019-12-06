package leetcode

import (
	"fmt"
)

// 1278 https://leetcode-cn.com/problems/palindrome-partitioning-iii/

// 先看了一眼资料，知道使用动态规划了
// 然后画出矩阵，先把明显的有结果的标注出来 然后把已经标注出来的挨着的没标注的 思考
// 怎么从已经标注的得到未标注的 就得到递推公式了

// 总算是在动态规划上前进一点了

func minInts(nums ...int) int {
	a := nums[0]
	for i := 1; i < len(nums); i++ {
		if nums[i] < a {
			a = nums[i]
		}
	}
	return a
}

func bool2int(b bool) int {
	if b {
		return 1
	}
	return 0
}

func makeCost(s string) [][]int {
	N := len(s)
	T := make([][]int, N)
	for i := range T {
		T[i] = make([]int, N)
	}
	for i := N - 2; i > -1; i-- {
		for j := i + 1; j < N; j++ {
			T[i][j] = T[i+1][j-1] + bool2int(s[i] != s[j])
		}
	}
	return T
}

func palindromePartition(s string, k int) int {
	if len(s) < 2 {
		return 0
	}
	if k < 1 {
		return 0
	}
	N := len(s)
	// pre return result
	if k >= N {
		return 0
	}
	T := make([][]int, N+1)
	for i := range T {
		T[i] = make([]int, N)
	}
	costT := makeCost(s)
	for j := 1; j < N; j++ {
		T[1][j] = costT[0][j]
	}
	// pre return result
	if k == 1 {
		return T[1][N-1]
	}
	for i := 2; i <= N; i++ {
		for j := i; j < N; j++ {
			minCost := T[i-1][j-1]
			for k := 1; k < j; k++ {
				v1 := T[i-1][k-1] + costT[k][j]
				minCost = minInts(minCost, v1)
			}
			T[i][j] = minCost
		}
	}
	k = minInts(k, N)
	return T[k][N-1]
}

// s[i,j] 变为回文的修改次数
// 使用 cost 缓存 加速
// cost 区间计算也存在重叠子问题
func cost(s string, i, j int) int {
	ret := 0
	for i < j {
		if s[i] != s[j] {
			ret += 1
		}
		i += 1
		j -= 1
	}
	return ret
}

func dump(T [][]int, s string) {
	fmt.Printf("%3v |", "")
	for i := 0; i < len(s); i++ {
		fmt.Printf("%3v |", string(s[i]))
	}
	fmt.Printf("\n")
	fmt.Printf("%3v |", "")
	for i := 0; i < len(s); i++ {
		fmt.Printf("%3v |", i)
	}
	fmt.Printf("\n")
	for i := 0; i < len(T); i++ {
		fmt.Printf("%3v |", i)
		for j := 0; j < len(T[i]); j++ {
			fmt.Printf("%3v |", T[i][j])
		}
		fmt.Printf("\n")
	}
	fmt.Printf("\n")
}
