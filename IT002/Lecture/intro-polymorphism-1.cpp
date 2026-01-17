#include <iostream>
using namespace std;

class Calc {
    public:
        int add (int a, int b) {
            return a + b;
        }

        int add (int a, int b, int c) {
            return a + b + c;
        }

        double add (double a, double b) {
            return a + b;
        }
};

int main () {
    Calc calculator;

    cout << calculator.add(2, 5) << endl; // sum of 2 integers
    cout << calculator.add(2, 3, 4) << endl; // sum of 3 integers
    cout << calculator.add(1.2, 3.4) << endl; // sum of 2 doubles

    return 0;
}