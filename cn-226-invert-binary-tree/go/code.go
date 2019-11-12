package leetcode

// 226 https://leetcode-cn.com/problems/invert-binary-tree/

// 传说 Google 考试 Homebrew 作者的那个题目

type TreeNode struct {
	Val int
	Left *TreeNode
	Right *TreeNode
}

func invertTree(root *TreeNode) *TreeNode {
	if root == nil {
		return nil
	}
	left := invertTree(root.Left)
	right := invertTree(root.Right)
	root.Left = right
	root.Right = left
	return root
}