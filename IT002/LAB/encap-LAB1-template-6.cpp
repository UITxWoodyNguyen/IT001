#include <iostream>
#include <cmath>
using namespace std;

class Point {
    private:   
        double x;
        double y;

    public:
        Point() {}
        Point(double _x, double _y) {
            this->x = _x;
            this->y = _y;
        }

        void setX(double _x) { this->x = _x; }
        double getX() { return x; }
        void setY(double _y) { this->y = _y; }
        double getY() { return y; }

        void setXY (double _x, double _y) {
            this->x = _x;
            this->y = _y;
        }

        double distance (double _x, double _y) {
            return sqrt( (_x - this->x) * (_x - this->x) + (_y - this->y) * (_y - this->y) );
        }

        double distance (Point another) {
            return sqrt( (another.x - this->x) * (another.x - this->x) + (another.y - this->y) * (another.y - this->y) );
        }
};

int main() {
    Point p1(1.5, 6.7);
	Point p2(2.8, 3.2);
	cout << p1.distance(p2) << endl;
	cout << p1.distance(2.34, 7.8) << endl;
	return 0;
}