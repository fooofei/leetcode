package code

import (
	"fmt"
)

// 028 https://leetcode-cn.com/problems/implement-strstr/

// 这个讲的挺多，我还是看不懂
// https://www.tuhd.top/2017/06/29/2017-06-29-5%E5%AD%97%E7%AC%A6%E4%B8%B25-3%E5%AD%90%E5%AD%97%E7%AC%A6%E4%B8%B2%E6%9F%A5%E6%89%BE/

// 看不懂的点：构造出所有状态和合法的输入产生的转移，这个是一步到位的，
// 但是对于每个状态中非法的输入，该怎么转移状态 如何构造呢？

// 从这里受到启示
// https://www.zhihu.com/question/24382751

// 第一类字符：不在 pattern 里出现的，状态转移一定是到 0 ，初始态就行了
// 第二类字符：在 pattern 里出现，但是不是有效转移的，求最大前缀
// 第三类字符：在 pattern 里出现，有效转移的，状态往后转移就行了

// 按照三类字符理解 DFA 矩阵会陷入僵局，和复杂
// 应该这样理解:
// 第一类是正反馈(有效)转移状态，从 0 状态，依次输入所有字符，得到的状态转移
// 到终结状态时即满足字符匹配 对应到代码就是 matrix[c][j] = j + 1
// 第二类是当遇到不匹配字符时, 应该转移到哪里，假设遇到 j 时不匹配，
// 则在构造 DFA 的过程中，前面的 DFA 状态转移已经构造好了，我们可以直接拿来用
// 我们现在的处境是 [0,j-1] 都是匹配的，j 发生不匹配，
// 则按照朴素比较的处理逻辑应该是模式串向后移动一位，
// 跟上一句结合起来就是要重新匹配 [1,j-1] ，
// 因为我们现在 DFA 是 j 状态前面的部分已经构建好了
// 因此可以直接拿来使用，就是 DFA 状态转化从 0 状态开始依次输入 [i,j-1] 个输入
// 把这个作为 X，然后 dfa[p[j]][x] 就是 j 不匹配时应该转到到下一个状态
// 到这里理解就通畅了

// 这里以动态规划的解决方案把 KMP 讲一遍
// https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/dong-tai-gui-hua-zhi-kmp-zi-fu-pi-pei-suan-fa

func buildDFA(pat []byte) [][]int {
	// 尽量使用多语言共有的数据结构 这里不使用 map
	// 同样的算法也能快速应用到其他语言
	uniqMap := make([]int, 0x100)
	// 不使用 uniqChars 就会导致有一层循环是 for (<255) 循环量加大 其实没必要这么大
	uniqChars := make([]byte, 0)
	for _, c := range pat {
		if uniqMap[c] < 1 {
			uniqChars = append(uniqChars, c)
			uniqMap[c] = len(uniqChars) + 1
		}
	}
	T := make([][]int, 0x100)
	for i := range T {
		T[i] = make([]int, len(pat))
	}
	T[pat[0]][0] = 1
	LPS := 0 // longest prefix suffix)
	for j := 1; j < len(pat); j++ {
		c := pat[j]
		for _, uc := range uniqChars {
			// x 代表 [1,j] 之间字符的状态转移到 x
			T[uc][j] = T[uc][LPS]
		}
		// 这里会覆盖上面 for 循环提前的赋值
		T[c][j] = j + 1
		LPS = T[c][LPS]
	}
	return T
}

func strStr(str string, pattern string) int {
	strBytes := []byte(str)
	patternBytes := []byte(pattern)
	if len(patternBytes) == 0 {
		return 0
	}
	if len(strBytes) == 0 {
		return -1
	}
	matrix := buildDFA(patternBytes)
	j := 0
	for i,c := range strBytes {
		j = matrix[c][j]
		// 不需要写成这样 在自动机里如果匹配， j 自然 +1
		//if c == patternBytes[j] {
		//	j++
		//} else {
		//	j = matrix[c][j]
		//}
		if j >= len(patternBytes) {
			return i - len(patternBytes) + 1
		}
	}
	return -1
}

func dumpMatrix(matrix [][]int, columnSize int, chars []byte, prefix string) {
	fmt.Printf("%v\n", prefix)
	for i := range chars {
		for j := 0; j < columnSize; j++ {
			fmt.Printf("%v ", matrix[int(chars[i])][j])
		}
		fmt.Printf("\n")
	}
	fmt.Printf("\n")
}
