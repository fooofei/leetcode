package leetcode

// 198 https://leetcode-cn.com/problems/house-robber/

// 2 1 1 2 5 1
// .     .   .
// .   .   .

func robNext(nums []int, off int) int {
	if off >= len(nums) {
		return 0
	}
	val1 := nums[off] + robNext(nums, off+2)
	off += 1
	if off >= len(nums) {
		return val1
	}
	val2 := nums[off] + robNext(nums, off+2)

	if val1 > val2 {
		return val1
	}
	return val2
}

// time too long
func robTTL(nums []int) int {
	return robNext(nums, 0)
}

func maxInt(i, j int) int {
	if i > j {
		return i
	}
	return j
}

// 看了题目解答才知道的
func rob(nums []int) int {
	if len(nums) <= 0 {
		return 0
	}
	if len(nums) == 1 {
		return nums[0]
	}
	max := make([]int, 2)
	max[0] = nums[0]
	max[1] = nums[1]

	for i := 2; i < len(nums); i++ {
		val1 := max[0] + nums[i]
		val2 := max[1]
		max[0] = maxInt(max[0], max[1])
		max[1] = maxInt(val1, val2)
	}
	return maxInt(max[0], max[1])
}
