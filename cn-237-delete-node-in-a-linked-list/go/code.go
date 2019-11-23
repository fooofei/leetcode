package leetcode

// 237 https://leetcode-cn.com/problems/delete-node-in-a-linked-list/

type ListNode struct {
	Val int
	Next *ListNode
}

// 删除的结点非末尾
// 且是原地修改，如果是删除头结点 都无法返回新的头部
// 这是在表明让我们使用假删除

// 不需要比对 参数 node 就是待删除的结点
func deleteNode(node *ListNode) {
	toDelete := node.Next
	node.Val = toDelete.Val
	node.Next = toDelete.Next
}