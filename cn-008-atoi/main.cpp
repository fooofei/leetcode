#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <stack>
#include <string>
#include <thread>
#include <vector>

using namespace std;

// 008 https://leetcode-cn.com/problems/string-to-integer-atoi/

int NumsToNegativeInt(int* nums, int size)
{
    int ret = 0;
    for (int i = 0; i < size; i++) {
        if (ret < INT_MIN / 10) {
            return INT_MIN;
        } else if (ret == INT_MIN / 10 && (-nums[i] < INT_MIN % 10)) {
            return INT_MIN;
        }
        ret = ret * 10;
        ret -= nums[i];
    }

    return ret;
}

int NumsToPositiveInt(int* nums, int size)
{
    int ret = 0;
    for (int i = 0; i < size; i++) {
        if (ret > INT_MAX / 10) {
            return INT_MAX;
        } else if (ret == INT_MAX / 10 && (nums[i] > INT_MAX % 10)) {
            return INT_MAX;
        }
        ret = ret * 10;
        ret += nums[i];
    }
    return ret;
}

int NumsStart(const char* b, int* nums, int cap)
{
    int size = 0;
    for (; *b != 0 && *b == '0'; b++) {
    }
    for (; *b != 0 && isdigit(*b); b++) {
        if (size >= cap) {
            return size;
        }
        nums[size] = *b - '0';
        size += 1;
    }
    return size;
}

// return nums' size
int StrToNums(const char* p, size_t l, int* nums, int cap, bool* negative)
{
    const char* end = p + l;
    const char* b = p;
    for (; *b != 0; b++) {
        if (*b == '-') {
            int size = 0;
            size = NumsStart(b + 1, nums, cap);
            if (size > 0) {
                *negative = true;
                return size;
            }
            return 0;
        } else if (*b == '+') {
            int size = 0;
            size = NumsStart(b + 1, nums, cap);
            if (size > 0) {
                return size;
            }
            return 0;
        } else if (*b == ' ') {

        } else if (isdigit(*b)) {
            int size = 0;
            size = NumsStart(b, nums, cap);
            if (size > 0) {
                return size;
            }
            return 0;
        } else {
            return 0;
        }
    }
    return 0;
}

class Solution {
public:
    int myAtoi(string str)
    {
        int size = 0;
        int cap = 20;
        bool negative = false;
        int ret = 0;
        int* nums = (int*)calloc(cap, sizeof(int));
        size = StrToNums(str.c_str(), str.size(), nums, cap, &negative);
        if (negative && size > 0) {
            ret = NumsToNegativeInt(nums, size);
        } else if (size > 0) {
            ret = NumsToPositiveInt(nums, size);
        }
        free(nums);
        return ret;
    }
};

// 我认为 "words and 987" 设计为输出 987 更好，更符合实际
// 但是测试用例预期输出 0

void test1()
{
    Solution sln;
    auto r = sln.myAtoi("42");
    if (r != 42) {
        printf("%s() fail\n", __func__);
    }
}

void test2()
{
    Solution sln;
    auto r = sln.myAtoi("      -42");
    if (r != -42) {
        printf("%s() fail\n", __func__);
    }
}

void test3()
{
    Solution sln;
    auto r = sln.myAtoi("4193 with words");
    if (r != 4193) {
        printf("%s() fail\n", __func__);
    }
}

void test4()
{
    Solution sln;
    auto r = sln.myAtoi("-91283472332");
    if (r != INT_MIN) {
        printf("%s() fail\n", __func__);
    }
}

void test5()
{
    Solution sln;
    auto r = sln.myAtoi("words and 987");
    if (r != 0) {
        printf("%s() fail\n", __func__);
    }
}

void test6()
{
    Solution sln;
    auto r = sln.myAtoi("  0000000000012345678");
    if (r != 12345678) {
        printf("%s() fail\n", __func__);
    }
}

void test7()
{
    Solution sln;
    auto r = sln.myAtoi("-000000000000001");
    if (r != -1) {
        printf("%s() fail\n", __func__);
    }
}

// 题目也真是模糊，这样的用例输出 -2 不行么
void test8()
{
    Solution sln;
    auto r = sln.myAtoi("+-2");
    if (r != 0) {
        printf("%s() fail\n", __func__);
    }
}

void test9()
{
    Solution sln;
    auto r = sln.myAtoi("-+2");
    if (r != 0) {
        printf("%s() fail\n", __func__);
    }
}

void test10()
{
    Solution sln;
    auto r = sln.myAtoi("--2");
    if (r != 0) {
        printf("%s() fail\n", __func__);
    }
}

void test11()
{
    Solution sln;
    auto r = sln.myAtoi("++2");
    if (r != 0) {
        printf("%s() fail\n", __func__);
    }
}

int main()
{

    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
    std::cout << "main exit\n";
    return 0;
}
