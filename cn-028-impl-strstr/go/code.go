package code

func buildDFA(pattern []byte) [][]int {

	uniqCount := 0
	// 尽量使用多语言共有的数据结构 这里不使用 map
	uniqMap := make([]int, 0x100)
	for i := 0; i < len(pattern); i++ {
		c := pattern[i]
		if uniqMap[c] < 1 {
			uniqCount += 1
			uniqMap[c] = uniqCount
		}
	}
	matrix := make([][]int, 0x100)
	for i := range matrix {
		matrix[i] = make([]int, len(pattern))
	}
	matrix[pattern[0]][0] = 1

	x := 0 // LPS (longest prefix suffix)
	for j := 0; j < len(pattern); j++ {
		c := pattern[j]
		for k := 0; k < uniqCount; k++ {
			matrix[k][j] = matrix[k][x]
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
		if c == patternBytes[j] {
			j++
		} else {
			j = matrix[c][j]
		}
		if j >= len(patternBytes) {
			return i - len(patternBytes) + 1
		}
	}

	return -1
}
