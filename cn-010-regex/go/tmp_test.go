package main

import (
	"gotest.tools/assert"
	"testing"
)

func Test1(t *testing.T) {
	assert.Equal(t, isMatch("", "c*c*"), true)
}

func Test2(t *testing.T) {
	assert.Equal(t, isMatch("a", "ab*"), true)
}

func Test3(t *testing.T) {
	assert.Equal(t, isMatch("aaa", "a*a"), true)
}

func Test4(t *testing.T) {
	assert.Equal(t, isMatch("ab", ".*c"), false)
}

func Test5(t *testing.T) {
	assert.Equal(t, isMatch("ab", ".*"), true)
}

func Test6(t *testing.T) {
	assert.Equal(t, isMatch("mississippi", "mis*is*p*."), false)
}

func Test7(t *testing.T) {
	assert.Equal(t, isMatch("aaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*c"), false)
}
