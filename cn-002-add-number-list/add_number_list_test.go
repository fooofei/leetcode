package leetcode

import (
	"testing"
)

func TestAddTwoNumers(t *testing.T) {

	l1 := &ListNode{Val: 1}
	l1.Next = &ListNode{Val: 8}
	l2 := &ListNode{Val: 0}

	l3 := addTwoNumbers(l1, l2)

	_ = l3
}
