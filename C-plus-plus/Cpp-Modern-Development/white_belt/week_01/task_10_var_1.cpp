#include <iostream>
#include <vector>

using namespace std;

/* На вход дано целое положительное число N. Выведите его в двоичной системе счисления без ведущих нулей.
 * Про перевод в двоичную систему: https://www.yaklass.ru/p/informatika/10-klass/informatciia-i-informatcionnye-protcessy-11955/predstavlenie-chislovoi-informatcii-v-kompiutere-11901/re-62e8903e-ba93-478a-85b5-ae45af40c658. */

int main() {
    int n, w, r;
    cin >> n;
    vector<int> v;

    while (n >= 2) {
        w = n / 2;
        r = n % (w * 2);
        n = w;
        v.push_back(r);
    }

    v.push_back(n);

    for (int i = v.size() - 1; i >= 0; --i) {
          cout << v[i];
    }

    return 0;
}
