#include <bits/stdc++.h>
using namespace std;

#define JUDGE(name) if (fopen(name".inp", "r")) { freopen(name".inp","r",stdin); freopen(name".out","w",stdout); }
const int MAXN = 1e5+5;
double a[MAXN],raw[MAXN];
bool isPos[MAXN];

void printRealArray(double a[], int n) {
    for(int i=1; i<=n; i++) {
        cout << fixed << setprecision(4) << a[i] << " ";
    }
    cout << "\n";
}

void printArray (int a[], int n) {
    for(int i=1; i<=n; i++) {
        cout << a[i] << " ";
    }
    cout << "\n";
}

double getDist (int u, int v) {
    return abs(a[u] - a[v]);
}

void updateMin (int &index_low, int &index_high, int i, int j) {
    index_low = i;
    index_high = j;
}

bool isValid (int n) {
    if (n==1) return 0;
    int cnt = 0;
    for(int i=1; i<=n; i++) cnt += (isPos[i] > 0);
    return (cnt >= 2);
}

void solve () {
    int n;
    cout << "Nhap vao so nguyen N: ";
    cin >> n;
    int rawN = n;
    cout << "Nhap vao mang A gom " << n << " so thuc: ";
    for(int i=1; i<=n; i++) {
        cin >> a[i], raw[i] = a[i];
        isPos[i] = (a[i] > 0);
    }

    if (!isValid(n)) {
        cout << "Mang khong hop le de tim khoang cach giua hai so duong!\n";
        return;
    }
    
    int index_low = 1, index_high = n;
    double dist = 1e9;
    for(int i=1; i<=n; i++) {
        if (!isPos[i]) continue;
        for(int j=i+1; j<=n; j++) {
            if (!isPos[j]) continue;
            if (getDist(i, j) < dist) {
                updateMin(index_low, index_high, i, j);
                dist = getDist(i, j);
            }
        }
    }

    cout << fixed << setprecision(3);
    cout << "Khoang cach nho nhat giua hai so duong la: " << dist << "\n";
    cout << "Hai so duong gan nhau nhat la: " << a[index_low] << " va " << a[index_high] << "\n";
}

int main () {
    solve();
}
