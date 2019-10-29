#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

using namespace std;

// 001 https://leetcode-cn.com/problems/two-sum/

struct WithIndex {
    int index;
    int value;
};

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target)
    {
        vector<WithIndex> with_index;
        with_index.resize(nums.size());
        for (int i = 0; i < nums.size(); i++) {
            with_index[i].index = i;
            with_index[i].value = nums[i];
        }

        sort(with_index.begin(), with_index.end(), [](const WithIndex& first, const WithIndex& last) -> bool {
            return first.value < last.value;
        });

        vector<int> result;
        result.resize(2, -1);

        if (with_index.size() < 2) {
            return result;
        }

        int i = 0;
        int j = with_index.size() - 1;
        for (; i < j;) {

            const WithIndex& a = with_index[i];
            const WithIndex& b = with_index[j];
            if (a.value + b.value < target) {
                i++;

            } else if (a.value + b.value > target) {
                j--;
            } else {
                result[0] = with_index[i].index;
                result[1] = with_index[j].index;
                break;
            }
        }

        return result;
    }
};

int main()
{

    vector<int> data1 = { 1, 1, 2 };
    vector<int> data2 = { 3, 2, 4 };

    Solution a;
    a.twoSum(data2, 6);
    std::cout << "main exit\n";
    return 0;
}
