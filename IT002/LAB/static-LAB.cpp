#include <iostream> 
using namespace std;

class Math {
    public:
        static int abs(int num) {
            return (num > 0) ? num : -num;
        }

        static int add (int a, int b) {
            return a + b;
        }

        static int subtract (int a, int b) {
            return a - b;
        }

        static int min (int a, int b) {
            return (a < b) ? a : b;
        }

        static int max (int a, int b) {
            return (a > b) ? a : b;
        }

        static int pow (int base, int exp) {
            int res = 1;
            while (exp) {
                res *= base;
                exp--;
            }
            return res;
        }
};

int main() {
	cout << Math::abs(-2) << endl;
	cout << Math::add(2, 3) << endl;
	cout << Math::subtract(2, 3) << endl;
	cout << Math::min(2, 3) << endl;
	cout << Math::max(2, 3) << endl;
	cout << Math::pow(2, 3) << endl;
	return 0;
}