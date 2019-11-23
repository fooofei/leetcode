package leetcode

// 268 https://leetcode-cn.com/problems/missing-number/

// 0 1 2 3 (4)

// 0 1 2 3 4 (5)

func missingNumber1(nums []int) int {
	var expectSum uint64
	midLen := (len(nums) + 1) / 2
	expectSum = uint64(len(nums)) * uint64(midLen)
	if len(nums)%2 == 0 {
		expectSum += uint64(midLen)
	}
	for _, n := range nums {
		expectSum -= uint64(n)
	}
	return int(expectSum)
}

func missingNumber(nums []int) int {
	var ret int
	for i,n := range nums {
		ret = ret ^ i ^ n
	}
	ret = ret ^ len(nums)
	return ret
}
