/*
  В стандартном потоке дана одна строка, состоящая из N + 1 целых чисел. Первым числом идёт само число N. Далее следуют
  ещё N чисел, обозначим их за массив A. Между собой числа разделены пробелом.
  
  Отсортируйте массив А по модулю и выведите его в стандартный поток.
 */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> v;

    for (int i = 0; i < n; ++i) {
        int n_i;
        cin >> n_i;
        v.push_back(n_i);
    }

    sort(begin(v), end(v), [](int i, int j) { return abs(i) < abs(j); });

    for (const auto& i : v){
        cout << i << " ";
    }

    return 0;
}