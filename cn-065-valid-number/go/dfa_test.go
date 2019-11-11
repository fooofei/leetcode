package leetcode

import (
	"gotest.tools/assert"
	"testing"
)

func Test1(t *testing.T) {
	assert.Equal(t, isNumber("3.e10"), true)
}
func Test2(t *testing.T) {
	assert.Equal(t, isNumber(".e10"), false)
}
func Test3(t *testing.T) {
	assert.Equal(t, isNumber(".0e10"), true)
}
func Test4(t *testing.T) {
	assert.Equal(t, isNumber("0.e10"), true)
}
func Test5(t *testing.T) {
	assert.Equal(t, isNumber("3."), true)
}
func Test6(t *testing.T) {
	assert.Equal(t, isNumber("003"), true)
}
func Test7(t *testing.T) {
	assert.Equal(t, isNumber("003.e000"), true)
}
func Test8(t *testing.T) {
	assert.Equal(t, isNumber("003.e0003"), true)
}
func Test9(t *testing.T) {
	assert.Equal(t, isNumber(".e0003"), false)
}
func Test10(t *testing.T) {
	assert.Equal(t, isNumber("003."), true)
}
func Test11(t *testing.T) {
	assert.Equal(t, isNumber("123"), true)
}
func Test12(t *testing.T) {
	assert.Equal(t, isNumber(" 123 "), true)
}
func Test13(t *testing.T) {
	assert.Equal(t, isNumber("0"), true)
}
func Test14(t *testing.T) {
	assert.Equal(t, isNumber("0123"), true)
}
func Test15(t *testing.T) {
	assert.Equal(t, isNumber("00"), true)
}
func Test16(t *testing.T) {
	assert.Equal(t, isNumber("-10"), true)
}
func Test17(t *testing.T) {
	assert.Equal(t, isNumber("-0"), true)
}
func Test18(t *testing.T) {
	assert.Equal(t, isNumber("123.5"), true)
}
func Test19(t *testing.T) {
	assert.Equal(t, isNumber("123.000000"), true)
}
func Test20(t *testing.T) {
	assert.Equal(t, isNumber("-500.777"), true)
}
func Test21(t *testing.T) {
	assert.Equal(t, isNumber("0.0000001"), true)
}
func Test22(t *testing.T) {
	assert.Equal(t, isNumber("0.00000"), true)
}
func Test23(t *testing.T) {
	assert.Equal(t, isNumber("0."), true)
}
func Test24(t *testing.T) {
	assert.Equal(t, isNumber("00.5"), true)
}
func Test25(t *testing.T) {
	assert.Equal(t, isNumber("123e1"), true)
}
func Test26(t *testing.T) {
	assert.Equal(t, isNumber("1.23e10"), true)
}
func Test27(t *testing.T) {
	assert.Equal(t, isNumber("0.5e-10"), true)
}
func Test28(t *testing.T) {
	assert.Equal(t, isNumber("1.0e4.5"), false)
}
func Test29(t *testing.T) {
	assert.Equal(t, isNumber("0.5e04"), true)
}
func Test30(t *testing.T) {
	assert.Equal(t, isNumber("12 3"), false)
}
func Test31(t *testing.T) {
	assert.Equal(t, isNumber("1a3"), false)
}
func Test32(t *testing.T) {
	assert.Equal(t, isNumber(""), false)
}
func Test33(t *testing.T) {
	assert.Equal(t, isNumber("     "), false)
}
func Test34(t *testing.T) {
	assert.Equal(t, isNumber(".1"), true)
}
func Test35(t *testing.T) {
	assert.Equal(t, isNumber("."), false)
}
func Test36(t *testing.T) {
	assert.Equal(t, isNumber("2e0"), true)
}
func Test37(t *testing.T) {
	assert.Equal(t, isNumber("+.8"), true)
}
func Test38(t *testing.T) {
	assert.Equal(t, isNumber(" 005047e+6"), true)
}
func Test39(t *testing.T) {
	assert.Equal(t, isNumber("  2.8"), true)
}
