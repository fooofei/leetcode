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
	n1 := &TreeNode{
		Val:   6,
		Left:  nil,
		Right: nil,
	}
	n2 := &TreeNode{
		Val:   2,
		Left:  nil,
		Right: nil,
	}
	n3 := &TreeNode{
		Val:   8,
		Left:  nil,
		Right: nil,
	}
	n4 := &TreeNode{
		Val:   0,
		Left:  nil,
		Right: nil,
	}
	n5 := &TreeNode{
		Val:   4,
		Left:  nil,
		Right: nil,
	}
	n6 := &TreeNode{
		Val:   7,
		Left:  nil,
		Right: nil,
	}
	n7 := &TreeNode{
		Val:   9,
		Left:  nil,
		Right: nil,
	}
	n8 := &TreeNode{
		Val:   3,
		Left:  nil,
		Right: nil,
	}
	n9 := &TreeNode{
		Val:   5,
		Left:  nil,
		Right: nil,
	}
	n5.Left = n8
	n5.Right = n9
	n2.Left = n4
	n2.Right = n5
	n3.Left = n6
	n3.Right = n7
	n1.Left = n2
	n1.Right = n3

	ret := lowestCommonAncestor(n1, n2, n3)
	assert.Equal(t, ret, n1)
}
