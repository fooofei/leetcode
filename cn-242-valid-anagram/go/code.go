package leetcode

// 242 https://leetcode-cn.com/problems/valid-anagram/

// 字母异位词: 两个单词包含相同的字母，但是次序不同
//

func extract(s []byte) ([]int, []byte) {
	countMap := make([]int, 0x100)
	uniqChar := make([]byte, len(s))

	for _, c := range s {
		if countMap[c] == 0 {
			uniqChar = append(uniqChar, c)
		}
		countMap[c] += 1
	}
	return countMap, uniqChar
}

func isAnagram(s string, t string) bool {
	sCountMap, sUniq := extract([]byte(s))
	tCountMap, tUniq := extract([]byte(t))
	if len(sUniq) != len(tUniq) {
		return false
	}
	if len(sUniq) == 0 {
		return true
	}
	for _, c := range sUniq {
		if sCountMap[c] != tCountMap[c] {
			return false
		}
	}
	return true
}
