#include <iostream>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <map>
#include <set>
#include <vector>
using namespace std;

class Rational {
public:
    Rational() {
        p = 0;
        q = 1;
    }

    Rational(long numerator, long denominator) {
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
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}