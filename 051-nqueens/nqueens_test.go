package nqueens

import (
	iterrow "nqueens/iterrow_colarray"
	"testing"

	"gotest.tools/assert"
)

type sumNQueens = func(int) int

func tests(fn sumNQueens, t *testing.T) {
	cases := [][]int{{4, 2}, {8, 92}}

	for _, cs := range cases {
		assert.Equal(t, fn(cs[0]), cs[1])
	}
}

func TestIterRowColArray(t *testing.T) {
	tests(iterrow.Sum, t)
}
