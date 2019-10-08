#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Solution {

public:
    int addToWindow(list<int>& windowIndex, vector<int>& nums, int minIndex, int index)
    {
        // 降序 6 4 2
        //   false false true
        //  found 5
        auto found = upper_bound(windowIndex.begin(), windowIndex.end(), index,
            [nums](const int& target, const int& mid) -> bool {
                return nums[mid] < nums[target];
            });

        if (found == windowIndex.end()) {
            windowIndex.push_back(index);
        } else {
            // insert at before found
            windowIndex.insert(found, index);
        }

        while (windowIndex.size() > 0 && windowIndex.front() < minIndex) {
            windowIndex.pop_front();
        }

        return windowIndex.empty() ? -1 : windowIndex.front();
    }

public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k)
    {
        vector<int> windowMax;
        size_t windowSize = k;
        list<int> window;
        int maxIndex = 0;

        windowSize = min(windowSize, nums.size());
        if (windowSize <= 0) {
            return windowMax;
        }

        int i = 0;
        for (i = 0; i < windowSize; i++) {
            maxIndex = addToWindow(window, nums, 0, i);
        }
        windowMax.push_back(nums[maxIndex]);

        for (; i < nums.size(); i++) {
            maxIndex = addToWindow(window, nums, i - windowSize + 1, i);
            if (maxIndex >= 0) {
                windowMax.push_back(nums[maxIndex]);
            }
        }
        return windowMax;
    }
};

int main()
{
    Solution a;
    vector<int> n = { 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 3, 2 };

    auto r = a.window(n);

    for (size_t i = 0; i < r.size(); i++) {
        cout << r[i] << " of ";
        for (size_t j = 0; j < 3; j++) {
            cout << n[i + j] << " ";
        }
        cout << "\n";
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
