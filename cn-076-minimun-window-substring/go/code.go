package leetcode

// 076 https://leetcode-cn.com/problems/minimum-window-substring/

// 这道题目模糊的真是可以 我又理解错误了
// 要 pattern 中的所有字符都出现在 s 中，包括重复的

func makePatMap(t string) []int {
	m := make([]int, 0x100)
	for i := 0; i < len(t); i++ {
		c := byte(t[i])
		m[c] += 1
	}
	return m
}

func subOf(s string, off, size int) string {
	sub := make([]byte, 0, size+1)
	for i := off; i < off+size && i < len(s); i++ {
		sub = append(sub, byte(s[i]))
	}
	return string(sub)
}

func minWindow(s string, t string) string {
	left := 0
	right := 0
	minStringLen := len(s) + 1
	start := 0
	patMap := makePatMap(t)
	allNonCount := len(t)
	m := make([]int, 0x100)

	for left < len(s) && right <= len(s) {
		// already all pattern in window
		for allNonCount < 1 {
			if right-left < minStringLen {
				start = left
				minStringLen = right - left
			}
			leftCh := s[left]
			if m[leftCh] > 0 {
				m[leftCh] -= 1
				if m[leftCh] < patMap[leftCh] {
					allNonCount += 1
				}
			}
			left += 1
		}
		if right >= len(s) {
			break
		}
		// push to window
		rightCh := s[right]
		if patMap[rightCh] > 0 {
			if m[rightCh] < patMap[rightCh] {
				allNonCount -= 1
			}
			m[rightCh] += 1
		}
		right += 1
	}
	if minStringLen > len(s) {
		return ""
	}
	if start+minStringLen > len(s) {
		return ""
	}
	return subOf(s, start, minStringLen)
}
