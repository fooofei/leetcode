package main

import (
	bita "nqueens/bit-array"
	iterrow "nqueens/iterrow-colarray"
	multi "nqueens/multi-array"
	per "nqueens/permutation"
	"testing"

	"github.com/willf/bitset"

	"gotest.tools/assert"
)

func tests(fn func(int) int, t *testing.T) {
	cases := [][]int{
		{4, 2},
		{5, 10},
		{6, 4},
		{7, 40},
		{8, 92},
		{9, 352},
		{10, 724},
		{11, 2680},
		{12, 14200},
		{13, 73712},
		//{15, 2279184},
		//{16, 14772512},
	}

	for _, cs := range cases {
		assert.Equal(t, fn(cs[0]), cs[1])
	}
}

func TestBitArray2(t *testing.T) {
	tests(bita.Sum2, t)
}

func TestIterRowColArray(t *testing.T) {
	tests(iterrow.Sum, t)
}

func TestMultiArray(t *testing.T) {
	tests(multi.Sum, t)
}

func TestBitArray1(t *testing.T) {
	tests(bita.Sum1, t)
}

func TestPermutation(t *testing.T) {
	tests(per.Sum, t)
}

func TestBitSetRightMove(t *testing.T) {

	bset := bitset.New(80)
	bset.Set(79)

	assert.Equal(t, bset.Len(), uint(80))

	bita.BitsetRightMove(bset, 79)
	assert.Equal(t, bset.Test(0), true)
}

func TestBitSetLeftMove(t *testing.T) {
	bset := bitset.New(80)
	bset.Set(0)

	assert.Equal(t, bset.Len(), uint(80))

	bita.BitsetLeftMove(bset, 79)
	assert.Equal(t, bset.Test(79), true)
}

// === RUN   TestIterRowColArray
//--- PASS: TestIterRowColArray (1.56s)
//=== RUN   TestMultiArray
//--- PASS: TestMultiArray (0.42s)
//=== RUN   TestBitArray1
//--- PASS: TestBitArray1 (0.06s)
//=== RUN   TestBitArray2
//--- PASS: TestBitArray2 (3.76s)
