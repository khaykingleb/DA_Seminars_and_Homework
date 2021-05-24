#include <iostream>
#include <vector>
using namespace std;

/* На вход дано целое положительное число N. Выведите его в двоичной системе счисления без ведущих нулей.
 * Про перевод в двоичную систему: https://www.yaklass.ru/p/informatika/10-klass/informatciia-i-informatcionnye-protcessy-11955/predstavlenie-chislovoi-informatcii-v-kompiutere-11901/re-62e8903e-ba93-478a-85b5-ae45af40c658. */

int main() {
    int n;
    vector<int> v;

    cin >> n;

    while (n > 0){
        v.push_back(n % 2);
        n /= 2;
    }

    for (int i = v.size() - 1; i >= 0; --i) {
        cout << v[i];
    }

    return 0;
}
