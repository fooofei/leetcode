package leetcode

// 205 https://leetcode-cn.com/problems/isomorphic-strings/
// 同构字符串

func isIsomorphicNext(s string, t string) bool {
	if len(s) != len(t) {
		return false
	}
	mapChars := make([]byte, 0x100)
	_ = mapChars
	sbs := []byte(s)
	tbs := []byte(t)
	for index, c := range sbs {
		ic := int(c)
		if mapChars[ic] == 0 {
			mapChars[ic] = tbs[index]
		} else if mapChars[ic] != tbs[index] {
			return false
		}
	}
	return true
}

// 错误点： 两个字符串的位置互换 是我没想到的
func isIsomorphic2(s string, t string) bool {
	return isIsomorphicNext(s, t) && isIsomorphicNext(t, s)
}

func isIsomorphic(s string, t string) bool {
	if len(s) != len(t) {
		return false
	}
	sbs := []byte(s)
	tbs := []byte(t)

	sMap := make([]int, 0x100)
	tMap := make([]int, 0x100)
	for i := range sMap {
		sMap[i] = -1
	}
	for i := range tMap {
		tMap[i] = -1
	}
	for index, c := range sbs {
		if sMap[int(c)] != tMap[int(tbs[index])] {
			return false
		}
		if sMap[int(c)] < 0 {
			sMap[int(c)] = index
			tMap[int(tbs[index])] = index
		}
	}
	return true
}
