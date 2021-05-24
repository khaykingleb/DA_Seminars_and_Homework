#include <iostream>
#include <string>

using namespace std;

/* Дана строка. Найдите в этой строке второе вхождение буквы f и выведите индекс этого вхождения. Если буква f в
 * данной строке встречается только один раз, выведите число -1, а если не встречается ни разу, выведите число -2. */

int main() {
    string s;
    cin >> s;

    int i = 0;
    int cnt = 0;
    for (auto c : s) {
        if (c == 'f') {
            ++cnt;
            if (cnt == 2) {
                cout << i;
            }
        }
        ++i;
    }

    if (cnt == 1) {
        cout << -1;
    } else if (cnt == 0) {
        cout << -2;
    }
    return 0;
}
