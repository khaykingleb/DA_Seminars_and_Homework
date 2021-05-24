#include "sum_reverse_sort.h"
#include <iostream>

using namespace std;

int main() {
    vector<int> v = {4, 3, 2, 1};
    string s = Reverse("HSE");
    cout << s << endl;

    Sort(v);
    for (auto& i : v) {
        cout << i << " ";
    }

    return 0;
}
