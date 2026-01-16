#include <bits/stdc++.h>
using namespace std;

bool is_prime (int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    int limit = sqrt(n);
    int i = 3;
    do {
        if (n % i == 0) return false;
        i += 2;
    } while (i + 2 <= limit);
    return true;
}

int count_prime (int a[], int n) {
    int count = 0;
    for(int i = 0; i < n; i++)
        if (is_prime(a[i])) count++;
    return count;
}

int main () {
    // demo test
    int num = 5;
    int a[6] = {5,7,9,11,13};
    int n = 6;

    cout << is_prime(num) << endl;
    cout << count_prime(a,n) << endl;
}
