package leetcode

// 877 https://leetcode-cn.com/problems/stone-game/

// 动态规划之博弈问题
// https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/dong-tai-gui-hua-zhi-bo-yi-wen-ti

// 20191204  在学习了几个动态规划的例题后，看到这个题目，
// 试图使用动态规划解题 发现只能写出来递归的解决方案
// 阻塞点：1 可以在动态规划里求奇数长度数组 我一直在纠结偶数
//        2 要倒着行递推
//        3 递推公式不是比较左右边界数值的大小 而是比较最终和

func next(piles []int, takeTimes int, leftTake int, rightTake int) bool {
	if len(piles) < 1 {
		return leftTake > rightTake
	}
	l := piles[0]
	ll := piles[1:]
	r := piles[len(piles)-1]
	rr := piles[:len(piles)-1]
	if takeTimes%2 == 0 {
		if next(ll, takeTimes+1, leftTake+l, rightTake) {
			return true
		}
		return next(rr, takeTimes+1, leftTake+r, rightTake)
	} else {
		if next(ll, takeTimes+1, leftTake, rightTake+l) {
			return true
		}
		return next(rr, takeTimes+1, leftTake, rightTake+r)
	}
}

func stoneGame(piles []int) bool {
	//return next(piles, 0, 0, 0)
	return dp(piles)
}

type Score struct {
	First  int
	Second int
}

// 这个动态规划的 for 循环是倒推的 第一次见
func dp(piles []int) bool {
	if len(piles) < 1 {
		return false
	}
	if len(piles) < 2 {
		return true
	}
	T := make([][]Score, len(piles))
	for i := range T {
		T[i] = make([]Score, len(piles))
	}
	for i := 0; i < len(piles); i++ {
		T[i][i].First = piles[i]
	}
	for i := len(piles) - 1; i > -1; i-- {
		for j := i + 1; j < len(piles); j++ {
			// 注意递推公式不是比较 i j 两个索引值的大小
			vi := piles[i] + T[i+1][j].Second
			vj := piles[j] + T[i][j-1].Second
			if vi > vj {
				T[i][j].First = vi
				T[i][j].Second = T[i+1][j].First
			} else {
				T[i][j].First = vj
				T[i][j].Second = T[i][j-1].First
			}
		}
	}
	s := &T[0][len(piles)-1]
	return s.First > s.Second
}