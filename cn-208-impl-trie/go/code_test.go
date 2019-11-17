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
	obj := Constructor()
	obj.Insert("apple")
	assert.Equal(t, obj.Search("apple"), true)
	assert.Equal(t, obj.Search("app"), false)
	assert.Equal(t, obj.StartsWith("app"), true)
	obj.Insert("app")
	assert.Equal(t, obj.Search("app"), true)
}

func Test2(t *testing.T) {
	obj := Constructor()
	obj.Insert("hello")
	assert.Equal(t, obj.StartsWith("helloa"), false)
	assert.Equal(t, obj.StartsWith("hell"), true)
	assert.Equal(t, obj.StartsWith("hello"), true)
}
