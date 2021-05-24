#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream input("input.txt");
    if (input) {
        string line;
        while (getline(input, line)) {
            cout << line << endl;
        }
    }

    ifstream input_new("input.txt");
    ofstream output("output.txt");

    if (input_new) {
        string line;
        while (getline(input_new, line)) {
            output << line << endl;
        }
    }
}