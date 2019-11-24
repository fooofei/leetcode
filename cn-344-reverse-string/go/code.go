package leetcode

// 344 https://leetcode-cn.com/problems/reverse-string/

func reverseString(s []byte) {
	if len(s) < 1 {
		return
	}
	i := 0
	j := len(s) - 1
	for i < j {
		s[i], s[j] = s[j], s[i]
		i++
		j--
	}
}
