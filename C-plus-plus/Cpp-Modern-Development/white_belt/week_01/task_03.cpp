#include <iostream>
#include <string>

using namespace std;

/* В стандартном потоке даны три строки, разделённые пробелом.
 * Каждая строка состоит из строчных латинских букв и имеет длину не более 30 символов.
 * Выведите в стандартный вывод лексикографически минимальную из них.*/

int main() {
    string a, b, c;
    cin >> a >> b >> c;

    if (a <= b && a <= c) {
        cout << a;
    } else {
        if (b <= a && b <= c) {
            cout << b;
        } else {
            cout << c;
        }
    }

    return 0;
}