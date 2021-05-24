#include "bus_manager.h"

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    for (const string& stop : stops) {
        buses_to_stops[bus].push_back(stop);
        stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
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

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
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

AllBusesResponse BusManager::GetAllBuses() const {
    AllBusesResponse response;
    if (buses_to_stops.empty()) {
        return response;
    } else {
        response.buses_to_stops_ = buses_to_stops;
        return response;
    }
}
