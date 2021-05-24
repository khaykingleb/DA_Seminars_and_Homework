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
            throw invalid_argument("Denominator should not be zero.");
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
        throw domain_error("Denominator should not be zero.");
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

int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}