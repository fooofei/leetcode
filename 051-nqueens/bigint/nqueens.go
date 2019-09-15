package nqueens

import (
	"math/big"
)

type BigInt = big.Int

// same as bit-array, but use BigInt

func testBit(cols, leftDnDig, rightDnDig, allBits *BigInt, row, maxRow int) int {
	if row >= maxRow {
		return 1
	}
	placed := big.NewInt(0)
	placed.Or(big.NewInt(0).Or(cols, leftDnDig), rightDnDig)
	leftOver := big.NewInt(0)
	leftOver.And(allBits, big.NewInt(0).Not(placed)) // 取反操作， 其他语言中是 ~placed
	r := 0
	for leftOver.BitLen() > 0 {
		firstBit := big.NewInt(0)
		firstBit.And(leftOver, big.NewInt(0).Neg(leftOver))
		v0 := big.NewInt(0).Sub(leftOver, firstBit)
		leftOver = v0

		r += testBit(big.NewInt(0).Or(cols, firstBit),
			big.NewInt(0).Rsh(big.NewInt(0).Or(leftDnDig, firstBit), 1),
			big.NewInt(0).Lsh(big.NewInt(0).Or(rightDnDig, firstBit), 1),
			allBits,
			row+1,
			maxRow)
	}
	return r
}

func Sum(N int) int {
	c := &BigInt{}
	l := &BigInt{}
	r := &BigInt{}

	one := big.NewInt(1)
	allBits := &BigInt{}
	allBits.Sub(big.NewInt(0).Lsh(one, uint(N)), one)

	return testBit(c, l, r, allBits, 0, N)
}
