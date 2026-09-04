#include <bits/stdc++.h>
using namespace std;

#define JUDGE(name) if (fopen(name".inp", "r")) { freopen(name".inp","r",stdin); freopen(name".out","w",stdout); }
const int MAXN = 1e5+5;
int n,a[MAXN];

void countDigits (int x, int numCount[]) {
    x = (x < 0 ? -x : x);
    while (x) {
        numCount[x % 10]++;
        x /= 10;
    }
}

void solve () {
    cout << "Nhap vao so nguyen N: ";
    cin >> n;
    cout << "Nhap vao mang A gom " << n << " so nguyen: ";
    for(int i=1; i<=n; i++) cin >> a[i];

    int numCount[10] = {0};
    for(int i=1; i<=n; i++) countDigits(a[i], numCount);
    for(int i=0; i<=9; i++) cout << "Chu so " << i << " xuat hien " << numCount[i] << " lan\n";
}

int main () {
    solve();
}
