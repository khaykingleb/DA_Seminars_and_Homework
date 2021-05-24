/*
Реализуйте систему хранения автобусных маршрутов. Вам нужно обрабатывать следующие запросы:
• NEW_BUS bus stop_count stop1 stop2 ... — добавить маршрут автобуса с названием bus и stop_count остановками с
  названиями stop1, stop2, ...
• BUSES_FOR_STOP stop — вывести названия всех маршрутов автобуса, проходящих через остановку stop.
• STOPS_FOR_BUS bus — вывести названия всех остановок маршрута bus со списком автобусов, на которые можно пересесть на
  каждой из остановок.
•ALL_BUSES — вывести список всех маршрутов с остановками.

# Формат ввода
В первой строке ввода содержится количество запросов Q, затем в Q строках следуют описания запросов.
Гарантируется, что все названия маршрутов и остановок состоят лишь из латинских букв, цифр и знаков подчёркивания.
Для каждого запроса NEW_BUS bus stop_count stop1stop2 ... гарантируется, что маршрут bus отсутствует, количество
остановок больше 0, а после числа stop_count следует именно такое количество названий остановок, причём все названия в
каждом списке различны.

# Формат вывода
Для каждого запроса, кроме NEW_BUS, выведите соответствующий ответ на него:
• На запрос BUSES_FOR_STOP stop выведите через пробел список автобусов, проезжающих через эту остановку, в том порядке,
  в котором они создавались командами NEW_BUS. Если остановка stop не существует, выведите No stop.
• На запрос STOPS_FOR_BUS bus выведите описания остановок маршрута bus в отдельных строках в том порядке, в котором они
  были заданы в соответствующей команде NEW_BUS. Описание каждой остановки stop должно иметь вид Stop stop: bus1bus2 ...,
  где bus1bus2 ... — список автобусов, проезжающих через остановку stop, в порядке, в котором они создавались командами
  NEW_BUS, за исключением исходного маршрута bus. Если через остановку stop не проезжает ни один автобус, кроме bus,
  вместо списка автобусов для неё выведите no interchange. Если маршрут bus не существует, выведите No bus.
• На запрос ALL_BUSES выведите описания всех автобусов в алфавитном порядке. Описание каждого маршрута bus должно иметь
  вид Bus bus: stop1stop2 ..., где stop1stop2 ... — список остановок автобуса bus в порядке, в котором они были заданы в
  соответствующей команде NEW_BUS. Если автобусы отсутствуют, выведите No buses.
 */

#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

int main() {
    int q;
    cin >> q;

    map<string, vector<string>> buses_to_routes;
    map<string, vector<string>> stops_to_buses;

    for (int i = 0; i < q; ++i) {
        string operation_code;
        cin >> operation_code;

        if (operation_code == "NEW_BUS") {

            string bus;
            int stop_count;
            cin >> bus >> stop_count;

            for (int j = 0; j < stop_count; ++j) {
                string stop;
                cin >> stop;
                buses_to_routes[bus].push_back(stop);
                stops_to_buses[stop].push_back(bus);
            }

        } else if (operation_code == "BUSES_FOR_STOP") {

            string stop;
            cin >> stop;

            if (stops_to_buses.count(stop) == 0) {
                cout << "No stop" << endl;
            } else {
                for (const auto&  bus : stops_to_buses[stop]) {
                    cout << bus << " ";
                }
                cout << endl;
            }

        } else if (operation_code == "STOPS_FOR_BUS") {

            string bus;
            cin >> bus;

            if (buses_to_routes.count(bus) == 0){

                cout << "No bus" << endl;

            } else {

                for (const auto &stop : buses_to_routes[bus]) {
                    cout << "Stop " << stop << ": ";

                    if (stops_to_buses[stop].size() == 1) {
                        cout << "no interchange" << endl;
                    } else {
                        for (const auto &bus_ : stops_to_buses[stop]) {
                            if (bus_ == bus){
                                continue;
                            } else {
                                cout << bus_ << " ";
                            }
                        }
                        cout << endl;
                    }
                }

            }

        } else if (operation_code == "ALL_BUSES") {

            if (buses_to_routes.empty()) {

                cout << "No buses" << endl;

            } else {

                for (const auto& item : buses_to_routes){
                    cout << "Bus " << item.first << ": ";

                    for (const auto& stop : buses_to_routes[item.first]) {
                        cout << stop << " ";
                    }

                    cout << endl;
                }

            }

        }

    }

    return 0;
}
