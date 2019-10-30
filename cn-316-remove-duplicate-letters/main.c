

#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// 316 https://leetcode-cn.com/problems/remove-duplicate-letters/submissions/

char* removeDuplicateLetters(char* s)
{
    if (s == NULL) {
        return NULL;
    }
    int countsMap[0x100] = { 0 };
    const char* cursor = s;

    for (; *cursor != 0; cursor++) {
        countsMap[(uint8_t)(*cursor)] += 1;
    }

    char* charStack = calloc(0x100, 1);
    int saved[0x100] = { 0 };
    int stackIndex = 0;
    stackIndex++;
    cursor = s;
    for (; *cursor != 0; cursor++) {
        uint8_t u8 = *cursor;
        if (saved[u8] == 0) {

            for (;;) {
                uint8_t topu8 = charStack[stackIndex - 1];
                if (!((char)u8 < (char)topu8 && countsMap[topu8] > 0)) {
                    break;
                }
                stackIndex -= 1;
                saved[topu8] = 0;
            }
            charStack[stackIndex] = u8;
            saved[u8] = 1;
            stackIndex += 1;
        }
        countsMap[u8] -= 1;
    }

    

    char* ret = calloc(1, strlen(s)+1);
    int index = 0;
    for (int i = 1; i < stackIndex; i++) {
        ret[index] = charStack[i];
        index += 1;
    }
    ret[index] = 0;
    free(charStack);
    charStack = NULL;
    return ret;
}

void test2()
{
    removeDuplicateLetters("bcabc");
}

void test3()
{
    removeDuplicateLetters("cbacdcbc");
}

void test1()
{
    removeDuplicateLetters("c");
}

int main()
{
    test1();

    return 0;
}
