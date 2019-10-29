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

// 160  https://leetcode-cn.com/problems/intersection-of-two-linked-lists/

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x)
        : val(x)
        , next(NULL)
    {
    }
};

class Solution1 {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
    {
        list<ListNode*> a;
        list<ListNode*> b;

        // 未考虑到的测试
        if (headA == headB) {
            return headA;
        }

        for (; headA;) {
            a.push_front(headA);
            headA = headA->next;
        }

        for (; headB;) {
            b.push_front(headB);
            headB = headB->next;
        }

        if (a.size() == 0 || b.size() == 0) {
            return NULL;
        }

        for (; a.size() > 0 && b.size() > 0;) {
            headA = a.front();
            a.pop_front();
            headB = b.front();
            b.pop_front();

            if (headA != headB) {
                return headA->next;
            }
        }

        // 未考虑到的测试
        if (a.size() > 0) {
            return a.front()->next;
        }
        if (b.size() > 0) {
            return b.front()->next;
        }

        return NULL;
    }
};

// 看了解答才明白的解法

class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
    {
        ListNode* pa = headA;
        ListNode* pb = headB;

        if (headA == NULL || headB == NULL) {
            return NULL;
        }

        for (; pa != pb;) {

            if (pa == NULL) {
                pa = headB;
            } else {
                pa = pa->next;
            }

            if (pb == NULL) {
                pb = headA;
            } else {
                pb = pb->next;
            }
        }
        return pa;
    }
};

void test2()
{
    ListNode* na0 = new ListNode(4);
    ListNode* na1 = new ListNode(1);
    ListNode* na2 = new ListNode(8);
    ListNode* na3 = new ListNode(4);
    ListNode* na4 = new ListNode(5);

    ListNode* nb0 = new ListNode(5);
    ListNode* nb1 = new ListNode(0);
    ListNode* nb2 = new ListNode(1);

    na0->next = na1;
    na1->next = na2;
    na2->next = na3;
    na3->next = na4;

    nb0->next = nb1;
    nb1->next = nb2;
    nb2->next = na2;

    Solution sln;

    auto r = sln.getIntersectionNode(na0, nb0);
    printf("%p", r);
}

void test1()
{

    ListNode* na0 = new ListNode(3);

    ListNode* nb0 = new ListNode(2);
    nb0->next = na0;
    Solution sln;

    auto r = sln.getIntersectionNode(na0, nb0);
    printf("%p", r);
}

int main()
{
    test1();
    return 0;
}
