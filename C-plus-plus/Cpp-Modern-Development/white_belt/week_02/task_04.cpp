#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/* Даны значения температуры, наблюдавшиеся в течение N подряд идущих дней. Найдите номера дней (в нумерации с нуля) со
 * значением температуры выше среднего арифметического за все N дней.
 *
 * Гарантируется, что среднее арифметическое значений температуры является целым числом. */

int main() {
    int n;
    cin >> n;
    vector<int> temps(n);

    int sum = 0;
    for (int& t : temps){
        cin >> t;
        sum += t;
    }

    int avg_temp = sum / n;

    vector<int> res_indices;
    for (int i = 0; i < temps.size(); ++i){
        if (temps[i] > avg_temp){
            res_indices.push_back(i);
        }
    }

    cout << res_indices.size() << endl;
    for (auto i : res_indices) {
        cout << i << " ";
    }

    return 0;
}
