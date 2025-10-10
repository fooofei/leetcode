package main

// 687 https://leetcode-cn.com/problems/longest-univalue-path/

// https://zxi.mytechroad.com/blog/tree/leetcode-687-longest-univalue-path/

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

///

func maxInt(values ...int) int {
	maxValue := values[0]
	for _, v := range values[1:] {
		if v > maxValue {
			maxValue = v
		}
	}
	return maxValue
}

// 返回值表示 root 的左右子树中 到 left/right 之后还依旧连续的路径长（不是所求问题的子集）
// answer 表示所有递归能遇到的最大值
func traverse(root *TreeNode, answer *int) int {
	if root == nil {
		return 0
	}
	left := traverse(root.Left, answer)
	right := traverse(root.Right, answer)

	var leftPath int
	var rightPath int
	if root.Left != nil && root.Val == root.Left.Val {
		leftPath = left + 1
	}
	if root.Right != nil && root.Val == root.Right.Val {
		rightPath = right + 1
	}

	// 优化点
	// 可以优化为 *answer = maxInt(*answer, leftPath + rightPath) 不需要任何判断
	if root.Left != nil && root.Right != nil && root.Val == root.Left.Val && root.Val == root.Right.Val {
		*answer = maxInt(*answer, leftPath+rightPath)
	} else {
		*answer = maxInt(*answer, leftPath, rightPath)
	}
	return maxInt(leftPath, rightPath)

}

func longestUnivaluePath(root *TreeNode) int {
	var answer int
	traverse(root, &answer)
	return answer
}
