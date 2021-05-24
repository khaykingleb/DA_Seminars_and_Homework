#include <iostream>
#include <vector>
#include <string>
using namespace std;


bool IsPalindrom(string s) {
    string new_s;

    for (int i = s.size() - 1; i >= 0; --i) {
        new_s += s[i];
    }

    if (s == new_s){
        return true;
    } else {
        return false;
    }
}

int main() {
    string word;
    cin >> word;
    cout << IsPalindrom(word);
    return 0;
}
