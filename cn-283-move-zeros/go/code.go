package leetcode

// 283 https://leetcode-cn.com/problems/move-zeroes/

// 有点类似把数组看作是栈的技巧

func moveZeroes(nums []int) {
	idx := 0
	for _, n := range nums {
		if n != 0 {
			nums[idx] = n
			idx += 1
		}
	}
	for ; idx < len(nums); idx++ {
		nums[idx] = 0
	}
}
