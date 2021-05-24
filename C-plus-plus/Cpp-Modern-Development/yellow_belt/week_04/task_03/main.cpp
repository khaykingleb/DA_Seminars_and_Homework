#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
    vector<string> res;
    bool first = true;
    for (auto it = begin(s); it != end(s); ) {
        if (!first) {
            ++it;
        }
        first = false;
        auto at = find(it, end(s), ' ');
        res.push_back({it, at});
        it = at;
    }
    return res;
}
