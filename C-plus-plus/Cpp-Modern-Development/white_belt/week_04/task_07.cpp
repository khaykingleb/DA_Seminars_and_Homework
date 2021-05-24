/*
  Определите структуру «Студент» со следующими полями: имя, фамилия, день, месяц и год рождения. Создайте вектор из таких
  структур, заполните его из входных данных и затем по запросам выведите нужные поля.

  # Формат ввода
  Первая строка содержит одно целое число N от 0 до 10000 — число студентов.
  Далее идут N строк, каждая из которых содержит две строки длиной от 1 до 15 символов — имя и фамилию очередного
  студента, и три целых числа от 0 до 1000000000 — день, месяц и год рождения.
  Следующая строка содержит одно целое число M от 0 до 10000 — число запросов.
  Следующие M строк содержат строку длиной от 1 до 15 символов — запрос, и целое число от 0 до 1000000000 — номер
  студента (нумерация начинается с 1).

  # Формат вывода
  Для запроса вида name K, где K от 1 до N, выведите через пробел имя и фамилию K-го студента.
  Для запроса вида date K, где K от 1 до N, выведите через точку день, месяц и год рождения K-го студента.
  Для остальных запросов выведите bad request.
 */

#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct Student {
    string first_name;
    string last_name;

    int day;
    int month;
    int year;
};

int main() {
    int n;
    cin >> n;

    string first_name, last_name;
    int day, month, year;
    vector<Student> students;

    for (size_t i = 0; i < n; ++i) {
        cin >> first_name >> last_name >> day >> month >> year;

        students.push_back(Student{first_name,
                                   last_name,
                                   day,
                                   month,
                                   year});
    }

    int m;
    cin >> m;

    string query;
    int student_number;

    for (int i = 0; i < m; ++i) {
        cin >> query >> student_number;
        --student_number;

        if (query == "name" && student_number >= 0 && student_number < n) {
            cout << students[student_number].first_name << " "
                 << students[student_number].last_name << endl;
        } else if (query == "date" && student_number >= 0 && student_number < n) {
            cout << students[student_number].day << "."
                 << students[student_number].month << "."
                 << students[student_number].year << endl;
        } else {
            cout << "bad request" << endl;
        }
    }

    return 0;
}