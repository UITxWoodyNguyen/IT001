#include <iostream>
#include <math.h>
using namespace std;

class ArrayCalculator {
    public:
        template <typename T>
        static T minOfArray(T* a, int size) {
            T min = a[0];
            for(int i = 1; i < size; i++) min = (a[i] < min) ? a[i] : min;
            return min;
        }

        template <typename T>
        static T maxOfArray(T* a, int size) {
            T max = a[0];
            for(int i = 1; i < size; i++) max = (a[i] > max) ? a[i] : max;
            return max;
        }
};

int main() {
	int arr1[] = { 3, 4, 2 };
	double arr2[] = { 1.3, 4.2, 6.7 };

	cout << ArrayCalculator::minOfArray(arr1, sizeof(arr1) / sizeof(int)) << endl;
	cout << ArrayCalculator::minOfArray(arr2, sizeof(arr2) / sizeof(double)) << endl;
	cout << ArrayCalculator::maxOfArray(arr1, sizeof(arr1) / sizeof(int)) << endl;
	cout << ArrayCalculator::maxOfArray(arr2, sizeof(arr2) / sizeof(double)) << endl;
	return 0;
}