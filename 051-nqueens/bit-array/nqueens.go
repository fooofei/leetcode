package nqueens

import (
	"math"
	"math/bits"

	"github.com/pkg/errors"
	"github.com/willf/bitset"
)

// 解释如何在 O(1) 时间内找到可以放置皇后的位置
// 0 是没放皇后的位置
// 1 是放置皇后的位置
// A 类别表示同列不能放皇后
// B 类别表示左下对角线不能放皇后
// C 类别表示右下对角线不能放皇后
//
// 0    1    0    0    0    0    0    0
// B    A    C    1    0    0    0    0
// 0    A    B    AC   C    0    0    0
// 0    0    0    0    0    0    0    0
// ...

// 这个解释了 A B C 分别变化的过程，跟随 row 的增长而变化
//
// 下一列的 A' = A | 当前位
// 下一列的 B' = (B | 当前位) 左边移动一格子
// 下一列的 C' = (C | 当前位) 右边移动一格子

//
// 使用 uint64 ，决定了最多有 64 个皇后
func testBit1(cols uint64, leftDnDig uint64, rightDnDig uint64,
	row int, maxRow int) int {
	if row >= maxRow {
		return 1
	}
	var allBits uint64 = (1 << maxRow) - 1
	placed := cols | leftDnDig | rightDnDig
	leftOver := allBits & ^placed // 取反操作， 其他语言中是 ~placed
	r := 0
	for leftOver > 0 {
		firstBit := leftOver & (-leftOver)
		leftOver -= firstBit

		r += testBit1(cols|firstBit,
			(leftDnDig|firstBit)>>1,
			(rightDnDig|firstBit)<<1,
			row+1,
			maxRow)
	}
	return r
}

func Sum1(N int) int {

	max := bits.OnesCount64(math.MaxUint64)
	if N > max {
		panic(errors.Errorf("exceed max %v", max))
	}

	return testBit1(0, 0, 0, 0, N)
}

//
// 标准的 bitset ，解决更一般的问题，覆盖范围更广
//
//

// BitSet 用法
// 假如我们要看 i = 32 ，第 32 位，1 个 uint64 是能够包含的
// i>>6 = 0， 所以看起来 set 的存储是从小值到大值
// return b.set[i>>6]&(1<<(i&(64-1))) != 0

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
	// 在此 row 中，尝试每一个可以放置皇后的 column,
	// column 用位来表示
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
