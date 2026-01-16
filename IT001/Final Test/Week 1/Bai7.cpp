#include <bits/stdc++.h>
using namespace std;

int getMax (int a[], int n) {
    if (n == 1) return a[0];
    return max(getMax(a, n-1), a[n-1]);
}

int getSum (int a[], int n) {
    if (n == 1) return a[0];
    return getSum(a, n-1) + a[n-1];
}

int main () {
    int a[] = {2,3,4,5};
    int n = 4;
    cout << getMax(a,n) << ' ' << getSum(a,n) << endl;
}
