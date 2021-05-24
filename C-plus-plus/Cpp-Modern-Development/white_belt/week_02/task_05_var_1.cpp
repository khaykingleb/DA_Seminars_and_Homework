#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/* Люди стоят в очереди, но никогда не уходят из её начала, зато могут приходить в конец и уходить оттуда. Более того,
 * иногда некоторые люди могут прекращать и начинать беспокоиться из-за того, что очередь не продвигается.
 *
 * Реализуйте обработку следующих операций над очередью:
 * WORRY i: пометить i-го человека с начала очереди (в нумерации с 0) как беспокоящегося;
 * QUIET i: пометить i-го человека как успокоившегося;
 * COME k: добавить k спокойных человек в конец очереди;
 * COME -k: убрать k человек из конца очереди;
 * WORRY_COUNT: узнать количество беспокоящихся людей в очереди.
 *
 * Изначально очередь пуста. */

void come(vector<int>& v, int k) {
    v.resize(v.size() + k, 0);
}

void worry(vector<int>& v, int i) {
    v[i] = 1;
}

void quiet(vector<int>& v, int i) {
    v[i] = 0;
}

int worry_count(const vector<int>& v){
     return count(v.begin(), v.end(), 1);
}

int main() {
    vector<int> queue;
    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        string s;
        int num;
        cin >> s;

        if (s == "COME"){
            cin >> num;
            come(queue, num);
        } else if (s == "WORRY") {
            cin >> num;
            worry(queue, num);
        } else if (s == "QUIET") {
            cin >> num;
            quiet(queue, num);
        } else { // "WORRY_COUNT"
            cout << worry_count(queue) << endl;
        }
    }

    return 0;
}
