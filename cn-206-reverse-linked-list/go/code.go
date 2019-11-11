package leetcode

// 206 https://leetcode-cn.com/problems/reverse-linked-list/

type ListNode struct {
	Val  int
	Next *ListNode
}

func reverseList(head *ListNode) *ListNode {
	if head == nil {
		return nil
	}
	ret := head
	head = head.Next
	ret.Next = nil
	for head != nil {
		out := head
		head = head.Next
		out.Next = ret
		ret = out
	}
	return ret
}
