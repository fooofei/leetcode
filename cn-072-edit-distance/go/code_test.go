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

//   |"" | r | o | s |
// " | 0 | 1 | 2 | 3 |
// h | 1 | 1 | 2 | 3 |
// o | 2 | 2 | 1 | 2 |
// r | 3 | 2 | 2 | 2 |
// s | 4 | 3 | 3 | 2 |
// e | 5 | 4 | 4 | 3 |
func Test1(t *testing.T) {
	assert.Equal(t, minDistance("horse", "ros"), 3)
}

func Test2(t *testing.T) {
	assert.Equal(t, minDistance("intention", "execution"), 5)
}
