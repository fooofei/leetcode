#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



// 028 https://leetcode-cn.com/problems/implement-strstr/

// sunday 比较好记忆

int Sunday(const char* str, const char* patt)
{
    if (str == NULL || patt == NULL) {
        return -1;
    }
    if (*patt == 0) {
        return 0;
    }

    int pattLen = strlen(patt);

    int* shift = (int*)calloc(0x100, sizeof(int));

    for (int i = 0; i < 0x100; i++) {
        shift[i] = pattLen + 1;
    }
    for (int i = 0; i < pattLen; i++) {
        uint8_t u8 = patt[i];
        shift[u8] = pattLen - i;
    }

    // 没有多余的变量记录 str 长度，导致总是依赖迭代判断 '\0'
    // 看到下面的代码很长
    char pattEnd = patt[pattLen - 1];
    const char* p = str;
    for (int i = pattLen - 1; *p != 0 && i > 0; i--, p++) {
    }
    if (*p == 0) {
        return -1;
    }
    p += 1;

    for (;;) {
        if (*(p - 1) == pattEnd && 0 == memcmp(p - pattLen, patt, pattLen)) {
            free(shift);
            return p - pattLen - str;
        }
        if (*p == 0) {
            break;
        }
        int step = shift[(uint8_t)(*p)] - 1;
        for (int i = 0; i < step && *p != 0; i++) {
            p++;
        }
        if (*p == 0) {
            break;
        }
        p++;
    }

    free(shift);
    shift = NULL;

    return -1;
}

void test1()
{
    int off = Sunday("hello", "ll");
    printf("%d\n", off);
    if (off != 2) {
        printf("%s() fail\n", __func__);
    }
}

void test2()
{
    int off = Sunday("hello", "he");
    printf("%d\n", off);
    if (off != 0) {
        printf("%s() fail\n", __func__);
    }
}

void test3()
{
    int off = Sunday("hello", "lo");
    printf("%d\n", off);
    if (off != 3) {
        printf("%s() fail\n", __func__);
    }
}

void test4()
{
    int off = Sunday("hello", "hello");
    printf("%d\n", off);
    if (off != 0) {
        printf("%s() fail\n", __func__);
    }
}

void test5()
{
    int off = Sunday("aaaaa", "bba");
    printf("%d\n", off);
    if (off != -1) {
        printf("%s() fail\n", __func__);
    }
}


int main()
{

    return 0;
}
