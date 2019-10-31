

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

// 278 https://leetcode-cn.com/problems/first-bad-version/

// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

int firstBadVersion(int n)
{
    int64_t first = 1;
    int64_t last = (int64_t)n + 1;

    for (; first < last;) {

        int64_t mid = (first + last) / 2;
        if (!isBadVersion((int)mid)) {
            first = mid + 1;
        } else {
            last = mid;
        }
    }

    return (int)first;
}

int main()
{

    return 0;
}
