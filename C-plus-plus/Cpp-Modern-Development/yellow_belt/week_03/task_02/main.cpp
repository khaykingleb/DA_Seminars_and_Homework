#include "phone_number.h"
#include <iostream>

using namespace std;

int main() {
    PhoneNumber number = PhoneNumber("+1-2-coursera-cpp");
    cout << number.GetCountryCode() << endl;
    cout << number.GetCityCode() << endl;
    cout << number.GetLocalNumber() << endl;
    cout << number.GetInternationalNumber() << endl;
    return 0;
}
