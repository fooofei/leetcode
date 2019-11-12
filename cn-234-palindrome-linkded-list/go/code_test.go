package leetcode

import (
	"testing"

	"gotest.tools/assert"
)

func assertEqualInts(t *testing.T, a []int, b []int) {
	assert.Equal(t, len(a), len(b))
	for i := 0; i < len(a); i++ {
		assert.Equal(t, a[i], b[i])
	}
}

func Test1(t *testing.T) {
	n1 := &ListNode{
		Val:  1,
		Next: nil,
	}
	n2 := &ListNode{
		Val:  2,
		Next: nil,
	}
	n1.Next = n2
	assert.Equal(t, isPalindrome(n1), false)
}

func Test2(t *testing.T) {
	n1 := &ListNode{
		Val:  1,
		Next: nil,
	}
	n2 := &ListNode{
		Val:  2,
		Next: nil,
	}
	n3 := &ListNode{
		Val:  2,
		Next: nil,
	}
	n4 := &ListNode{
		Val:  1,
		Next: nil,
	}
	n1.Next = n2
	n2.Next = n3
	n3.Next = n4
	assert.Equal(t, isPalindrome(n1), true)
}

func Test3(t *testing.T) {
	n1 := &ListNode{
		Val:  1,
		Next: nil,
	}
	n2 := &ListNode{
		Val:  2,
		Next: nil,
	}
	n3 := &ListNode{
		Val:  1,
		Next: nil,
	}
	n1.Next = n2
	n2.Next = n3
	assert.Equal(t, isPalindrome(n1), true)
}

func Test4(t *testing.T) {
	n1 := &ListNode{
		Val:  1,
		Next: nil,
	}
	assert.Equal(t, isPalindrome(n1), true)
}
