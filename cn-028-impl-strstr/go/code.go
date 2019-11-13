package code

// 028 https://leetcode-cn.com/problems/implement-strstr/

// 这个讲的挺多，我还是看不懂
// https://www.tuhd.top/2017/06/29/2017-06-29-5%E5%AD%97%E7%AC%A6%E4%B8%B25-3%E5%AD%90%E5%AD%97%E7%AC%A6%E4%B8%B2%E6%9F%A5%E6%89%BE/

// 看不懂的点：构造出所有状态和合法的输入产生的转移，这个是一步到位的，
// 但是对于每个状态中非法的输入，该怎么转移状态 如何构造呢？

func buildDFA(pattern []byte) [][]int {
	// 尽量使用多语言共有的数据结构 这里不使用 map
	// 同样的算法也能快速应用到其他语言
	uniqMap := make([]int, 0x100)
	uniqChars := make([]byte, 0)
	for i := 0; i < len(pattern); i++ {
		c := pattern[i]
		if uniqMap[c] < 1 {
			uniqChars = append(uniqChars, c)
			uniqMap[c] = len(uniqChars)
		}
	}
	matrix := make([][]int, 0x100)
	for i := range matrix {
		matrix[i] = make([]int, len(pattern))
	}

	matrix[pattern[0]][0] = 1
	x := 0 // LPS (longest prefix suffix)
	for j := 1; j < len(pattern); j++ {
		c := pattern[j]
		for k := range uniqChars {
			uc := uniqChars[k]
			matrix[uc][j] = matrix[uc][x]
		}
		matrix[c][j] = j + 1
		x = matrix[c][x]
	}
	return matrix
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
	for i := 0; i < len(strBytes); i++ {
		c := strBytes[i]
		j = matrix[c][j]
		// 不需要写成这样
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
