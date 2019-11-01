

#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifndef WIN32
#include <asprintf.h>
#endif

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// 053 https://leetcode-cn.com/problems/maximum-subarray/

// 比 C++ 版本使用更少的逻辑，没有用到 stack 

int maxSubArray(int* nums, int numsSize)
{
    if (numsSize <= 1) {
        return nums[0];
    }

    int start = 0;
    int maxSum = INT_MIN;
    int sum = nums[0];

    for (int i = 1; i < numsSize; i++) {
        if (sum <= 0) {
            maxSum = MAX(maxSum, sum);
            sum = 0;
            start = INT_MAX;
        }

        if (nums[i] < 0 && start < i) {
            maxSum = MAX(maxSum, sum);
        }

        if (start > numsSize) {
            start = i;
        }
        sum += nums[i];
    }

    maxSum = MAX(maxSum, sum);
    return maxSum;
}

void testf(int* p, int size, int expect)
{
    int ret = maxSubArray(p, size);
    if (ret != expect) {
        printf("%s() fail ret=%d expect=%d\n", __func__, ret, expect);
    }
}

int main()
{
    int a1[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    testf(a1, ARRAY_SIZE(a1), 6);

    int a2[] = { -2, -1 };
    testf(a2, ARRAY_SIZE(a2), -1);

    int a3[] = { -2, 3, 1, 3 };
    testf(a3, ARRAY_SIZE(a3), 7);

    return 0;
}
