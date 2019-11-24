package leetcode

// 345 https://leetcode-cn.com/problems/reverse-vowels-of-a-string/

// 判断是否是元音字母
// 大写字母也算
func isVowel(c byte) bool {
	switch c {
	case 'a', 'e', 'i', 'o', 'u':
		return true
	case 'A','E','I','O','U':
		return true
	default:
		return false
	}
}

func reverseVowels(s string) string {
	indexs := make([]int, 0)
	sBytes := []byte(s)
	for i, c := range sBytes {
		if isVowel(c) {
			indexs = append(indexs, i)
		}
	}
	if len(indexs) < 1 {
		return s
	}
	i := 0
	j := len(indexs) - 1
	for i < j {
		sBytes[indexs[i]], sBytes[indexs[j]] =
			sBytes[indexs[j]], sBytes[indexs[i]]
		i++
		j--
	}
	return string(sBytes)
}
