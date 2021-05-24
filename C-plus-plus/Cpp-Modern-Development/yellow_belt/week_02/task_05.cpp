#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <set>
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

template <typename Key, typename Value>
ostream& operator << (ostream& os, const pair<Key, Value>& p) {
  os << "{" << p.first << ": " << p.second;
  return os << "}";
}

template <typename T, typename U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
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
      } catch (exception& e) {
        ++fail_count;
        cerr << test_name << " fail: " << e.what() << endl;
      } catch (...) {
        ++fail_count;
        cerr << "Unknown exception caught" << endl;
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

void TestOddLengthStringTrue1() {
    AssertEqual(IsPalindrom("madam"), true);
}

void TestOddLengthStringTrue2() {
    AssertEqual(IsPalindrom("level"), true);
}

void TestOddLengthStringTrue3() {
    AssertEqual(IsPalindrom("wasitacaroracatisaw"), true);
}

void TestOddLengthStringFalse1() {
    AssertEqual(IsPalindrom("gentleman"), false);
}
// 11
void TestOddLengthStringFalse2() {
    AssertEqual(IsPalindrom("abcca"), false);
}
// 12
void TestOddLengthStringFalse3() {
    AssertEqual(IsPalindrom("abcbc"), false);
}

void TestEvenLengthStringTrue() {
    AssertEqual(IsPalindrom("abba"), true);
}
// 4
void TestEvenLengthStringFalse() {
    AssertEqual(IsPalindrom("ab"), false);
}

void TestLongString1() {
    AssertEqual(IsPalindrom("abcdefghijklmnopqrstuvwxyzzyxwvutsrqponmlkjihgfedcba"), true);
}

void TestLongString2() {
    AssertEqual(IsPalindrom("abcdefghijklnopqrstuvwxyzzyxwvutsrqponmlkjihgfedcba"), false);
}

void TestUpperCase() {
    AssertEqual(IsPalindrom("aA"), false);
}

void TestPassFirstSymbol() {
    AssertEqual(IsPalindrom("asitacaroracatisaw"), false);
}

void TestPassLastSymbol() {
    AssertEqual(IsPalindrom("wasitacaroracatisa"), false);
}

void TestPassTwoFirstSymbol() {
    AssertEqual(IsPalindrom("sitacaroracatisaw"), false);
}

void TestPassTwoLastSymbol() {
    AssertEqual(IsPalindrom("wasitacaroracatis"), false);
}

void TestEmptyString() {
    AssertEqual(IsPalindrom(""), true);
}
// 2
void TestOneSymbolString() {
    AssertEqual(IsPalindrom("a"), true);
}

void TestSpaceSymbols() {
    AssertEqual(IsPalindrom("kay ak"), false);
}

void TestTabSymbols() {
    AssertEqual(IsPalindrom("kay\tak"), false);
}

void TestIndent() {
    AssertEqual(IsPalindrom(" kayak"), false);
}

void TestWhitespaceSymbols() {
    AssertEqual(IsPalindrom("\t\n  \n\t"), true);
}

int main() {
    TestRunner runner;
    // добавьте сюда свои тесты
    runner.RunTest(TestOddLengthStringTrue1, "TestOddLengthStringTrue1");
    runner.RunTest(TestOddLengthStringTrue2, "TestOddLengthStringTrue2");
    runner.RunTest(TestOddLengthStringTrue3, "TestOddLengthStringTrue3");
    runner.RunTest(TestOddLengthStringFalse1, "TestOddLengthStringFalse1");
    runner.RunTest(TestOddLengthStringFalse2, "TestOddLengthStringFalse2");
    runner.RunTest(TestOddLengthStringFalse3, "TestOddLengthStringFalse3");
    runner.RunTest(TestEvenLengthStringTrue, "TestEvenLengthStringTrue");
    runner.RunTest(TestEvenLengthStringFalse, "TestEvenLengthStringFalse");
    runner.RunTest(TestLongString1, "TestLongString1");
    runner.RunTest(TestLongString2, "TestLongString2");
    runner.RunTest(TestUpperCase, "TestUpperCase");
    runner.RunTest(TestPassFirstSymbol, "TestPassFirstSymbol");
    runner.RunTest(TestPassLastSymbol, "TestPassLastSymbol");
    runner.RunTest(TestPassTwoFirstSymbol, "TestPassTwoFirstSymbol");
    runner.RunTest(TestPassTwoLastSymbol, "TestPassTwoLastSymbol");
    runner.RunTest(TestEmptyString, "TestEmptyString");
    runner.RunTest(TestOneSymbolString, "TestOneSymbolString");
    runner.RunTest(TestSpaceSymbols, "TestSpaceSymbols");
    runner.RunTest(TestTabSymbols, "TestTabSymbols");
    runner.RunTest(TestIndent, "TestIndent");
    runner.RunTest(TestWhitespaceSymbols, "TestWhitespaceSymbols");
    return 0;
}
