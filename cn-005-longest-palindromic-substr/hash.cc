#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <stack>
#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <thread>
#include <vector>

using namespace std;

// 005 https://leetcode-cn.com/problems/longest-palindromic-substring/

// ((('a')*233+'b')*233+'b')*233 + 'c'
// 'a' + 'b'*233 + 'b'*233*233 +'c'*233*233*233

// Remove 'c'
// ((('a')*233+'b')*233+'b')
// 'a' + 'b'*233 + 'b'*233*233

// Remove 'a'
// (('b'*233)+'b')*233+'c'
// 'b'+'b'*233 + 'c'*233*233

struct HashNode {
    int first;
    int last;
    uint64_t flhash; // ((('a')*233+'b')*233+'b')*233 + 'c'
    uint64_t lfhash; // 'a' + 'b'*233 + 'b'*233*233 +'c'*233*233*233
    uint64_t base;
    HashNode()
    {
        first =0;
        last = 0;
        flhash =0;
        lfhash = 0;
        base = 0;
    }

};
using HashNode = struct HashNode;

void Palindrome(const string& s, const vector<HashNode>& nodes, uint64_t seed, string* maxRome)
{
    vector<HashNode> subNodes;
    for (int i = 0; i < (int)nodes.size(); i++) {
        const HashNode& node = nodes[i];

        if (node.flhash == node.lfhash) {
            *maxRome = s.substr(node.first, node.last - node.first);
            return;
        }

        // 只计算少末尾字符的
        HashNode subNode;
        subNode.first = node.first;
        subNode.last = node.last - 1;
        subNode.flhash = node.flhash - s[node.last - 1];
        subNode.flhash /= seed;
        subNode.lfhash = node.lfhash - s[node.last - 1] * node.base;
        subNode.base = node.base / seed;
        subNodes.push_back(subNode);
    }

    if (nodes.size() > 0) {
        const HashNode& parentLast = nodes[nodes.size() - 1];
        HashNode lastNode;

        // 如果是 2 个字符不相等了，就直接返回 1 个字符的
        if (parentLast.first + 2 == parentLast.last) {
            *maxRome += s[0];
            return;
        }

        lastNode.first = parentLast.first + 1;
        lastNode.last = parentLast.last;
        lastNode.flhash = parentLast.flhash - s[parentLast.first] * parentLast.base;
        lastNode.lfhash = parentLast.lfhash - s[parentLast.first];
        lastNode.lfhash /= seed;
        lastNode.base = parentLast.base / seed;
        subNodes.push_back(lastNode);
    }
    if (subNodes.size() > 0) {
        Palindrome(s, subNodes, seed, maxRome);
    }
}

class Solution {

public:
    string longestPalindrome(string s)
    {
        string maxRome;
        vector<HashNode> nodes;
        HashNode node;

        if (s.size() < 2) {
            return s;
        }
        uint64_t seed = 26;
        node.first = 0;
        node.last = s.size();
        uint64_t base = 1;
        node.flhash = 0;

        for (int i = 0; i < (int)s.size(); i++) {
            node.flhash = node.flhash * seed + s[i];
            node.base = base;
            base *= seed;
        }
        node.lfhash = 0;
        for (int i = (int)s.size() - 1; i >= 0; i--) {
            node.lfhash = node.lfhash * seed + s[i];
        }
        nodes.push_back(node);
        Palindrome(s, nodes, seed, &maxRome);
        return maxRome;
    }
};

void test2()
{
    Solution sln;

    auto r = sln.longestPalindrome("babad");
    if (r != "bab") {
        printf("%s() fail\n", __func__);
    }
}

void test3()
{
    Solution sln;

    auto r = sln.longestPalindrome("cbbd");
    if (r != "bb") {
        printf("%s() fail\n", __func__);
    }
}

void test1()
{
    Solution sln;

    auto r = sln.longestPalindrome("babaddtattarrattatddetartrateedredividerb");
    if (r != "ddtattarrattatdd") {
        printf("%s() fail\n", __func__);
    }
}

int main()
{
    Solution sln;
    (void)sln;

    test1();
    return 0;
}
