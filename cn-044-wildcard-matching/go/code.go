package code

// 044 https://leetcode-cn.com/problems/wildcard-matching/

func match(s []byte, p []byte) bool {
	if len(p) == 0 {
		return len(s) == 0
	}
	// 优化：消除连续的 *
	for p[0] == '*' && len(p) > 1 && p[1] == '*' {
		p = p[1:]
	}
	if p[0] == '*' {
		if match(s, p[1:]) {
			return true
		}
		if len(s) == 0 {
			return false
		}
		if match(s[1:], p[1:]) {
			return true
		}
		return match(s[1:], p)
	}
	if len(s) == 0 {
		return false
	}
	if p[0] == '?' {
		return match(s[1:], p[1:])
	}
	if p[0] != s[0] {
		return false
	}
	return match(s[1:], p[1:])
}

func isMatch(s string, p string) bool {
	return match([]byte(s), []byte(p))
}
