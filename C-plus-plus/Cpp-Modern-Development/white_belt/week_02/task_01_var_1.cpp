#include <iostream>
#include <vector>
#include <string>
using namespace std;


int Factorial(int x) {
    int prod = 1;
    for (int i = 1; i <= x; ++i){
        prod *= i;
    }
    return prod;
}

int main() {
    int number;
    cin >> number;
    cout << Factorial(number);
    return 0;
}
