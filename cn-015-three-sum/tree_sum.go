package leetcode

import (
	"fmt"
	"sort"
)

// 015 https://leetcode-cn.com/problems/3sum/

func threeSum1(nums []int) [][]int {

	sort.Ints(nums)
	uniq := make(map[string]bool)
	zeroIdx := sort.SearchInts(nums, 0)
	totalLen := len(nums)
	result := make([][]int, 0, 20000)
loop1:
	for i := 0; i < totalLen-2 && nums[i] <= 0; i++ {
		v1 := nums[i]

		for j := i + 1; j < totalLen-1; j++ {
			v2 := nums[j]

			if v1+v2 > 0 {
				break loop1
			}
			if v1+v2+nums[totalLen-1] < 0 {
				continue
			}

			k := j + 1
			if k < zeroIdx {
				k = zeroIdx
			}

			expectV3 := -(v1 + v2)
			subNums := nums[k:totalLen]
			v3Idx := sort.SearchInts(subNums, expectV3)
			if v3Idx < len(subNums) && subNums[v3Idx] == expectV3 {
				s := fmt.Sprintf("%v.%v.%v", v1, v2, expectV3)
				if _, exists := uniq[s]; !exists {
					result = append(result, []int{v1, v2, expectV3})
					uniq[s] = true
				}
			}
		}
	}
	return result
}

func threeSum(nums []int) [][]int {
	var left int
	var right int
	var v1 int
	var negV1 int
	var negV1Idx int

	sort.Ints(nums)
	result := make([][]int, 0, 20000)
	zeroIdx := sort.SearchInts(nums, 0)

	for i := 0; i < len(nums)-2 && nums[i] <= 0; i++ {

		if i > 0 && nums[i-1] == nums[i] {
			continue
		}

		v1 = nums[i]
		negV1 = -v1
		left = i + 1
		right = len(nums) - 1

		subNums := nums[left:]
		negV1Idx = sort.SearchInts(subNums, negV1)

		if negV1Idx >= len(subNums) {
			// all subNums < negV1
			// we cannot use negative numbers
			left = zeroIdx
		} else if negV1Idx == 0 {
			// all subNums >= negV1
			if v1+nums[left]+nums[left+1] == 0 {
				result = append(result, []int{v1, nums[left], nums[left+1]})
			}
			continue
		}

		for left < right {
			sum := v1 + nums[left] + nums[right]
			if sum > 0 {
				right--
			} else if sum < 0 {
				left++
			} else if right-left > 1 && nums[left] == nums[left+1] && nums[right] == nums[right-1] {
				right-- // 比 left++ 更好，
				continue
			} else {
				result = append(result, []int{v1, nums[left], nums[right]})
				right--
				left++
			}
		}
	}
	return result
}
