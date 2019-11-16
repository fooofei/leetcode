package leetcode

// 235 https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-search-tree/

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

// 遍历 TREE 得到包含某结点在内的和它的父亲结点
// 组成一个 list
// 顺序是 自己 自己.parent 自己.parent.parent  ...
func getParentLists(root, target *TreeNode) []*TreeNode {
	if root == nil {
		return []*TreeNode{}
	}
	if root == target {
		return []*TreeNode{root}
	}
	left := getParentLists(root.Left, target)
	if len(left) > 0 {
		return append(left, root)
	}
	right := getParentLists(root.Right, target)
	if len(right) > 0 {
		return append(right, root)
	}
	return []*TreeNode{}
}

// 问题求解就被转化为 // 160  https://leetcode-cn.com/problems/intersection-of-two-linked-lists/
func findCommon(pList, qList []*TreeNode) *TreeNode {
	var i, j int
	pList = append(pList, qList...)
	qList = append(qList, pList...)
	for pList[i] != qList[j] {
		i += 1
		j += 1
	}
	return pList[i]
}

// 我这样做没有利用到 二叉搜索树的性质
// 我把它转化为两个 list ，求两个 list 的第一个交叉的结点
func lowestCommonAncestor(root, p, q *TreeNode) *TreeNode {
	if root == nil {
		return nil
	}
	pList := getParentLists(root, p)
	qList := getParentLists(root, q)
	return findCommon(pList, qList)
}
