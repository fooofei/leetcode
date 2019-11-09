package leetcode

// 191 https://leetcode-cn.com/problems/number-of-1-bits/

func hammingWeight(num uint32) int {

	var ret int
	for num > 0 {
		if num&0x01 == 1 {
			ret += 1
		}
		num = num >> 1
	}
	return ret
}
