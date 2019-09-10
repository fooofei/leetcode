package main

import (
	"fmt"
	prmt "nqueens/permutation"
)

func main() {
	for i := 4; i < 30; i++ {
		sum := prmt.Sum(i)
		fmt.Printf("sum(%v)= %v\n", i, sum)
	}
}
