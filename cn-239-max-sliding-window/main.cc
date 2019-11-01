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
// 239 https://leetcode-cn.com/problems/sliding-window-maximum/
// 20191008 反省，第一个版本没反应过来，如何保证窗口内的数据总是有序的
//  以及没反应过来，如何保证移除窗口内的老数据的时候如何做到重新找到最大值
//  比如 6 5 4 3 2，窗口为 3 个，窗口 [6,5,4] 变更到 [5,4,3] 时，
//  如果在 [6,5,4] 的时候，因为 5,4 都小于 6， 因此删除 5,4，  那么下一个窗口
//  就只剩 [6,3] ，6 移除窗口后，就只剩 [3]，这样不对，
//
//  应该是这样的
//  如何保证窗口内的数据有序，使用单调栈保证，栈内的 value 递减 ， index 递增
//  如何保证窗口移动时，能得到窗口内的极值，一定是所有值的极值，
//      因为每次入窗口（滑动窗口），都会判断当前入的值与栈顶的值比较，
//      如果新加入的是比栈顶更小（或等于）的，就入栈，这样知道最大值走后，谁更大
//      如果新加入的是比栈顶更大的，就一直出栈到比栈顶小，刷新了极大值



struct WithIndex {
    int index;
    int value;
};

using window_t = list<struct WithIndex>;

class Solution {

public:
    void addToWindow(window_t& windowIndex, int minIndex, const WithIndex& cur)
    {
        // 从右边移除值小于当前值的
        for (; windowIndex.size() > 0 && windowIndex.back().value < cur.value;) {
            windowIndex.pop_back();
        }

        if (windowIndex.size() > 0 && windowIndex.front().index < minIndex) {
            windowIndex.pop_front();
        }
        windowIndex.push_back(cur);
    }

    vector<int> maxSlidingWindow(vector<int>& nums, int k)
    {
        vector<int> windowMax;
        int windowSize = k;
        window_t window;

        windowSize = min(windowSize, (int)nums.size());
        if (windowSize <= 0) {
            return windowMax;
        }
        if (windowSize <= 1) {
            return nums;
        }

        int i = 0;
        for (i = 0; i < windowSize - 1; i++) {
            WithIndex cur = { i, nums[i] };
            addToWindow(window, 0, cur);
        }
        for (; i < nums.size(); i++) {
            WithIndex cur = { i, nums[i] };
            addToWindow(window, i - windowSize + 1, cur);
            windowMax.push_back(window.front().value);
        }
        return windowMax;
    }
};

int main()
{
    Solution a;
    vector<int> n = { 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 3, 2 };

    auto r = a.maxSlidingWindow(n, 3);

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
