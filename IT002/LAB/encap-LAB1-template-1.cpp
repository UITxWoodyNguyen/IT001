/*
    Template Here:
    #include<iostream>
    #include "Rectangle.cpp"

    using namespace std;

    int main() {
        Rectangle r(4, 5);
        cout << "Area: " << r.getArea() << endl;
        cout << "Perimeter: " << r.getPerimeter() << endl;
        r.setLength(2);
        r.setWidth(3);
        cout << "Area: " << r.getArea() << endl;
        cout << "Perimeter: " << r.getPerimeter() << endl;
        return 0;
    }

    Go gor Rectangle.cpp
*/

#include <iostream>
using namespace std;

class Rectangle {
    private:
        double length;
        double width;

    public:
        Rectangle() {}
        Rectangle (double _length, double _width) {
            this->length = _length;
            this->width = _width;
        }

        void setLength(double _length) {
            this->length = _length;
        }

        double getLength() {
            return length;
        }

        void setWidth(double _width) {
            this->width = _width;
        }

        double getWidth() {
            return width;
        }

        double getArea() {
            return length * width;
        }

        double getPerimeter() {
            return 2 * (length + width);
        }
};

int main () {
    Rectangle r(4, 5);
    cout << "Area: " << r.getArea() << endl;
    cout << "Perimeter: " << r.getPerimeter() << endl;
    r.setLength(2);
    r.setWidth(3);
    cout << "Area: " << r.getArea() << endl;
    cout << "Perimeter: " << r.getPerimeter() << endl;
    return 0;
}