package leetcode

// 234 https://leetcode-cn.com/problems/palindrome-linked-list/

type ListNode struct {
	Val  int
	Next *ListNode
}

// 把 list 平均分割为 2 个
// 奇数个数的 list ，丢弃中间的
// 偶数的就平分
func split(head *ListNode) *ListNode {
	var leftTail **ListNode
	leftTail = &head
	fast := *leftTail

	for fast != nil {
		fast = fast.Next
		if fast == nil {
			dummy := leftTail
			leftTail = &((*leftTail).Next)
			*dummy = nil
			break
		}
		leftTail = &((*leftTail).Next)
		fast = fast.Next
	}
	ret := *leftTail
	*leftTail = nil
	return ret
}
func isSameList(list1 *ListNode, list2 *ListNode) bool {
	for {
		if list1 == nil && list2 == nil {
			return true
		}
		if list1 == nil {
			return false
		}
		if list2 == nil {
			return false
		}
		if list1.Val != list2.Val {
			return false
		}
		list1 = list1.Next
		list2 = list2.Next
	}
}
func isPalindrome(head *ListNode) bool {
	// 错误点: 空 list 认为 true，我原本以为是 false
	if head == nil || head.Next == nil {
		return true
	}
	list2 := split(head)
	next := list2.Next
	list2.Next = nil
	// 头插法把第二个 list 反转
	for next != nil {
		newNode := next
		next = next.Next
		newNode.Next = list2
		list2 = newNode
	}
	return isSameList(head, list2)
}
