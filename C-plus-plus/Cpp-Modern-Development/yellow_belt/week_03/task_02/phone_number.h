#pragma once

#include <string>

using namespace std;

class PhoneNumber {
public:
    explicit PhoneNumber(const string &international_number);

    string GetCountryCode() const;
    string GetCityCode() const;
    string GetLocalNumber() const;
    string GetInternationalNumber() const;

private:
    string country_code_;
    string city_code_;
    string local_number_;
};
