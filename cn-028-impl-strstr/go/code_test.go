package code

import (
	"gotest.tools/assert"
	"testing"
)

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

func Test4(t *testing.T) {
	input := []byte("ababac")
	_ = buildDFA(input)
	assert.Equal(t, true, true)
}

func Test5(t *testing.T) {
	input := []byte("aacaaacf")
	_ = buildDFA(input)
	assert.Equal(t, true, true)
}
