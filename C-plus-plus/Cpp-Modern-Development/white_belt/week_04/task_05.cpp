#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
    vector<double> values;

    ifstream input("input.txt");

    string line;
    while(getline(input, line)) {
        values.push_back(stod(line));
    }

    cout << fixed << setprecision(3);

    for (const double& v : values) {
        cout << v << endl;
    }

    return 0;
}