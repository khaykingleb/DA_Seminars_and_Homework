/*
 В стандартном потоке дана одна строка, состоящая из числа N и следующих за ним N строк S.
 Между собой число и строки разделены пробелом.

 Отсортируйте строки S в лексикографическом порядке по возрастанию, игнорируя регистр букв, и выведите их
 в стандартный поток вывода.
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<string> v;

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        v.push_back(s);
    }

    sort(begin(v), end(v),
         [](const string& s_1, const string& s_2) {
             string new_s_1, new_s_2;

             for (char c : s_1) {
                 new_s_1 += tolower(c);
             }
             for (char c : s_2) {
                 new_s_2 += tolower(c);
             }

             return new_s_1 < new_s_2;

         });


    for (const auto& i : v){
        cout << i << " ";
    }

    return 0;
}