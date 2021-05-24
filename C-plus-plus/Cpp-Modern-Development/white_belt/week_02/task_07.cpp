#include <iostream>
#include <map>
using namespace std;

/*
 Слова называются анаграммами друг друга, если одно из них можно получить перестановкой букв в другом. Например, слово
 «eat» можно получить перестановкой букв слова «tea», поэтому эти слова являются анаграммами друг друга. Даны пары слов,
 проверьте для каждой из них, являются ли слова этой пары анаграммами друг друга.
 */

map<char, int> BuildCharCounters(const string& word) {
    map<char, int> result;

    for (const auto& s : word) {
        ++result[s];
    }

    return result;
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string word_1, word_2;
        cin >> word_1 >> word_2;

        if (BuildCharCounters(word_1) == BuildCharCounters(word_2)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }

    }
    return 0;
}