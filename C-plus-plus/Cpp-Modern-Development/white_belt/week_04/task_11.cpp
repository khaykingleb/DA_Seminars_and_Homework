#include <iostream>
#include <sstream>
#include <numeric>
#include <map>
#include <set>
#include <exception>
#include <vector>
using namespace std;

class Rational {
public:
    Rational() {
        p = 0;
        q = 1;
    }

    Rational(long numerator, long denominator) {
        if (denominator == 0) {
            throw invalid_argument("Invalid argument");
        }

        if (numerator == 0) {
            p = 0;
            q = 1;
        } else {
            if (numerator * denominator < 0) {
                if (numerator < 0) {
                    p = numerator / gcd(abs(numerator), abs(denominator));
                    q = denominator / gcd(abs(numerator), abs(denominator));
                } else { // numerator >= 0
                    p = - numerator / gcd(abs(numerator), abs(denominator));
                    q = - denominator / gcd(abs(numerator), abs(denominator));
                }
            } else { // numerator * denominator >= 0
                if (numerator < 0 && denominator < 0) {
                    p = - numerator / gcd(abs(numerator), abs(denominator));
                    q = - denominator / gcd(abs(numerator), abs(denominator));
                } else {
                    p = numerator / gcd(numerator, denominator);
                    q = denominator / gcd(numerator, denominator);
                }
            }
        }
    }

    long Numerator() const {
        return p;
    }

    long Denominator() const {
        return q;
    }

private:
    long p;
    long q;
};

bool operator == (const Rational& rational_1, const Rational& rational_2) {
    return rational_1.Numerator() == rational_2.Numerator() && rational_1.Denominator() == rational_2.Denominator();
}

Rational operator + (const Rational& rational_1, const Rational& rational_2) {
    long numerator, denominator;
    numerator = rational_1.Numerator() * rational_2.Denominator() + rational_2.Numerator() * rational_1.Denominator();
    denominator = rational_1.Denominator() * rational_2.Denominator();
    return Rational(numerator, denominator);
}

Rational operator - (const Rational& rational_1, const Rational& rational_2) {
    long numerator, denominator;
    numerator = rational_1.Numerator() * rational_2.Denominator() - rational_2.Numerator() * rational_1.Denominator();
    denominator = rational_1.Denominator() * rational_2.Denominator();
    return Rational(numerator, denominator);
}

Rational operator * (const Rational& rational_1, const Rational& rational_2) {
    long numerator, denominator;
    numerator = rational_1.Numerator() * rational_2.Numerator();
    denominator = rational_1.Denominator() * rational_2.Denominator();
    return Rational(numerator, denominator);
}

Rational operator / (const Rational& rational_1, const Rational& rational_2) {
    long numerator, denominator;
    numerator = rational_1.Numerator() * rational_2.Denominator();
    denominator = rational_1.Denominator() * rational_2.Numerator();

    if (denominator == 0) {
        throw domain_error("Division by zero");
    }

    return Rational(numerator, denominator);
}

ostream& operator << (ostream& stream, const Rational& rational) {
    stream << rational.Numerator() << "/" << rational.Denominator();
    return stream;
}

istream& operator >> (istream& stream, Rational& rational) {
    int numerator, denominator;
    char c;
    stream >> numerator >> c >> denominator;
    if (stream && c == '/') {
        rational = {numerator, denominator};
    }
    return stream;
}

bool operator < (const Rational& rational_1, const Rational& rational_2) {
    return (rational_1.Numerator() * rational_2.Denominator() < rational_2.Numerator() * rational_1.Denominator());
}

Rational ParseOperation(const string& s) {
    stringstream stream(s);
    string code_operation;
    Rational rational_1, rational_2;

    int numerator_1, denominator_1;
    char c_1;
    stream >> numerator_1 >> c_1 >> denominator_1;
    if (stream && c_1 == '/') {
        rational_1 = {numerator_1, denominator_1};
    }

    stream >> code_operation;

    int numerator_2, denominator_2;
    char c_2;
    stream >> numerator_2 >> c_2 >> denominator_2;
    if (stream && c_2 == '/') {
        rational_2 = {numerator_2, denominator_2};
    }

    if (code_operation == "+") {
        return rational_1 + rational_2;
    } else if (code_operation == "-") {
        return rational_1 - rational_2;
    } else if (code_operation == "*") {
        return rational_1 * rational_2;
    } else {
        return rational_1 / rational_2;
    }
}

int main() {
    string response;
    // response will contain the contents of the entire line.
    getline(cin, response);

    try {
       Rational answer = ParseOperation(response);
       cout << answer;
    } catch (exception& e) {
        cout << e.what();
    }


    return 0;
}