#include "sum_reverse_sort.h"
#include <algorithm>


int Sum(int x, int y) {
    return x + y;
}

string Reverse(string s) {
    string res = "";
    for (size_t i = s.size() - 1; i > 0; --i) {
        res += s[i];
    }
    res += s[0];
    return res;
}

void Sort(vector<int>& nums) {
    sort(begin(nums), end(nums));
}
