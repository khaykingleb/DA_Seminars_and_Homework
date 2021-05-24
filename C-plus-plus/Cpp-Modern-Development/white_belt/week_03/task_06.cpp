/*
   Дополните класс Person из задачи «Имена и фамилии — 2» конструктором, позволяющим задать имя и фамилию человека при
   рождении, а также сам год рождения. Класс не должен иметь конструктора по умолчанию.

   При получении на вход года, который меньше года рождения:
   • методы GetFullName и GetFullNameWithHistory должны отдавать "No person";
   • методы ChangeFirstName и ChangeLastName должны игнорировать запрос.

   Кроме того, необходимо объявить константными все методы, которые по сути ими являются.
 */

#include <algorithm>
#include <map>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> FindNamesHistory(const map<int, string>& names_by_year, int year) {
    vector<string> names;
    // перебираем всю историю в хронологическом порядке
    for (const auto& item : names_by_year) {
        // если очередное имя не относится к будущему и отличается от предыдущего, добавляем его в историю
        if (item.first <= year && (names.empty() || names.back() != item.second)) {
            names.push_back(item.second);
        }
    }

    return names;
}

string BuildFullName(const string& first_name, const string& last_name) {
    if (first_name.empty() && last_name.empty()) {
        return "No person";
    } else if (first_name.empty()) {
        return last_name + " with unknown first name";
    } else if (last_name.empty()) {
        return first_name + " with unknown last name";
    } else {
        return first_name + " " + last_name;
    }
}

string BuildJoinedName(vector<string> names){
    // нет истории — имя неизвестно
    if (names.empty()) {
        return "";
    }

    // меняем прямой хронологический порядок на обратный
    reverse(begin(names), end(names));

    // начинаем строить полное имя с самого последнего
    string joined_name = names[0];

    // перебираем все последующие имена
    for (int i = 1; i < names.size(); ++i) {
        if (i == 1) {
            // если это первое «историческое» имя, отделяем его от последнего скобкой
            joined_name += " (";
        } else {
            // если это не первое имя, отделяем от предыдущего запятой
            joined_name += ", ";
        }
        // и добавляем очередное имя
        joined_name += names[i];
    }

    // если в истории было больше одного имени, мы открывали скобку — закроем её
    if (names.size() > 1) {
        joined_name += ")";
    }

    return joined_name;
}


class Person {
public:
    // Конструктор
    Person(const string& fisrt_name, const string& last_name, int year) {
        first_names[year] = fisrt_name;
        last_names[year] = last_name;
    }

    void ChangeFirstName(int year, const string& first_name) {
        first_names[year] = first_name;
    }

    void ChangeLastName(int year, const string& last_name) {
        last_names[year] = last_name;
    }

    string GetFullName(int year) const {
        // найдём историю изменений имени и фамилии
        // в данном случае это излишне, так как нам достаточно узнать последние имя и фамилию, но почему бы
        // не использовать готовые функции?
        const vector<string> first_names_history = FindFirstNamesHistroy(year);
        const vector<string> last_names_history = FindLastNamesHistory(year);

        // подготовим данные для функции BuildFullName: возьмём последние имя и
        // фамилию или оставим их пустыми, если они неизвестны
        string first_name;
        string last_name;

        if (!first_names_history.empty()) {
            first_name = first_names_history.back();
        }

        if (!last_names_history.empty()) {
            last_name = last_names_history.back();
        }

        return BuildFullName(first_name, last_name);
    }

    string GetFullNameWithHistory(int year) const {
        // получим полное имя со всей историей
        const string first_name = BuildJoinedName(FindNamesHistory(first_names, year));
        // получим полную фамилию со всей историей
        const string last_name = BuildJoinedName(FindNamesHistory(last_names, year));
        // объединим их с помощью готовой функции
        return BuildFullName(first_name, last_name);
    }
private:
    vector<string> FindFirstNamesHistroy(int year) const {
        return FindNamesHistory(first_names, year);
    }

    vector<string> FindLastNamesHistory(int year) const {
        return FindNamesHistory(last_names, year);
    }

    map<int, string> first_names;
    map<int, string> last_names;
};

int main() {
    Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    return 0;
}
