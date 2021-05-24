#include "phone_number.h"
#include <sstream>

using namespace std;

PhoneNumber::PhoneNumber(const string& international_number) {
    stringstream stream(international_number);
    char c1, c2, c3;
    int country_code, city_code;
    string local_number;

    if ((stream >> c1 >> country_code
                      >> c2 >> city_code
                      >> c3 >> local_number)
        && c1 == '+' && c2 == '-' && c3 == '-') {
        country_code_ = to_string(country_code);
        city_code_ = to_string(city_code);
        local_number_ = local_number;
    } else {
        throw invalid_argument("Wrong number format");
    }
}

/* Different execution
PhoneNumber::PhoneNumber(const string& international_number) {
  istringstream is(international_number);

  char sign = is.get();
  getline(is, country_code_, '-');
  getline(is, city_code_, '-');
  getline(is, local_number_);

  if (sign != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty()) {
    throw invalid_argument("Phone number must begin with '+' symbol and contain 3 parts separated by '-' symbol: " + international_number);
  }
}
*/

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    stringstream ss;
    ss << '+' << country_code_
       << '-' << city_code_
       << '-' << local_number_;
    return ss.str();
}
