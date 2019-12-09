package leetcode

// 132 https://leetcode-cn.com/problems/palindrome-partitioning-ii/

// 在学习过 1278 这道题目系列的3 后写了这道题目
// 第一次尝试 AC 了, 但是时间比较长
// 执行用时 :
//1124 ms
//, 在所有 golang 提交中击败了
//5.00%
//的用户
//内存消耗 :
//7.3 MB
//, 在所有 golang 提交中击败了
//100.00%
//的用户

func isPalindRome(s string, i, j int) bool {
	for i < j {
		if s[i] != s[j] {
			return false
		}
		i += 1
		j -= 1
	}
	return true
}

// 某个区间是否是回文
func palindromeCache(s string) [][]bool {
	N := len(s)
	T := make([][]bool, N)
	for i := range T {
		T[i] = make([]bool, N)
	}
	for i := 0; i < len(T); i++ {
		T[i][i] = true
	}
	// first row
	for j := 1; j < len(T); j++ {
		T[0][j] = isPalindRome(s, 0, j)
	}
	// end col
	endCol := len(T) - 1
	for i := 1; i < len(T)-1; i++ {
		T[i][endCol] = isPalindRome(s, i, endCol)
	}
	for i := len(T) - 2; i > -1; i-- {
		T[i][i+1] = isPalindRome(s, i, i+1)
		for j := i + 2; j < endCol; j++ {
			T[i][j] = T[i+1][j-1] && s[i] == s[j]
		}
	}
	return T
}

// 矩阵是 [][]bool
// i 是切割次数
// j 是 [0,j] 的子串
// 矩阵含义是 [0,j] 的子串切割 i 次，是否能成功
func minCut1(s string) int {
	N := len(s)
	T := make([][]bool, N)
	for i := range T {
		T[i] = make([]bool, N)
	}
	rome := palindromeCache(s)
	// N most use N-1 cut
	// first col
	for i := 0; i < len(T); i++ {
		T[i][0] = true
	}
	// first row
	for j := 1; j < len(T); j++ {
		T[0][j] = rome[0][j]
	}
	for i := 1; i < len(T); i++ {
		for j := 1; j < len(T); j++ {
			findCut := false
			for k := 0; k < j; k++ {
				findCut = T[i-1][k] && rome[k+1][j]
				if findCut {
					break
				}
			}
			T[i][j] = findCut
		}
	}
	endCol := len(T) - 1
	for i := 0; i < len(T); i++ {
		if T[i][endCol] {
			return i
		}
	}
	// doesn't matter
	return -1
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

// 这个版本耗时 8ms 与 Huahua 解决方案耗时相同
// 矩阵是 []int
// 含义是 [0,i] 子串的最小切割数
func minCut(s string) int {
	N := len(s)
	T := make([]int, N)
	rome := palindromeCache(s)
	for i := 1; i < len(T); i++ {
		if rome[0][i] {
			T[i] = 0
			continue
		}
		min := T[i-1] + 1
		for j := 0; j < i; j++ {
			if rome[j+1][i] {
				min = minInts(min, T[j]+1)
			}
		}
		T[i] = min
	}
	return T[N-1]
}
