package code

import "testing"
import "gotest.tools/assert"

func Test1(t *testing.T) {
	ret := strStr("hello", "ll")
	assert.Equal(t, ret, 2)

}

func Test2(t *testing.T) {
	ret := strStr("aaaaa", "bba")
	assert.Equal(t, ret, -1)

}

func Test3(t *testing.T) {
	ret := strStr("mississippi", "issip")
	assert.Equal(t, ret, 4)

}
