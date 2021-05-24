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
