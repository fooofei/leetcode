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
	obj.AddWord("bad")
	obj.AddWord("dad")
	obj.AddWord("mad")
	assert.Equal(t, obj.Search("pad"), false)
	assert.Equal(t, obj.Search("bad"), true)
	assert.Equal(t, obj.Search(".ad"), true)
	assert.Equal(t, obj.Search("b.."), true)
	assert.Equal(t, obj.Search("b..."), false)
}

func Test2(t *testing.T) {
	obj := Constructor()
	obj.AddWord("at")
	obj.AddWord("and")
	obj.AddWord("an")
	obj.AddWord("add")
	obj.AddWord("add")
	assert.Equal(t, obj.Search("a"), false)
	assert.Equal(t, obj.Search(".at"), false)
	obj.AddWord("bat")
	assert.Equal(t, obj.Search(".at"), true)
	assert.Equal(t, obj.Search("an."), true)
	assert.Equal(t, obj.Search("a.d."), false)
	assert.Equal(t, obj.Search("b."), false)
	assert.Equal(t, obj.Search("a.d"), true)
	assert.Equal(t, obj.Search("."), false)

}
