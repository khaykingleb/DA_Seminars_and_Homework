/*
Реализуйте шаблонную функцию Sqr, которая работает не только для чисел, но и для контейнеров. 
Функция должна возвращать копию исходного контейнера, модифицировав его следующим образом:
• для vector элементы нужно возвести в квадрат;
• для map в квадрат нужно возвести только значения, но не ключи;
• для pair в квадрат нужно возвести каждый элемент пары.
 */
 

#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

// Предварительное объявление шаблонных функций

template <typename Number> Number Sqr(const Number& number);

template <typename T> vector<T> Sqr(const vector<T>& vec);

template <typename First, typename Second> pair<First, Second> Sqr(const pair<First, Second>& p);

template <typename Key, typename Value> map<Key, Value> Sqr(const map<Key, Value>& m);

// Объявляем шаблонные функции

template <typename Number>
Number Sqr(const Number& number) {
    return number * number;
}

template <typename T>
vector<T> Sqr(const vector<T>& vec) {
    vector<T> vec_new;
    for (const auto& i : vec) {
        vec_new.push_back(Sqr(i));
    }
    return vec_new;
}

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p) {
    return make_pair(Sqr(p.first), Sqr(p.second));
}

template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m) {
    map<Key, Value> m_new;
    for (const auto& [key, value] : m) {
        m_new.insert({key, Sqr(value)});
    }
    return m_new;
}

int main() {
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
            {4, {2, 2}},
            {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }

    return 0;
}
