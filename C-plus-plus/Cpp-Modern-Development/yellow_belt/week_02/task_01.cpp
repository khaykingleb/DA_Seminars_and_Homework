// Декомпозиция task_09, week_02 белого пояса

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
#include <string>
#include <map>
#include <vector>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string operation_code;
    is >> operation_code;

    if (operation_code == "NEW_BUS") {
        q.type = QueryType::NewBus;

        is >> q.bus;

        int stop_count;
        is >> stop_count;

        q.stops.resize(stop_count);

        for (string& stop : q.stops) {
            is >> stop;
        }

    } else if (operation_code == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;

    } else if (operation_code == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;

    } else {
        q.type = QueryType::AllBuses;

    }

    return is;
}

struct BusesForStopResponse {
    string stop;
    vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.stop.empty()) {
        os << "No stop";
    } else {
        for (const string& bus : r.buses) {
            os << bus << " ";
        }
    }
    return os;
}

struct StopsForBusResponse {
    string bus;
    vector<string> stops;
    map<string, vector<string>> stops_to_buses_;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.bus.empty()) {
        os << "No bus";
    } else {
        int cnt = r.stops.size();
        for (const string& stop : r.stops) {
            os << "Stop " << stop << ": ";
            if (r.stops_to_buses_.at(stop).size() == 1) {
                os << "no interchange";
            } else {
                for (const string& other_bus : r.stops_to_buses_.at(stop)) {
                    if (r.bus != other_bus) {
                        os << other_bus << " ";
                    }
                }
            }
            --cnt;
            if (cnt != 0) {
                cout << endl;
            }
        }
    }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> buses_to_stops_;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.buses_to_stops_.empty()) {
        os << "No buses";

    } else {
        int cnt = r.buses_to_stops_.size();
        for (const auto& [bus, stops] : r.buses_to_stops_) {
            os << "Bus " << bus << ": ";
            for (const string& stop : stops) {
                os << stop << " ";
            }
            --cnt;
            if (cnt != 0) {
                cout << endl;
            }
        }

    }
    return os;
}

class BusManager {
private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;

public:
    void AddBus(const string& bus, const vector<string>& stops) {
        for (const string& stop : stops) {
            buses_to_stops[bus].push_back(stop);
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        BusesForStopResponse response;

        if (stops_to_buses.count(stop) == 0) {
            return response;
        } else {
            response.stop = stop;
            for (const string& bus : stops_to_buses.at(stop)) {
                response.buses.push_back(bus);
            }
            return response;
        }
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        StopsForBusResponse response;
        if (buses_to_stops.count(bus) == 0) {
            return response;
        } else {
            response.bus = bus;
            for (const string& stop : buses_to_stops.at(bus)) {
                response.stops.push_back(stop);
            }
            response.stops_to_buses_ = stops_to_buses;
            return response;
        }
    }

    AllBusesResponse GetAllBuses() const {
        AllBusesResponse response;
        if (buses_to_stops.empty()) {
            return response;
        } else {
            response.buses_to_stops_ = buses_to_stops;
            return response;
            }
        }
};

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }
    return 0;
}
