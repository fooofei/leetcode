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

func maxInts(nums ...int) int {
	a := nums[0]
	for i := 1; i < len(nums); i++ {
		if nums[i] > a {
			a = nums[i]
		}
	}
	return a
}

// 看了题目解答才知道的
func rob1(nums []int) int {
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
		max[0] = maxInts(max[0], max[1])
		max[1] = maxInts(val1, val2)
	}
	return maxInts(max[0], max[1])
}

// 别想着像上面的解决方案那样把空间复杂度从 O(n) 降到 O(1)，
// 那样会看不到动态规划的影子
func rob(nums []int) int {
	if len(nums) < 1 {
		return 0
	}
	if len(nums) < 3 {
		return maxInts(nums...)
	}
	money := make([]int, len(nums))
	money[0] = nums[0]
	money[1] = maxInts(nums[0:2]...)
	for i := 2; i < len(nums); i++ {
		money[i] = maxInts(money[i-2]+nums[i], money[i-1])
	}
	return money[len(nums)-1]
}
