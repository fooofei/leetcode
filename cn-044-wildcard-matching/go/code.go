package code

// 044 https://leetcode-cn.com/problems/wildcard-matching/

// Test9 Time too long
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
		// 为什么是多余的，因为 match(s[1:], p) 递归进去后，也会判断 s[1:] p[1:]
		//if match(s[1:], p[1:]) {
		//	return true
		//}
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
	return dpMatch([]byte(s), []byte(p))
}

// 怎么理解呢
func dpMatch(s []byte, p []byte) bool {
	// len()+1 省去判断空
	dp := make([][]bool, len(s)+1)
	for i := range dp {
		dp[i] = make([]bool, len(p)+1)
	}
	dp[0][0] = true
	for j := 0; j < len(p); j++ {
		dp[0][j+1] = dp[0][j] && p[j] == '*'
	}
	for i := 0; i < len(s); i++ {
		for j := 0; j < len(p); j++ {
			if p[j] == '*' {
				dp[i+1][j+1] = dp[i+1][j] || dp[i][j+1]
			} else if p[j] == '?' || p[j] == s[i] {
				dp[i+1][j+1] = dp[i][j]
			}
		}
	}
	return dp[len(s)][len(p)]
}
