package leetcode

// 190 https://leetcode-cn.com/problems/reverse-bits/

import (
	"unsafe"
)

func reverseBits(num uint32) uint32 {
	var ret uint32
	var i uint32
	for i = 0; i < uint32(unsafe.Sizeof(num)*8); i++ {
		fromRight := uint32(0x01 << i)
		fromLeft := uint32(0x80000000 >> i)

		if (num & fromRight) != 0 {
			ret |= fromLeft
		}
	}

	return ret
}
