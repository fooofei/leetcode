package leetcode

// 387 https://leetcode-cn.com/problems/first-unique-character-in-a-string/

func firstUniqChar(s string) int {
	sBytes := []byte(s)
	countMap := make([]int, 0x100)
	for _, c := range sBytes {
		countMap[c] += 1
	}
	for i, c := range sBytes {
		if countMap[c] == 1 {
			return i
		}
	}
	return -1
}
