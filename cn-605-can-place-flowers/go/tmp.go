package main

// 605 https://leetcode-cn.com/problems/can-place-flowers/

// 已经提供的参数 `flowerbed` 中的 1 表示已经种植过，在给定的 n 要在剩下的空地上种植

func can(flowerbed []int, n int, dep int) bool {
	if n <= 0 {
		return true
	}
	if len(flowerbed) < 3 {
		return false
	}
	next := 1
	for next+1 < len(flowerbed) {
		if flowerbed[next-1] == 0 && flowerbed[next] == 0 && flowerbed[next+1] == 0 {
			flowerbed[next] = 1
			return can(flowerbed[next:], n-1, dep+1)
		}
		next += 1
	}
	return false
}

func canPlaceFlowers(flowerbed []int, n int) bool {
	newFlowerBed := make([]int, 0, len(flowerbed)+2)
	newFlowerBed = append(newFlowerBed, 0)
	newFlowerBed = append(newFlowerBed, flowerbed...)
	newFlowerBed = append(newFlowerBed, 0)
	return can(newFlowerBed, n, 0)
}
