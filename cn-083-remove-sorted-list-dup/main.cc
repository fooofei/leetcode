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

// https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x)
        : val(x)
        , next(NULL)
    {
    }
};

typedef struct ListNode ListNode;

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head)
    {
        if (head == NULL) {
            return NULL;
        }

        ListNode* newHead = head;
        ListNode* tail = newHead;
        head = head->next;
        tail->next = NULL;

        for (; head;) {

            ListNode* del = NULL;
            if (head->val != tail->val) {
                tail->next = head;
                tail = head;
                head = head->next;
                tail->next = NULL;
            } else {
                del = head;
                head = head->next;
                delete del;
            }
        }
        return newHead;
    }
};

int main()
{

    Solution sln;
    (void)sln;

    ListNode* a = new ListNode(1);
    ListNode* b = new ListNode(1);
    a->next = b;

    sln.deleteDuplicates(a);

    std::cout << "main exit\n";
    return 0;
}
