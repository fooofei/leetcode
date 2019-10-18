#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

// https://leetcode-cn.com/problems/3sum/

bool sort_cmp(const int& first, const int& last)
{
    return first < last;
}

class Solution {
public:
    vector<vector<int> > threeSum(vector<int>& nums)
    {
        vector<vector<int> > result;

        sort(nums.begin(), nums.end(), sort_cmp);

        for (size_t i = 0; i + 2 < nums.size() && nums[i] <= 0;) {

            size_t j = i + 1;
            size_t k = nums.size() - 1;
            int val1 = nums[i];

            for (; j < k;) {
                int sum = val1 + nums[j] + nums[k];
                if (sum == 0) {
                    result.push_back({ val1, nums[j], nums[k] });

                    // 跳过重复的
                    size_t j1 = j + 1;
                    for (; j1 < k && nums[j1] == nums[j]; j1++) {
                    }
                    j = j1;

                    size_t k1 = k + 1;
                    for (; j < k1 && nums[k1] == nums[k]; k1++) {
                    }
                    k = k1;

                } else if (sum < 0) {
                    j++;
                } else if (sum > 0) {
                    k--;
                }
            }

            size_t i1 = i + 1;

            for (; i1 < nums.size() && nums[i1] == nums[i]; i1++) {
            }
            i = i1;
        }
        return result;
    }
};

int main()
{

    Solution sln;
    (void)sln;

    vector<int> c = {-1, 0, 1, 2, -1, -4};
    auto r = sln.threeSum(c);

    std::cout << "main exit\n";
    return 0;
}
