#include <bits/stdc++.h>
using namespace std;

#define JUDGE(name) if (fopen(name".inp", "r")) { freopen(name".inp","r",stdin); freopen(name".out","w",stdout); }
const int MAXN = 1e5+5;
int a[MAXN];

long long getEvenSum (const int a[], int n) { // n = sizeof(a)
    long long sum = 0;
    for(int i=1; i<=n; i++) {
        if (a[i] < 0) continue;
        sum += (a[i] & 1 ? 0 : a[i]);
    }
    return sum;
}

void printArray (const int a[], int n) { // n = sizeof(a)
    for(int i=1; i<=n; i++) cout << a[i] << " ";
    cout << endl;
}

void solve () {
    int n;
    cout << "Nhap vao so nguyen N: ";
    cin >> n;
    cout << "Nhap vao mang A gom " << n << " so nguyen: ";
    for(int i=1; i<=n; i++) cin >> a[i];

    long long result = getEvenSum(a, n);
    cout << "Tong cac phan tu chan trong mang la: " << result << endl;
}

int main () {
    solve();
}
