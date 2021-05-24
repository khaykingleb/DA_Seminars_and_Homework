#include <iostream>
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

int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}