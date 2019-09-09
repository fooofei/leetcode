package leetcode

import (
	"testing"

	"gotest.tools/assert"
)

func TestDailyTemp(t *testing.T) {
	input := []int{73, 74, 75, 71, 69, 72, 76, 73}
	expect := []int{1, 1, 4, 2, 1, 1, 0, 0}

	result := dailyTemperatures(input)
	t.Logf("expect = %v", expect)
	t.Logf("resut= %v", result)

	assert.DeepEqual(t, result, expect)

}
