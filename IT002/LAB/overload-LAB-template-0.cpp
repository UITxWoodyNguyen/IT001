#include <iostream>
using namespace std;

class ArrayCalculator {
    public:
        static int sumOfArray (int* a, int size) {
            int sum = 0;
            for(int i = 0; i < size; i++) sum += a[i];
            return sum;
        }

        static double sumOfArray (double* a, int size) {
            double sum = 0.0;
            for(int i = 0; i < size; i++) sum += a[i];
            return sum;
        }
};

int main() {
	int arr1[] = { 3, 4, 2 };
	double arr2[] = { 1.3, 4.2, 6.7 };
	cout << ArrayCalculator::sumOfArray(arr1, sizeof(arr1) / sizeof(int)) << endl;
	cout << ArrayCalculator::sumOfArray(arr2, sizeof(arr2) / sizeof(double)) << endl;
	return 0;
}