#include <iostream>
#include <vector>
#include <string>
using namespace std;


int Factorial(int x) {
    if (x <= 1) {
        return 1;
    } else {
        return x * Factorial(x - 1);
    }
}

int main() {
    int number;
    cin >> number;
    cout << Factorial(number);
    return 0;
}
