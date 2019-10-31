#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <stack>
#include <string>
#include <vector>

using namespace std;

// 021 https://leetcode-cn.com/problems/merge-two-sorted-lists/

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x)
        : val(x)
        , next(NULL)
    {
    }
};

class Solution {
public:
    ListNode* advance(ListNode** l1, ListNode** l2)
    {

        if (*l1 && *l2) {
            if ((*l1)->val < (*l2)->val) {
                ListNode* r = *l1;
                (*l1) = (*l1)->next;
                return r;
            } else {
                ListNode* r = *l2;
                (*l2) = (*l2)->next;
                return r;
            }
        }

        if (*l1) {
            ListNode* r = *l1;
            (*l1) = (*l1)->next;
            return r;
        }
        if (*l2) {
            ListNode* r = *l2;
            (*l2) = (*l2)->next;
            return r;
        }
        return NULL;
    }

    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
    {
        ListNode* l = NULL;
        ListNode* head = NULL;

        head = advance(&l1, &l2);
        if (head == NULL) {
            return head;
        }
        l = head;

        for (; l1 != NULL || l2 != NULL;) {
            l->next = advance(&l1, &l2);
            l = l->next;
        }
        l->next = NULL;
        return head;
    }
};

int main()
{

    Solution a;
    std::cout << "main exit\n";
    return 0;
}
