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
	nums1 := []int{1, 2, 2, 1}
	nums2 := []int{2, 2}
	assertEqualInts(t, intersect(nums1, nums2), []int{2, 2})
}

func Test2(t *testing.T) {
	nums1 := []int{4, 9, 5}
	nums2 := []int{9, 4, 9, 8, 4}
	assertEqualInts(t, intersect(nums1, nums2), []int{9, 4})
}

func Test3(t *testing.T) {
	nums1 := []int{4, 9, 5, 9}
	nums2 := []int{9, 4, 9, 8, 4}
	assertEqualInts(t, intersect(nums1, nums2), []int{9, 4, 9})
}

func Test4(t *testing.T) {
	nums1 := []int{4, 9, 5, 9}
	nums2 := []int{9, 4, 8, 4}
	assertEqualInts(t, intersect(nums1, nums2), []int{9, 4})
}
