#include <bits/stdc++.h>
using namespace std;

#define JUDGE(name) if (fopen(name".inp", "r")) { freopen(name".inp","r",stdin); freopen(name".out","w",stdout); }
const int MAXN = 1e5+5;
int a[MAXN],raw[MAXN];
bool isPrime[MAXN];

void erathosen() {
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i < MAXN; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j < MAXN; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

void printArray(int a[], int n) {
    for (int i = 1; i <= n; i++) cout << a[i] << " ";
    cout << endl;
}

void copyArray (const int raw[], int a[], int n) {
    for(int i=1; i<=n; i++) a[i] = raw[i];
}

int findFirstPrimeIndex (int a[], int n) {
    for(int i=1; i<=n; i++) if (isPrime[a[i]]) return i;
    return -1;
}

int findLastPrimeIndex (int a[], int n) {
    for(int i=n; i>=1; i--) if (isPrime[a[i]]) return i;
    return -1;
}

void delete_element (int a[], int &n, int index) {
    for(int i=index; i<n; i++) a[i] = a[i+1];
    n--;
}

void deleteFirstPrime (int a[], int& n) {
    int pos = findFirstPrimeIndex(a, n);
    if (pos == -1) return;
    delete_element(a, n, pos);
}

void deleteLastPrime (int a[], int& n) {
    int pos = findLastPrimeIndex(a, n);
    if (pos == -1) return;
    delete_element(a, n, pos);
}

void deleteAllPrimes (int a[], int &n) {
    int writeIndex = 1;
    for(int i=1; i<=n; i++) {
        if (!isPrime[a[i]]) a[writeIndex++] = a[i];
    }
    n = writeIndex - 1;
}

void solve () {
    int n;
    cout << "Nhap vao so nguyen N: ";
    cin >> n;
    int rawN = n;
    cout << "Nhap vao mang A gom " << n << " so nguyen: ";
    for(int i=1; i<=n; i++) cin >> a[i], raw[i] = a[i];

    deleteFirstPrime(a, n);
    cout << "Mang A sau khi xoa so nguyen to dau tien: ";
    printArray(a, n);

    n = rawN;
    copyArray(raw, a, n);
    deleteLastPrime(a, n);
    cout << "Mang A sau khi xoa so nguyen to cuoi cung: ";
    printArray(a, n);

    n = rawN; // reset n
    copyArray(raw, a, n); // reset a
    deleteAllPrimes(a, n);
    cout << "Mang A sau khi xoa tat ca so nguyen to: ";
    printArray(a, n);
}

int main () {
    erathosen();
    solve();
}
