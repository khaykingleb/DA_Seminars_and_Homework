#include "query.h"
#include <iostream>

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
