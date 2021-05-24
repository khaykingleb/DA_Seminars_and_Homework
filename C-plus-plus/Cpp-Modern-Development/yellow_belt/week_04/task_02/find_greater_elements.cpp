#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& element, const T& border) {
    vector<T> res;
    auto it = begin(element);
    while (it != end(element)) {
        if (*it > border) {
            res.push_back(*it);
            ++it;
        } else {
            ++it;
        }
    }
    return res;
}
