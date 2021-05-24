#include <iostream>

using namespace std;

void EnsureEqual(const string& s1, const string& s2) {
    if (s1 != s2) {
        throw runtime_error(s1 + " != " + s2);
    }
}

int main() {
    try {
        EnsureEqual("C++ White", "C++ White");
        EnsureEqual("C++ White", "C++ Yellow");
    } catch (runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}