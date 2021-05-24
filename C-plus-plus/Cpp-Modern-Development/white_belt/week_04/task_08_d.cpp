#include <iostream>
#include <sstream>
#include <iomanip>
#include <numeric>
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

bool operator==(const Rational& rational_1, const Rational& rational_2) {
    return rational_1.Numerator() == rational_2.Numerator() && rational_1.Denominator() == rational_2.Denominator();
}

Rational operator+(const Rational& rational_1, const Rational& rational_2) {
    long numerator, denominator;
    numerator = rational_1.Numerator() * rational_2.Denominator() + rational_2.Numerator() * rational_1.Denominator();
    denominator = rational_1.Denominator() * rational_2.Denominator();
    return Rational(numerator, denominator);
}

Rational operator-(const Rational& rational_1, const Rational& rational_2) {
    long numerator, denominator;
    numerator = rational_1.Numerator() * rational_2.Denominator() - rational_2.Numerator() * rational_1.Denominator();
    denominator = rational_1.Denominator() * rational_2.Denominator();
    return Rational(numerator, denominator);
}

Rational operator*(const Rational& rational_1, const Rational& rational_2) {
    long numerator, denominator;
    numerator = rational_1.Numerator() * rational_2.Numerator();
    denominator = rational_1.Denominator() * rational_2.Denominator();
    return Rational(numerator, denominator);
}

Rational operator/(const Rational& rational_1, const Rational& rational_2) {
    long numerator, denominator;
    numerator = rational_1.Numerator() * rational_2.Denominator();
    denominator = rational_1.Denominator() * rational_2.Numerator();
    return Rational(numerator, denominator);
}

ostream& operator<<(ostream& stream, const Rational& rational) {
    stream << rational.Numerator() << "/" << rational.Denominator();
    return stream;
}

istream& operator>>(istream& stream, Rational& rational) {
    int numerator, denominator;
    char c;
    stream >> numerator >> c >> denominator;
    if (stream && c == '/') {
        rational = {numerator, denominator};
    }
    return stream;
}

int main() {
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 4;
        }
    }

    cout << "OK" << endl;
    return 0;
}