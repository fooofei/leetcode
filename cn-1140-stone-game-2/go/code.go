package leetcode

import (
	"fmt"
)

// 1140 https://leetcode-cn.com/problems/stone-game-ii/

func maxInts(nums ...int) int {
	a := nums[0]
	for i := 1; i < len(nums); i++ {
		if nums[i] > a {
			a = nums[i]
		}
	}
	return a
}

// 学习了这里
// https://leetcode.com/problems/stone-game-ii/discuss/345404/Simple-DP-Solution-clean-Code
func dp(piles []int) int {
	T := make([][]int, len(piles)+1)
	for i := range T {
		T[i] = make([]int, len(piles)+1)
	}
	// sum of [i,end)
	sums := make([]int, len(piles)+1)
	for i := len(piles) - 1; i > -1; i-- {
		sums[i] = piles[i] + sums[i+1]
	}
	// alex can get from [i,end) with M=len(piles)
	for i := 0; i < len(piles); i++ {
		T[i][len(piles)] = sums[i]
	}
	// 可有可无
	//tail := piles[len(piles)-1]
	//for j:=1; j< len(piles); j++ {
	//	T[len(piles)-1][j] = tail
	//}

	for i := len(piles) - 1; i > -1; i-- {
		for j := len(piles) - 1; j > -1; j-- {
			max := T[i][j]
			for x := 1; x <= 2*j && i+x <= len(piles); x++ {
				v1 := maxInts(x, j)
				max = maxInts(max, sums[i]-T[i+x][v1])
			}
			T[i][j] = max
		}
	}
	return T[0][1]
}

func stoneGameII(piles []int) int {
	return dp(piles)
}

// x 从 j 开始会导致这样
//    |  0 |  1 |  2 |  3 |  4 |  5 |  6 |
//  1 |115 |104 |115 |115 |115 |115 |115 |
//  2 |114 | 11 |114 |114 |114 |114 |114 |
//  3 |112 |103 |112 |112 |112 |  0 |112 |
//  4 |109 |  9 |109 |109 |  0 |  0 |109 |
//  5 |105 |105 |105 |  0 |  0 |  0 |105 |
//100 |100 |100 |100 |100 |100 |100 |100 |
//  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |

// 预期这样
//    |  0 |  1 |  2 |  3 |  4 |  5 |  6 |
//  1 |  0 |104 |101 |115 |115 |115 |115 |
//  2 |  0 | 11 | 14 |114 |114 |114 |114 |
//  3 |  0 |103 |112 |112 |112 |112 |112 |
//  4 |  0 |  9 |109 |109 |109 |109 |109 |
//  5 |  0 |105 |105 |105 |105 |105 |105 |
//100 |  0 |100 |100 |100 |100 |100 |100 |
//  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |

func dump(T [][]int, piles []int) {
	fmt.Printf("%3v |", "")
	for i := 0; i < len(piles)+1; i++ {
		fmt.Printf("%3v |", i)
	}
	fmt.Printf("\n")
	piles = append(piles, 0)
	for i := 0; i < len(T); i++ {
		fmt.Printf("%3v |", piles[i])
		for j := 0; j < len(T[i]); j++ {
			fmt.Printf("%3v |", T[i][j])
		}
		fmt.Printf("\n")
	}
	fmt.Printf("\n")
}
