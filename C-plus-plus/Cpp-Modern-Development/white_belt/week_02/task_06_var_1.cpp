#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
У каждого из нас есть повторяющиеся ежемесячные дела, каждое из которых нужно выполнять в конкретный день каждого месяца:
оплата счетов за электричество, абонентская плата за связь и пр. Вам нужно реализовать работу со списком таких дел
на месяц, а именно, реализовать набор следующих операций:

ADD i s
Назначить дело с названием s на день i текущего месяца.

DUMP i
Вывести все дела, запланированные на день i текущего месяца.

NEXT
Перейти к списку дел на новый месяц. При выполнении данной команды вместо текущего (старого) списка дел на текущий месяц
создаётся и становится активным (новый) список дел на следующий месяц: все дела со старого списка дел копируются в новый
список. После выполнения данной команды новый список дел и следующий месяц становятся текущими, а работа со старым
списком дел прекращается. При переходе к новому месяцу необходимо обратить внимание на разное количество дней в месяцах:
• если следующий месяц имеет больше дней, чем текущий, «дополнительные» дни необходимо оставить пустыми (не содержащими дел);
• если следующий месяц имеет меньше дней, чем текущий, дела со всех «лишних» дней необходимо переместить на последний 
  день следующего месяца.
*/

int main() {
    int q;
    cin >> q;

    vector<int> days_in_month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int cur_month = 0;

    vector<vector<string>> v;
    v.resize(days_in_month[0]);

    vector<vector<string>> result;

    for (int i = 0; i < q; ++i) {
        string operation;
        cin >> operation;

        if (operation == "NEXT") {
            ++cur_month;
            cur_month %= 12;

            if (days_in_month[cur_month] < days_in_month[cur_month - 1]) {
                vector<string> last_todo;

                for (int j = days_in_month[cur_month]; j < days_in_month[cur_month - 1]; ++j){
                    last_todo.insert(end(last_todo), begin(v[j]), end(v[j]));
                }

                v.resize(days_in_month[cur_month]);
                v[v.size()-1].insert(end(v[v.size()-1]), begin(last_todo), end(last_todo));

                last_todo.clear();

            } else {
                v.resize(days_in_month[cur_month]);
            }

        } else {
            if (operation == "ADD") {
                int day;
                string command;

                cin >> day >> command;

                v[day - 1].push_back(command);

            } else { // operation == "DUMP"
                int day;
                cin >> day;

                vector<string> cur_result;
                cur_result.push_back(to_string(v[day - 1].size()));

                if (!v[day - 1].empty()) {
                    for (const auto& activity : v[day - 1]) {
                        cur_result.push_back(activity);
                    }
                }

                result.push_back(cur_result);
            }
        }
    }

    for (auto & i : result) {
        for (const auto & j : i) {
            cout << j << " ";
        }
        cout << endl;
    }

    return 0;

}
