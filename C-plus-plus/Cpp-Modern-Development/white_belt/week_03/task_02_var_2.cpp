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

    vector<string> v(n);
    for (string& s : v) {
        cin >> s;
    }

    sort(begin(v), end(v),
         // компаратор для сортировки — лямбда-функция, сравнивающая строки без учёта регистра
         [](const string& l, const string& r) {
         // сравниваем лескикографически ... (https://ru.cppreference.com/w/cpp/algorithm/lexicographical_compare)
             return lexicographical_compare(
                     // ... все символы строки l ...
                     begin(l), end(l),
                     // ... со всеми символами строки r ...
                     begin(r), end(r),
                     // ..., используя в качестве компаратора сравнение отдельных символов без учёта регистра
                     [](char cl, char cr) { return tolower(cl) < tolower(cr); }
             );
         }
    );

    for (const string& s : v) {
        cout << s << " ";
    }

    return 0;
}