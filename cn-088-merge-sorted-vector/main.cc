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

// 088 https://leetcode-cn.com/problems/merge-sorted-array/submissions/

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
    {

        vector<int> dummy;
        dummy.swap(nums1);
        dummy.resize(m);

        size_t minSize = (size_t)min(m, n);

        size_t i = 0;
        size_t j = 0;

        for (; i < dummy.size() && j < nums2.size();) {
            if (dummy[i] < nums2[j]) {
                nums1.push_back(dummy[i]);
                i++;
            } else {
                nums1.push_back(nums2[j]);
                j++;
            }
        }

        for (; i < dummy.size(); i++) {
            nums1.push_back(dummy[i]);
        }

        for (; j < nums2.size(); j++) {
            nums1.push_back(nums2[j]);
        }
    }
};

int main()
{

    Solution sln;
    (void)sln;

    std::cout << "main exit\n";
    return 0;
}
