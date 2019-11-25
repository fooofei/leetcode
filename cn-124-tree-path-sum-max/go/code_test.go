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
		Val:   2,
		Left:  nil,
		Right: nil,
	}
	n2 := &TreeNode{
		Val:   -1,
		Left:  nil,
		Right: nil,
	}
	n1.Left = n2
	assert.Equal(t, maxPathSum(n1), 2)
}

func Test2(t *testing.T) {
	n1 := &TreeNode{
		Val:   1,
		Left:  nil,
		Right: nil,
	}
	n2 := &TreeNode{
		Val:   2,
		Left:  nil,
		Right: nil,
	}
	n3 := &TreeNode{
		Val:   3,
		Left:  nil,
		Right: nil,
	}
	n1.Left = n2
	n1.Right = n3
	assert.Equal(t, maxPathSum(n1), 6)
}

func Test3(t *testing.T) {
	n1 := &TreeNode{
		Val:   -10,
		Left:  nil,
		Right: nil,
	}
	n2 := &TreeNode{
		Val:   9,
		Left:  nil,
		Right: nil,
	}
	n3 := &TreeNode{
		Val:   20,
		Left:  nil,
		Right: nil,
	}
	n4 := &TreeNode{
		Val:   15,
		Left:  nil,
		Right: nil,
	}
	n5 := &TreeNode{
		Val:   7,
		Left:  nil,
		Right: nil,
	}
	n1.Left = n2
	n1.Right = n3
	n3.Left = n4
	n3.Right = n5
	assert.Equal(t, maxPathSum(n1), 42)
}