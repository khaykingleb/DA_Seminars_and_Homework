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


vector<string> PalindromFilter (vector<string> words, int min_length) {
    vector<string> new_words;

    for (auto w : words) {
        if (w.size() >= min_length && IsPalindrom(w)) {
            new_words.push_back(w);
        }
    }

    return new_words;
}