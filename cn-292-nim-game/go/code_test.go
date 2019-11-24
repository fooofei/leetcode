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
	assert.Equal(t, canWinNim(4), false)
	//for i:=0; i< 100; i++ {
	//	log.Printf("%v = %v", i, canWinNim(i))
	//}
}

func Test2(t *testing.T) {
	assert.Equal(t, canWinNim(6), true)
}
