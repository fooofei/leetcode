package leetcode

import (
	"container/list"
)

// https://leetcode-cn.com/problems/add-two-numbers/

type ListNode struct {
	Val  int
	Next *ListNode
}

func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {

	dl := list.New()
	carry := 0
	for l1 != nil && l2 != nil {
		v := l1.Val + l2.Val + carry
		carry = v / 10
		dl.PushBack(v % 10)
		l1 = l1.Next
		l2 = l2.Next
	}
	for ; l1 != nil; l1 = l1.Next {
		v := l1.Val + carry
		carry = v / 10
		dl.PushBack(v % 10)
	}
	for ; l2 != nil; l2 = l2.Next {
		v := l2.Val + carry
		carry = v / 10
		dl.PushBack(v % 10)

	}
	if carry > 0 {
		dl.PushBack(carry)
	}

	var head *ListNode
	var tail *ListNode
	for dl.Front() != nil {
		if tail == nil {
			head = &ListNode{}
			tail = head
		} else {
			tail.Next = &ListNode{}
			tail = tail.Next
		}
		tail.Val = dl.Front().Value.(int)
		dl.Remove(dl.Front())
	}
	return head
}
