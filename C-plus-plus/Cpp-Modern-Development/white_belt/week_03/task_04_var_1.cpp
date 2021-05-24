/*
 Реализуйте класс для человека, поддерживающий историю изменений человеком своих фамилии и имени.
 
 Считайте, что в каждый год может произойти не более одного изменения фамилии и не более одного изменения имени. При этом с течением времени могут 
 открываться всё новые факты из прошлого человека, поэтому года́ в последовательных вызовах методов ChangeLastName и ChangeFirstName не обязаны возрастать.

 Гарантируется, что все имена и фамилии непусты.

 Строка, возвращаемая методом GetFullName, должна содержать разделённые одним пробелом имя и фамилию человека по состоянию на конец данного года.
 • Если к данному году не случилось ни одного изменения фамилии и имени, верните строку "Incognito".
 • Если к данному году случилось изменение фамилии, но не было ни одного изменения имени, верните "last_name with unknown first name".
 • Если к данному году случилось изменение имени, но не было ни одного изменения фамилии, верните "first_name with unknown last name".
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        UpdateFirstName(year, first_name);
    }

    void ChangeLastName(int year, const string& last_name) {
        UpdateLastName(year, last_name);
    }

    string GetFullName(int year) {
        int year_1 = 0;
        int year_2 = 0;

        for (const auto& i : first_names) {
             if (i.first <= year) {
                 year_1 = i.first;
             } else {
                 break;
             }
        }

        for (const auto& i : last_names) {
            if (i.first <= year) {
                year_2 = i.first;
            } else {
                break;
            }
        }

        if (year_1 == 0 && year_2 == 0) {
            return "Incognito";
        } else if (year_1 == 0 || year_2 == 0) {
            if (year_1 == 0) {
                return  last_names[year_2] + " with unknown first name";
            } else {
                return first_names[year_1] + " with unknown last name";
            }
        } else {
            return first_names[year_1] + " " + last_names[year_2];
        }


    }

private:
    void UpdateFirstName(int year, const string& first_name) {
        first_names[year] = first_name;
    }

    void UpdateLastName(int year, const string& last_name) {
        last_names[year] = last_name;
    }

    map<int, string> first_names;
    map<int, string> last_names;
};

int main() {
    Person person;

    person.ChangeLastName(1968, "1968_2nd");
    person.ChangeLastName(1967, "1967_2nd");
    person.ChangeLastName(1965, "1965_2nd");
    person.ChangeLastName(1966, "1966_2nd");

    for (int year : {1900, 1920, 1950, 1965, 1966, 1967, 1968}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1920, "1920_1st");
    person.ChangeFirstName(1900, "1900_1st");
    person.ChangeFirstName(1965, "1965_1st");
    person.ChangeFirstName(1950, "1950_1st");

    for (int year : {1900, 1920, 1950, 1965, 1966, 1967, 1968}) {
        cout << person.GetFullName(year) << endl;
    }

    return 0;
}
