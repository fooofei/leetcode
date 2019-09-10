package main

import (
	"fmt"
	bita "nqueens/bit-array"
)

func main() {
	for i := 4; i < 30; i++ {
		sum := bita.Sum1(i)
		fmt.Printf("sum(%v)= %v\n", i, sum)
	}
}
