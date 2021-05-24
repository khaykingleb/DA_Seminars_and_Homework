#include "responses.h"
#include <iostream>

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
