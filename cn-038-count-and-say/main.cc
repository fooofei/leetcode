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

class Solution {
public:
    map<int, string> cache;

    string countAndSay(int n)
    {
        int start = 1;
        string numString("1");
        int64_t num = 0;

        auto found = cache.find(n);
        if (found != cache.end()) {
            return found->second;
        }

        for (; start < n; start++) {

            found = cache.find(start);
            if (found != cache.end()) {
                numString = found->second;
                continue;
            }
            // not found

            int count = 1;
            char cursorNum = numString[0];
            string tmpString;

            for (size_t i = 1; i < numString.size(); i++) {

                if (numString[i] == cursorNum) {
                    count += 1;
                } else {
                    tmpString.append(to_string(count));
                    tmpString.append(1, cursorNum);
                    count = 1;
                    cursorNum = numString[i];
                }
            }

            tmpString.append(to_string(count));
            tmpString.append(1, cursorNum);
            numString = tmpString;

            cache[start] = numString;
        }

        return numString;
    }
};

int main()
{

    Solution a;
    auto r = a.countAndSay(1);
    cout << "1= " << r << endl;

    r = a.countAndSay(2);
    cout << "2= " << r << endl;

    r = a.countAndSay(3);
    cout << "3= " << r << endl;

    r = a.countAndSay(4);
    cout << "4= " << r << endl;

    r = a.countAndSay(5);
    cout << "5= " << r << endl;
    std::cout << "main exit\n";
    return 0;
}
