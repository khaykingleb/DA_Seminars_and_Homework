/* 
 # Пример использования шаблонов функций
 */

#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <utility>
#include <string>

using namespace std;

// Предварительное объявление шаблонных функций

template <typename First, typename Second>
ostream& operator << (ostream& out, const pair<First, Second>& p);

template <typename T>
ostream& operator << (ostream& out, const vector<T>& vec);

template <typename Key, typename Value>
ostream& operator << (ostream& out, const map<Key, Value>& m);

template <typename Collection>
string Join(const Collection& c, char d) {
    stringstream stream;
    bool first = true;
    for (const auto& i : c) {
        if (!first) {
            stream << d;
        }
        first = false;
        stream << i;
    }
    return stream.str();
}

// Объявляем шаблонные функции

template <typename First, typename Second>
ostream& operator << (ostream& out, const pair<First, Second>& p) {
    return out << '(' << p.first << ',' << p.second << ')';
}

template <typename T>
ostream& operator << (ostream& out, const vector<T>& vec) {
    return out << '[' << Join(vec, ',') << ']';
}

template <typename Key, typename Value>
ostream& operator << (ostream& out, const map<Key, Value>& m) {
    return out << '{' << Join(m, ',') << '}';
}

int main() {
    vector<double> vi = {1.4, 2, 3};
    cout << vi << endl;
    map<int, double> m = {{1, 2.5}, {3, 4}};
    cout << m << endl;
    vector<vector<int>> v = {{1, 2}, {3, 4}};
    cout << v << endl;
    return 0;
}
