#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void RemoveDuplicates(vector<T>& elements) {
    sort(begin(elements), end(elements));
    elements.erase(unique(begin(elements), end(elements)), end(elements));
}
