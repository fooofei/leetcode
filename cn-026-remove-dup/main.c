

#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 026 https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array/

// 巧妙，把遍历过的数据当作栈了

int removeDuplicates(int* nums, int numsSize)
{
    if (numsSize < 2) {
        return numsSize;
    }

    int pos = 1;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] != nums[pos - 1]) {
            nums[pos] = nums[i];
            pos += 1;
        }
    }
    return pos;
}

int main()
{
    return 0;
}
