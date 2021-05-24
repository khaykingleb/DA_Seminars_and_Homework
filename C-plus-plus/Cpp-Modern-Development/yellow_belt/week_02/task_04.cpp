#include <iostream>
#include <map>
#include <ostream>
#include <random>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <typename T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& i : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << i;
    }
    return os << "}";
}

template <typename T>
ostream& operator << (ostream& os, const vector<T>& v) {
    os << "{";
    bool first = true;
    for (const auto& i : v) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << i;
    }
    return os << "}";
}

template <typename Key, typename Value>
ostream& operator << (ostream& os, const map<Key, Value>& m) {
    os << "{";
    bool first = true;
    for (const auto& [key, value] : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << key << ": " << value;
    }
    return os << "}";
}

template <typename T, typename U>
void AssertEqual(const T& t, const U& u, const string& hint) {
    if (t != u) {
        ostringstream oss;
        oss << "Assertion failed: " << t << " != " << u << " hint: " << hint;
        throw runtime_error(oss.str());
    }
}

inline void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <typename TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (runtime_error& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
    }

    // Деконструктор
    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            // Прекращение работы программы
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

void TestDefault() {
    Rational r;
    AssertEqual(r.Numerator(), 0, "Numerator is 0 by default.");
    AssertEqual(r.Denominator(), 1, "Denominator is 1 by default.");
}

void TestSimplificaton() {
    Rational r(3, 10);
    Assert(r.Numerator() == 3 && r.Denominator() == 10, "Rational(3, 10) == 3/10");

    Rational q(8, 12);
    Assert(q.Numerator() == 2 && q.Denominator() == 3, "Rational(8, 12) == 2/3");

    Rational w(-4, 6);
    Assert(w.Numerator() == -2 && w.Denominator() == 3, "Rational(-4, 6) == -2/3");

    Rational z(4, -6);
    Assert(z.Numerator() == -2 && z.Denominator() == 3, "Rational(4, -6) == -2/3");
}

void TestNegativeRational() {
    Rational w(-4, 6);
    Assert(w.Numerator() <= 0 && w.Denominator() > 0, "Numerator of Rational(-4, 6) is negative");

    Rational z(4, -6);
    Assert(z.Numerator() <= 0 && z.Denominator() > 0, "Numerator of Rational(4, -6) is negative");
}

void TestPositiveRational() {
    Rational w(4, 6);
    Assert(w.Numerator() > 0 && w.Denominator() > 0, "Numerator of Rational(4, 6) is positive");

    Rational z(-4, -6);
    Assert(z.Numerator() > 0 && z.Denominator() > 0, "Numerator of Rational(-4, -6) is positive");
}

void TestNumeratorEqualZero() {
    Rational r(0, 15);
    Assert(r.Numerator() == 0 && r.Denominator() == 1, "Rational(0, 15) == 0/1");
}

int main() {
    TestRunner runner;
    runner.RunTest(TestDefault, "TestDefault");
    runner.RunTest(TestSimplificaton, "TestSimplificaton");
    runner.RunTest(TestNegativeRational, "TestNegativeRational");
    runner.RunTest(TestPositiveRational, "TestPositiveRational");
    runner.RunTest(TestNumeratorEqualZero, "TestNumeratorEqualZero");
    return 0;
}
