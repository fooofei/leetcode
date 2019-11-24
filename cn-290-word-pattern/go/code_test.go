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
	assert.Equal(t, wordPattern("abba", "dog cat cat dog"), true)
}

func Test2(t *testing.T) {
	assert.Equal(t, wordPattern("abba", "dog cat cat cat"), false)
}

func Test3(t *testing.T) {
	assert.Equal(t, wordPattern("abba", "dog dog dog dog"), false)
}

func Test4(t *testing.T) {
	assert.Equal(t, wordPattern("aaa", "dog dog dog dog"), false)
}

func Test5(t *testing.T) {
	assert.Equal(t, wordPattern("hut", "unit test harpoon"), true)
}

func TestHash1(t *testing.T) {
	// 如果选 27 的话，会有这个冲突
	v1 := hashStr([]byte("unit"), 0, 4)
	v2 := hashStr([]byte("test"), 0, 4)
	assert.Equal(t, v1, uint64(448))
	assert.Equal(t, v2, uint64(704))
}
