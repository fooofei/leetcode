package code

// 044 https://leetcode-cn.com/problems/wildcard-matching/

// 他讲的我看明白了
// https://blog.csdn.net/maxiaotiaoti/article/details/52965116

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

// 为什么要所有格子都计算
// 为什么不存在一个前面是 false ，后面就不需要看的优化方向呢
// 比如 *b与a 不匹配 *b与ab 是匹配的，

// 代码习惯： 不使用 dp 命名数组 而使用 T
// 循环使用 len(p) len(s) 不使用 T.size()
// p 和 s 遍历顺序为 for(len(p)) { for(len(s))}

func dpMatch(s []byte, p []byte) bool {
	if len(p) < 1 {
		return len(s) == 0
	}
	// len()+1 省去判断空
	T := make([][]bool, len(p)+1)
	for i := range T {
		T[i] = make([]bool, len(s)+1)
	}
	// 第一行
	T[0][0] = true
	for i := 0; i < len(p); i++ {
		T[i+1][0] = T[i][0] && p[i] == '*'
	}
	for i := 0; i < len(p); i++ {
		for j := 0; j < len(s); j++ {
			if p[i] == '*' {
				// 匹配 0 个 或者 递归的匹配多个
				T[i+1][j+1] = T[i][j+1] || T[i+1][j]
			} else {
				T[i+1][j+1] = T[i][j] && (p[i] == '?' || p[i] == s[j])
			}
		}
	}
	return T[len(p)][len(s)]
}
