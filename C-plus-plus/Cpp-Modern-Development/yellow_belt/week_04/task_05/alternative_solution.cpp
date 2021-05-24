#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> vec(n);

    // iota -> http://ru.cppreference.com/w/cpp/algorithm/iota
    // Заполняет диапазон последовательно возрастающими значениями
    // Обратные итераторы позволяют заполнить его, двигаясь от конца к началу
    iota(vec.rbegin(), vec.rend(), 1);

    // prev_permutation -> http://ru.cppreference.com/w/cpp/algorithm/prev_permutation
    // Преобразует диапазон в предыдущую (лексикографически) перестановку,
    // если она существует, и возвращает true,
    // иначе (если не существует) - в последнюю (наибольшую) и возвращает false
    do {
        for (int i : vec) {
            cout << i << " ";
        }
        cout << endl;
    } while (prev_permutation(begin(vec), end(vec)));

    return 0;
}
