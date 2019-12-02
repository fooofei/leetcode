package leetcode

import (
	"sort"
	"testing"

	"gotest.tools/assert"
)

func assertEqualInts(t *testing.T, a []int, b []int) {
	assert.Equal(t, len(a), len(b), "%v != %v", a, b)
	for i := 0; i < len(a); i++ {
		assert.Equal(t, a[i], b[i])
	}
}

func assertEqualStrings(t *testing.T, a []string, b []string) {
	assert.Equal(t, len(a), len(b), "%v != %v", a, b)
	for i := 0; i < len(a); i++ {
		assert.Equal(t, a[i], b[i])
	}
}

func Test1(t *testing.T) {
	ret := findWords([][]byte{
		{'o', 'a', 'a', 'n'},
		{'e', 't', 'a', 'e'},
		{'i', 'h', 'k', 'r'},
		{'i', 'f', 'l', 'v'},
	}, []string{"oath", "pea", "eat", "rain"})
	sort.Strings(ret)
	expect := []string{"eat", "oath"}
	sort.Strings(expect)
	assertEqualStrings(t, ret, expect)
}

// 竟然有拐弯的测试用例
func Test2(t *testing.T) {
	assertEqualStrings(t, findWords([][]byte{
		{'a', 'b'},
		{'c', 'd'},
	}, []string{"acdb"}),
		[]string{"acdb"})
}

func Test3(t *testing.T) {
	ret := findWords([][]byte{
		{'a', 'a'},
	}, []string{"aaa"})
	sort.Strings(ret)
	expect := []string{}
	assertEqualStrings(t, ret, expect)
}
