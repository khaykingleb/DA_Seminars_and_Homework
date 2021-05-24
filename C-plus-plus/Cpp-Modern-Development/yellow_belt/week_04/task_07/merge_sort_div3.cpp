#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin >= 3) {
        vector<typename RandomIt::value_type> elements(range_begin, range_end);
        auto it1 = begin(elements) + elements.size() / 3;
        auto it2 = it1 + elements.size() / 3;
        MergeSort(begin(elements), it1);
        MergeSort(it1, it2);
        MergeSort(it2, end(elements));
        vector<typename RandomIt::value_type> temp;
        merge(begin(elements), it1, it1, it2, back_inserter(temp));
        merge(begin(temp), end(temp), it2, end(elements), range_begin);
    }
}
