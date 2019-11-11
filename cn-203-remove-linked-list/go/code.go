package leetcode

// 203 https://leetcode-cn.com/problems/remove-linked-list-elements/

type ListNode struct {
	Val  int
	Next *ListNode
}

// 指针的指针解决这个问题
func removeElements(head *ListNode, val int) *ListNode {
	var pp **ListNode
	pp = &head

	for *pp != nil {
		if (*pp).Val == val {
			*pp = (*pp).Next
		} else {
			pp = &((*pp).Next)
		}
	}
	return head
}
