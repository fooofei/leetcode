#include <iostream>
#include <vector>

using namespace std;

// https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array/

class Solution {
public:
    int removeDuplicates(vector<int>& nums)
    {
        if (nums.empty()) {
            return 0;
        }
        int last_val = nums[0];

        vector<int>::iterator b = nums.begin();
        for (b++; b != nums.end();) {

            if (*b == last_val) {
                b = nums.erase(b);
            } else {
                last_val = *b;
                b++;
            }
        }

        return nums.size();
    }
};

int main()
{

    vector<int> data1 = { 1, 1, 2 };

    Solution a;
    a.removeDuplicates(data1);
    std::cout << "main exit\n";
    return 0;
}
