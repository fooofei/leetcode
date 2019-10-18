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

// https://leetcode-cn.com/problems/maximum-subarray/

struct Node {
    int startIndex;
    int endIndex; // [start, end)
    int valueIndex;

    struct Node* parent;
    struct Node* left;
    struct Node* right;
};

class SegmentTree {
public:
    using value_t = int;
    using container_t = vector<int>;

    SegmentTree()
    {
        root_ = NULL;
    }
    ~SegmentTree()
    {
        for (auto it : freeNodes_) {
            free(it);
        }
        freeNodes_.clear();
    }

    void from(const container_t& vec)
    {
        root_ = makeNode(0, vec.size(), vec, NULL);
    }

    int find(int start, int end, const container_t& vec)
    {
        return searchNode(root_, start, end, vec);
    }

private:
    list<struct Node*> freeNodes_;
    struct Node* root_;

    struct Node* allocNode()
    {
        struct Node* n = (struct Node*)calloc(1, sizeof(struct Node));
        freeNodes_.push_back(n);
        return n;
    }

    struct Node* makeNode(int start, int end, const container_t& vec, struct Node* parent)
    {
        struct Node* n = allocNode();
        n->startIndex = start;
        n->endIndex = end;
        n->valueIndex = -1;
        n->parent = parent;

        if (start == end - 1) {
            n->valueIndex = start;
            return n;
        }
        int mid = (int)((uint32_t(start) + end) / 2);
        n->left = makeNode(start, mid, vec, n);
        n->right = makeNode(mid, end, vec, n);

        const value_t& left = vec.at(n->left->valueIndex);
        const value_t& right = vec.at(n->right->valueIndex);
        if (left < right) {
            n->valueIndex = n->left->valueIndex;
        } else {
            n->valueIndex = n->right->valueIndex;
        }
        return n;
    }

    int searchNode(struct Node* n, int start, int end, const container_t& vec)
    {
        if (start == n->startIndex && end == n->endIndex) {
            return n->valueIndex;
        }

        if (start == end - 1) {
            return start;
        }
        int mid = (int)((uint32_t(n->startIndex) + n->endIndex) / 2);

        if (end <= mid) {
            return searchNode(n->left, start, end, vec);
        }
        if (start >= mid) {
            return searchNode(n->right, start, end, vec);
        }
        int leftIndex = searchNode(n->left, start, mid, vec);
        int rightIndex = searchNode(n->right, mid, end, vec);

        const value_t& left = vec.at(leftIndex);
        const value_t& right = vec.at(rightIndex);
        if (left < right) {
            return leftIndex;
        } else {
            return rightIndex;
        }
    }
};

bool sort_cmp(const int& first, const int& last)
{
    return first > last;
}

class Solution {
public:
    // 在 [start. end) 之间的最大连续子数组和
    void internal(SegmentTree& trie, vector<int>& nums, vector<int>& maxSums, int start, int end)
    {
        if (start == end - 1) {
            maxSums.push_back(nums[start]);
            return;
        }

        int minIndex = trie.find(start, end, nums);

        int leftSum = 0;
        int rightSum = 0;

        // 不与极小值做加和
        for (int i = start; i < minIndex; i++) {
            leftSum += nums[i];
        }
        for (int i = minIndex + 1; i < end; i++) {
            rightSum += nums[i];
        }

        // 错误点：当前的值也要看
        maxSums.push_back(leftSum + rightSum + nums[minIndex]);

        if (minIndex == start) {
            // 错误点：左边值没有的，丢掉
            maxSums.push_back(rightSum);
        } else if (minIndex + 1 == end) {
            // 错误点：右边值没有的 丢掉
            maxSums.push_back(leftSum);
        } else {
            maxSums.push_back(max(leftSum, rightSum));
        }

        if (start < minIndex) {
            internal(trie, nums, maxSums, start, minIndex);
        }
        if (minIndex + 1 < end) {
            internal(trie, nums, maxSums, minIndex + 1, end);
        }
    }

    int maxSubArray(vector<int>& nums)
    {
        vector<int> maxSums;
        SegmentTree trie;

        if (nums.size() == 0) {
            return 0;
        }
        if (nums.size() == 1) {
            return nums[0];
        }
        trie.from(nums);

        internal(trie, nums, maxSums, 0, nums.size());

        sort(maxSums.begin(), maxSums.end(), sort_cmp);

        return maxSums[0];
    }
};

int main()
{

    Solution a;
    (void)a;

    vector<int> vec1 = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    vector<int> vec2 = { -2, -1 };
	// 这个测试用例证明按照极小值分割左右求值 是错误的
    vector<int> vec = { 31, -41, 59, 26, -53, 58, 97, -93, -23, 84 };

    auto r = a.maxSubArray(vec);

    cout << "max = " << r << endl;

    std::cout << "main exit\n";
    return 0;
}
