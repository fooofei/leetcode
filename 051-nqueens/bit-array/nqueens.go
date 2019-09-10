package nqueens

import (
	"math"
	"math/bits"

	"github.com/pkg/errors"
	"github.com/willf/bitset"
)

// BitSet 用法
// 假如我们要看 i = 32 ，第 32 位，1 个 uint64 是能够包含的
// i>>6 = 0， 所以看起来 set 的存储是从小值到大值
// return b.set[i>>6]&(1<<(i&(64-1))) != 0

// BitsetLeftMove LeftMove the BitSet struct
func BitsetLeftMove(bset *bitset.BitSet, count int) *bitset.BitSet {
	var r *bitset.BitSet
	for i := 0; i < count; i++ {
		r = bset.InsertAt(0)
		bset.DeleteAt(r.Len() - 1)
	}
	return r
}

func BitsetRightMove(bset *bitset.BitSet, count int) *bitset.BitSet {
	var r *bitset.BitSet
	oriLen := bset.Len()
	if oriLen <= 0 {
		return bset
	}
	for i := 0; i < count; i++ {
		r = bset.DeleteAt(0)
		bset.InsertAt(oriLen - 1)
	}
	return r
}

func testBit1(allBits, row, ld, rd uint64) int {

	if row == allBits {
		return 1
	}

	placed := row | ld | rd
	leftover := allBits & (^placed)
	r := 0
	for leftover > 0 {
		rightestBit := leftover & (-leftover)
		leftover -= rightestBit

		r += testBit1(allBits,
			row|rightestBit,
			(ld|rightestBit)<<1,
			(rd|rightestBit)>>1)
	}

	return r
}

func Sum1(N int) int {
	max := bits.OnesCount64(math.MaxUint64)
	if N > max {
		panic(errors.Errorf("exceed max %v", max))
	}

	var allBits uint64
	// Not consider overflow,
	// because Golang also not consider overflow ,
	// define MaxUint64 = 1<<64 - 1
	allBits = (1 << N) - 1
	return testBit1(allBits, 0, 0, 0)

}

// leftDnDig leftDownDiagonal  左下对角线 要左移(位运算的右移)
// rightDnDig rightDownDiagonal  右下对角线 要右移(位运算的左移)
func testBit(colset *bitset.BitSet, leftDnDig *bitset.BitSet,
	rightDnDig *bitset.BitSet, row uint) int {

	if row >= colset.Len() {
		return 1
	}
	// diableBits is where we cannot place
	disableBits := colset.Union(leftDnDig).Union(rightDnDig)

	if disableBits.All() {
		return 0
	}
	var i uint
	r := 0
	for i = 0; i < disableBits.Len(); i++ {
		if disableBits.Test(i) {
			continue
		}
		c0 := colset.Clone().Set(i)
		l0 := BitsetRightMove(leftDnDig.Clone().Set(i), 1)
		r0 := BitsetLeftMove(rightDnDig.Clone().Set(i), 1)
		r += testBit(c0, l0, r0, row+1)
	}
	return r
}

func Sum2(N int) int {
	col := bitset.New(uint(N))
	l := bitset.New(uint(N))
	r := bitset.New(uint(N))
	return testBit(col, l, r, 0)

}
