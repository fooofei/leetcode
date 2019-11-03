
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Data {
    int data;
};
using Data = struct Data;

bool SortCmp(const Data& last, const Data& first)
{
    // 有 = 号 会导致 sort 无法退出/或者崩溃
    return last.data < first.data;
}

void TestSort()
{
    vector<Data> vec;

    for (int i = 0; i < 100; i++) {
        Data d;
        d.data = 2;
        vec.push_back(d);
    }

    vec[33].data = 100;

    sort(vec.begin(), vec.end(), SortCmp);

    cout << "first= " << (*vec.begin()).data << endl;
    cout << "last=" << (*(vec.end() - 1)).data << endl;
}

int main()
{
    TestSort();
    return 0;
}
