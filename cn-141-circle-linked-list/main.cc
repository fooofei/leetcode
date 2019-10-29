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


struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x)
        : val(x)
        , next(NULL)
    {
    }
};


// 141 https://leetcode-cn.com/problems/linked-list-cycle/

class Solution {
public:
    bool hasCycle(ListNode* head)
    {

        if (head == NULL) {
            return false;
        }

        ListNode* slow = head;
        ListNode* fast = head->next;

        for (; slow != NULL && fast != NULL;) {
            if (slow == fast) {
                return true;
            }

            slow = slow->next;
            fast = fast->next;
            if (fast == NULL) {
                break;
            }
            fast = fast->next;
        }
        return false;
    }
};

void test1()
{
    Solution sln;
}

int main()
{
    test1();
    return 0;
}
