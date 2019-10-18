#include <iostream>
#include <vector>

using namespace std;

// https://leetcode-cn.com/problems/remove-element/

class Solution {
public:
    int removeElement(vector<int>& nums, int val)
    {
        vector<int>::iterator b = nums.begin();
        for (; b != nums.end();) {

            if (*b == val) {
                b = nums.erase(b);
            } else {
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
    a.removeElement(data1, 1);
    std::cout << "main exit\n";
    return 0;
}
