#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
    ifstream input("input.txt");

    int n, m;
    input >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x;
            input >> x;
            input.ignore(1);
            cout << setw(10) << x;

            // выводим пробел, если только этот столбец не последний
            if (j != m - 1) {
                cout << " ";
            }
        }
        // выводим перевод строки, если только эта строка не последняя
        if (i != n - 1) {
            cout << endl;
        }
    }

    return 0;
}