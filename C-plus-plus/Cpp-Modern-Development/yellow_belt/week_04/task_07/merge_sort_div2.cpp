#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin >= 2) {
        vector<typename RandomIt::value_type> elements(range_begin, range_end);
        auto it = begin(elements) + elements.size() / 2;
        MergeSort(begin(elements), it);
        MergeSort(it, end(elements));
        merge(begin(elements), it, it, end(elements), range_begin);
    }
}
