/*
    Template here:
        #include <iostream>
        #include "Circle.cpp"

        using namespace std;

        int main() {
            Circle c(7);
            cout << c.getArea() << endl;
            cout << c.getCircumference() << endl;
            return 0;
        }

    Go for Circle.cpp
*/

#include <iostream>
using namespace std;

const double PI = 3.14;

class Circle {
    private: 
        double radius;

    public:
        Circle (double _radius) {
            this->radius = _radius;
        }

        double getArea() {
            return PI * radius * radius;
        }

        double getCircumference() {
            return 2 * PI * radius;
        }
};