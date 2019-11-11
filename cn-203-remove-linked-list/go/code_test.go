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
	h1 := &ListNode{
		Val:  1,
		Next: nil,
	}
	h2 := &ListNode{
		Val:  1,
		Next: nil,
	}
	h3 := &ListNode{
		Val:  1,
		Next: nil,
	}
	h1.Next = h2
	h2.Next = h3
	assert.Equal(t, removeElements(h1, 1) == nil, true)

}

func Test2(t *testing.T) {
	h1 := &ListNode{
		Val:  1,
		Next: nil,
	}
	h2 := &ListNode{
		Val:  2,
		Next: nil,
	}
	h3 := &ListNode{
		Val:  3,
		Next: nil,
	}
	h1.Next = h2
	h2.Next = h3

	ret := removeElements(h1, 1)
	assert.Equal(t, ret.Val, 2)
	assert.Equal(t, ret.Next.Val, 3)
	assert.Equal(t, ret.Next.Next == nil, true)
}

func Test3(t *testing.T) {
	h1 := &ListNode{
		Val:  3,
		Next: nil,
	}
	h2 := &ListNode{
		Val:  2,
		Next: nil,
	}
	h3 := &ListNode{
		Val:  1,
		Next: nil,
	}
	h1.Next = h2
	h2.Next = h3

	ret := removeElements(h1, 1)
	assert.Equal(t, ret.Val, 3)
	assert.Equal(t, ret.Next.Val, 2)
	assert.Equal(t, ret.Next.Next == nil, true)
}
