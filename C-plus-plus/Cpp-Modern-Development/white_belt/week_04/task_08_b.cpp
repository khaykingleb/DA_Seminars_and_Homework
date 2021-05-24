#include <iostream>
#include <numeric>


using namespace std;

class Rational {
public:
    Rational() {
        p = 0;
        q = 1;
    }

    Rational(int numerator, int denominator) {
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

    int Numerator() const {
        return p;
    }

    int Denominator() const {
        return q;
    }

private:
    int p;
    int q;
};

bool operator==(const Rational& rational_1, const Rational& rational_2) {
    return rational_1.Numerator() == rational_2.Numerator() && rational_1.Denominator() == rational_2.Denominator();
}

Rational operator+(const Rational& rational_1, const Rational& rational_2) {
    int numerator, denominator;
    numerator = rational_1.Numerator() * rational_2.Denominator() + rational_2.Numerator() * rational_1.Denominator();
    denominator = rational_1.Denominator() * rational_2.Denominator();
    return Rational(numerator, denominator);
}

Rational operator-(const Rational& rational_1, const Rational& rational_2) {
    int numerator, denominator;
    numerator = rational_1.Numerator() * rational_2.Denominator() - rational_2.Numerator() * rational_1.Denominator();
    denominator = rational_1.Denominator() * rational_2.Denominator();
    return Rational(numerator, denominator);
}

int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}