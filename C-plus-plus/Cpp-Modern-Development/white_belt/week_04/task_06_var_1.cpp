#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
    ifstream input("input.txt");
    int rows, columns;
    input >> rows >> columns;

    vector<vector<int>> values(rows);

    for (int i = 0; i < rows; ++ i) {
        for (int j = 0; j < columns; ++j) {
            int value;
            input >> value;
            values[i].push_back(value);

            input.ignore(1);
        }
    }

    for (int i = 0; i < rows; ++ i) {
        for (int j = 0; j < columns; ++j) {
            cout << setw(10) << values[i][j];
            if (j != columns - 1) {
                cout << " ";
            }
        }
        if (i != n - 1) {
            cout << endl;
        }
    }

    return 0;
}
