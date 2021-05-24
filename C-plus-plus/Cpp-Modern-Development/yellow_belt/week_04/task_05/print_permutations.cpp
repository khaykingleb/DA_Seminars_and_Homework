#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> vec(n);
    int cnt = vec.size();
    for (int& i : vec) {
        i += cnt;
        --cnt;
    }

    do {
        for (const int& i : vec) {
            cout << i << " ";
        }
        cout << endl;
     } while (prev_permutation(begin(vec), end(vec)));

    return 0;
}
