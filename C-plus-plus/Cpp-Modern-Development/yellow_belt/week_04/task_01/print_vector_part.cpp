#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void PrintVectorPart(const vector<int>& vec) {
    auto negative_it = find_if(
            begin(vec),
            end(vec),
            [](int number) {
                return number < 0;
            }
    );

    for (auto it = negative_it; it != begin(vec); ) {
        cout << *(--it) << " ";
    }
}
