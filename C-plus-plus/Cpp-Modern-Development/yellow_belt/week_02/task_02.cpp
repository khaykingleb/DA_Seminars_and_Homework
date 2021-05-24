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

int GetDistinctRealRootCount(double a, double b, double c) {
    // ax² + bx + c = 0.
    // Вы можете вставлять сюда различные реализации функции,
    // чтобы проверить, что ваши тесты пропускают корректный код
    // и ловят некорректный
}

void TestRootCount() {
    mt19937 generator;
    uniform_real_distribution<> unif(-10, 10);

    for (auto i = 0; i < 100; ++i) {
        const auto a = unif(generator);
        const auto b = unif(generator);
        const auto c = unif(generator);

        const auto count = GetDistinctRealRootCount(a, b, c);

        Assert(count >= 0 && count <= 2, "Quadratic equation has only 0, 1 or 2 real roots.");
    }
}

void TestOneRoot() {
    mt19937 generator;
    uniform_real_distribution<> unif(-10, 10);

    for (auto i = 0; i < 100; ++i) {
        const auto x_1 = unif(generator);

        const auto b = x_1 + x_1;
        const auto c = x_1 * x_1;

        const auto count = GetDistinctRealRootCount(1, b, c);
        stringstream ss;
        ss << showpos << "x^2" << b << "x" << c << " = 0 has 1 real root.";

        AssertEqual(count, 1, ss.str());
    }
}

void TestNoRoots() {
    AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0, "x^2+1 = 0 has 0 real roots.");
    AssertEqual(GetDistinctRealRootCount(1, 3, 4), 0, "x^2+3x+4 = 0 has 0 real roots.");
    AssertEqual(GetDistinctRealRootCount(1, -2, 10), 0, "x^2-2x+10 = 0 has 0 real roots.");
}

void TestLinearEquation() {
    AssertEqual(GetDistinctRealRootCount(0, 2, 1), 1, "2x+1 = 0 has 1 real root.");
    AssertEqual(GetDistinctRealRootCount(0, -1, 0), 1, "-x = 0 has 1 real root.");
    AssertEqual(GetDistinctRealRootCount(0, 120, -10), 1, "120x - 10 = 0 has 1 real root.");
}

void TestConstant() {
    AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0, "c = 0, where c = 1 has 0 real roots.");
    AssertEqual(GetDistinctRealRootCount(0, 0, -10), 0, "c = 0, where c = -10 has 0 real roots.");
    AssertEqual(GetDistinctRealRootCount(0, 0, 189238910), 0, "c = 0, where c = 189238910 has 0 real roots.");
}

int main() {
    TestRunner runner;
    runner.RunTest(TestRootCount, "TestRootCount");
    runner.RunTest(TestOneRoot, "TestOneRoot");
    runner.RunTest(TestNoRoots, "TestNoRoots");
    runner.RunTest(TestLinearEquation, "TestLinearEquation");
    runner.RunTest(TestConstant, "TestConstant");
    return 0;
}
