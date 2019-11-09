package leetcode

// 189 https://leetcode-cn.com/problems/rotate-array/

// index
// 0 1 2 3 4 5 6
// 4 5 6 0 1 2 3
// 谁腾出位置了 就看这个位置应该是谁来填充，按照这个链走下去

// 从头部开始
// k=3
// 4->0
// 1->4
// 5->1
// 2->5
// 6->2
// 3->6
// 0->3

// 从尾部开始
// k=3
// 3->6
// 0->3
// 4->0
// 1->4
// 5->1
// 2->5
// 6->2

// index
// 0 1 2 3 4 5
// 4 5 0 1 2 3
// k=2
// 4->0
// 2->4
// 0->2
// 5->1
// 3->5

func rotate(nums []int, k int) {
	k = k % len(nums)
	if k <= 0 {
		return
	}
	holder := nums[0]
	holderIndex := 0
	empty := holderIndex
	for i := 1; i < len(nums); i++ {
		j := 0
		if empty < k {
			j = empty + len(nums) - k
		} else {
			j = empty - k
		}
		if j == holderIndex {
			nums[empty] = holder
			holderIndex += 1
			holder = nums[holderIndex]
			empty = holderIndex
		} else {
			nums[empty] = nums[j]
			empty = j
		}
	}
	nums[empty] = holder
}
