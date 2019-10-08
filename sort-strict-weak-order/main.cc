
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct data_t {
    int data;

    bool operator()(const struct data_t& a, const struct data_t& b)
    {
        // 有 = 号 会导致 sort 无法退出/或者崩溃
        return a.data >= b.data;
    }
};

void testSort()
{
    vector<struct data_t> vec;

    for (int i = 0; i < 100; i++) {
        struct data_t d;
        d.data = 2;
        vec.push_back(d);
    }

    struct data_t cmp;
    sort(vec.begin(), vec.end(), cmp);

    cout << "first= " << (*vec.begin()).data << endl;
    cout << "last=" << (*(vec.end() - 1)).data << endl;
}

int main()
{

    testSort();

    return 0;
}
