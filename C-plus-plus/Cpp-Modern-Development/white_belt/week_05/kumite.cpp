#include <iostream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <exception>

using namespace std;

class Date {
private:
    int Year;
    int Month;
    int Day;

public:
    Date () {
        Year = 0;
        Month = 0;
        Day = 0;
    }

    Date (const string& s) {
            stringstream stream(s);
            int year, month, day;
            char c1, c2;

            stream >> year;
            Year = year;

            stream >> c1;

            stream >> month;
            if (month < 1 || month > 12) {
                throw invalid_argument("Month value is invalid: " + to_string(month));
            } else {
                Month = month;
            }

            stream >> c2;

            stream >> day;
            if (day < 1 || day > 31) {
                throw invalid_argument("Day value is invalid: " + to_string(day));
            } else {
                Day = day;
            }
    }

    int GetYear() const {
        return Year;
    }

    int GetMonth() const {
        return Month;
    }

    int GetDay() const {
        return Day;
    }
};

bool operator < (const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() < rhs.GetYear()) {
        return true;
    } else if (lhs.GetYear() == rhs.GetYear()) {

        if (lhs.GetMonth() < rhs.GetMonth()) {
            return true;
        } else if (lhs.GetMonth() ==rhs.GetMonth()) {

            return lhs.GetDay() < rhs.GetDay();

        } else {
            return false;
        }

    } else {
        return false;
    }
};

class Database {
private:
    map<Date, set<string>> database;
public:
    void AddEvent(const Date& date, const string& event) {
        database[date].insert(event);
    }

    bool DeleteEvent(const Date& date, const string& event) {
        if (database.count(date) == 1) {
            if (database[date].count(event) == 1) {
                database[date].erase(event);
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    int DeleteDate(const Date& date) {
        if (database.count(date) == 1) {
            int cnt = database[date].size();
            database.erase(date);
            return cnt;
        } else {
            return 0;
        }
    }

    void Find(const Date& date)  {
        for (const auto& item : database[date]) {
            cout << item << endl;
        }
    }

    void Print() const {
        for (const auto& item : database) {
            for (const string& element : item.second) {
                cout << setw(4) << setfill('0') << item.first.GetYear() << '-'
                     << setw(2) << setfill('0') << item.first.GetMonth() << '-'
                     << setw(2) << setfill('0') << item.first.GetDay();
                cout << " " << element << endl;
            }
        }
    }

};


void EnsureOperationCode(const string& s) {
    if (s != "Add" && s != "Del" && s != "Find" && s != "Print" && s != "") {
        throw invalid_argument("Unknown command: " + s);
    }
}

void EnsureDateFormat(const string& s) {
    // Полезно прочитать:
    // https://www.coursera.org/learn/c-plus-plus-white/programming/sO7Vq/final-naia-zadacha-kursa/discussions/threads/YcjMtxphEemQSw4P4a3-4A

    stringstream stream(s);
    int year, month, day;
    char c1, c2;

    if (!(stream >> year >> c1 >> month >> c2 >> day && stream.eof() && c1 == '-' & c2 == '-')) {
        throw invalid_argument("Wrong date format: " + s);
    }
}

int main() {
    Database database;

    string line;
    while (getline(cin, line)) {
        stringstream stream(line);

        try {
            string operation_code;
            stream >> operation_code;

            EnsureOperationCode(operation_code);

            string date_str;
            Date date;

            if (stream.good()) {
                stream >> date_str;

                EnsureDateFormat(date_str);
                date = {date_str};
            }

            string event;
            if (stream.good()) {
                stream >> event;
            }

            if (operation_code == "Add") {
                database.AddEvent(date, event);

            } else if (operation_code == "Del") {

                if (event.empty()) {

                    int n = database.DeleteDate(date);
                    cout << "Deleted " << n << " events" << endl;

                } else {

                    if (database.DeleteEvent(date, event)) {
                        cout << "Deleted successfully" << endl;
                    } else {
                        cout << "Event not found" << endl;
                    }

                }

            } else if (operation_code == "Find") {
                database.Find(date);

            } else if (operation_code == "Print") {
                database.Print();
            }
        } catch (exception &e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}

