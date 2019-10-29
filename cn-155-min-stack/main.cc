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

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

// 155 https://leetcode-cn.com/problems/min-stack/

// 真是学习知识，用两个栈 一个是假栈， 我的土方法， 用  
// strcut Item* stackNext;
// struct Item* minNext;
// struct Item* minPrev;
// 复杂度高


class MinStack {
public:
    /** initialize your data structure here. */
    MinStack()
    {
    }

    ~MinStack()
    {
    }

    void push(int x)
    {
        stack_.push_back(x);
        if (min_.size() > 0 && x >= min_.back()) {
            min_.push_back(min_.back());
        } else {
            min_.push_back(x);
        }
    }

    void pop()
    {
        min_.pop_back();
        stack_.pop_back();
    }

    int top()
    {
        return stack_.back();
    }

    int getMin()
    {
        return min_.back();
    }

private:
    list<int> stack_;
    list<int> min_;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

void test1()
{
}

int main()
{
    test1();
    return 0;
}
