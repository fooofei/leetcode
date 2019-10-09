
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct data_t {
    int data;
};

bool sort_cmp(const struct data_t& last, const struct data_t& first)
{
    // 有 = 号 会导致 sort 无法退出/或者崩溃
    return last.data < first.data;
}

void testSort()
{
    vector<struct data_t> vec;

    for (int i = 0; i < 100; i++) {
        struct data_t d;
        d.data = 2;
        vec.push_back(d);
    }

    vec[33].data = 100;

    sort(vec.begin(), vec.end(), sort_cmp);

    cout << "first= " << (*vec.begin()).data << endl;
    cout << "last=" << (*(vec.end() - 1)).data << endl;
}

int main()
{

    testSort();

    return 0;
}
