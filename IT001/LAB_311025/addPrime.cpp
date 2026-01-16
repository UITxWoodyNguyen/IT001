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

int findNearestPrime (int x) {
    if (isPrime[x]) return x;
    int lower_idx = x-1, upper_idx = x+1;
    while (lower_idx >= 2 || upper_idx < MAXN) {
        if (lower_idx >= 2 && isPrime[lower_idx]) return lower_idx;
        if (upper_idx < MAXN && isPrime[upper_idx]) return upper_idx;
        lower_idx--;
        upper_idx++;
    }
}

void replace_element (int index) {
    int value = findNearestPrime(a[index]);
    a[index] = value;
}

void add_element (int a[], int index, int value) {
    a[index] = value;
}

void addPrimeAfter (int a[], int index) {
    int value = findNearestPrime(a[index]);
    for (int i = MAXN-2; i > index; i--) a[i+1] = a[i]; 
    // dich chuyen phan tu ve sau 1 vi tri --> a[index+1] trong --> co the them phan tu moi
    add_element(a, index + 1, value);
}

void solve () {
    int n;
    cout << "Nhap vao so nguyen N: ";
    cin >> n;
    int rawN = n;
    cout << "Nhap vao mang A gom " << n << " so nguyen: ";
    for(int i=1; i<=n; i++) cin >> a[i], raw[i] = a[i];

    for(int i=1; i<=n; i++) replace_element(i);
    cout << "Mang A sau khi thay the cac phan tu bang so nguyen to gan nhat la: " << endl;
    printArray(a, n);

    copyArray(raw, a, rawN);
    n = rawN;
    for(int i=1; i<=n; i++) {
        if (!isPrime[a[i]]) {
            addPrimeAfter(a, i); // neu a[i] khong phai la so nguyen to, them so nguyen to vao sau no
            n++;
            i++; // vi tri i+1 se la so nguyen to vua them vao --> bo qua
        }
        // printArray(a, n);
    }
    cout << "Mang A sau khi them cac so nguyen to sau cac phan tu khong la so nguyen to la: " << endl;
    printArray(a, n);
}

int main () {
    erathosen();
    solve();
}
