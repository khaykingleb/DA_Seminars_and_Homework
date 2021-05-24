#include <iostream>

using namespace std;

/* В stdin даны два натуральных числа. Выведите в stdout их наибольший общий делитель. */

int main() {
    int a, b, c;
    cin >> a >> b;

    // Воспользуемся алгоритмом Евклида
    if (a > b) {
        while (a % b != 0) {
            c = b;
            b = a % b;
            a = c;
        }

        cout << b;

    } else {
        while (b % a != 0) {
            c = a;
            a = b % a;
            b = c;
        }

        cout << a;

    }

    return 0;
}
