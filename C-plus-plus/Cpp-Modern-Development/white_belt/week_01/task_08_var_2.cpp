#include <iostream>
#include <string>

using namespace std;

/* Дана строка. Найдите в этой строке второе вхождение буквы f и выведите индекс этого вхождения. Если буква f в
 * данной строке встречается только один раз, выведите число -1, а если не встречается ни разу, выведите число -2. */

int main() {
    string s;
    cin >> s;

    //  если f ни разу не встретится, он останется равным -2
    int result = -2;

    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'f') {
            if (result == -2) {
                result = -1;
            } else if (result == -1) {
                result = i;
                break;
            }
        }
    }

    cout << result;

    return 0;
}
