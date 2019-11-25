package leetcode

import (
	"math"
)

// 124 https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/
// 参照 053 https://leetcode-cn.com/problems/maximum-subarray/
// 区别在于 Tree 要保留的是中间结点 不能 Left Right 同时保留 最多留其中一个
// 数组就只需要往后看就行了

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func traverse(node *TreeNode, maxSum *int) int {
	if node == nil {
		return math.MinInt32
	}

	leftSum := traverse(node.Left, maxSum)
	rightSum := traverse(node.Right, maxSum)

	sumRet := maxInts(node.Val, node.Val+maxInts(0, leftSum),
		node.Val+maxInts(0, rightSum))
	sumNoRet := node.Val + maxInts(0, leftSum) + maxInts(0, rightSum)

	*maxSum = maxInts(*maxSum, sumRet, sumNoRet)
	// 返回的 sum 一定要是包含 node.Val 的 sum
	return sumRet
}

func maxPathSum(root *TreeNode) int {
	maxSum := math.MinInt32
	traverse(root, &maxSum)
	return maxSum
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
