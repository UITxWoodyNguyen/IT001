#include <bits/stdc++.h>
using namespace std;

const string FILE_NAME = "test";

long long k, n;

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    if (fopen((FILE_NAME + ".inp").c_str(), "r")) {
        freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
        freopen((FILE_NAME + ".out").c_str(), "w", stdout);
    }

    cin >> k >> n;
    long long s = 1, temp = n; 
    // s la so nguyen nho nhat sao cho n * s la so chinh phuong -> s la tich cac tsnt mu le cua n
    
    // phan tich n thanh tsnt
    for(int i = 2; i <= sqrt(n); i++) {
        if (temp % i == 0) {
            int cnt = 0;
            while (temp % i == 0) {
                cnt++;
                temp /= i;
            }

            if (cnt & 1) s *= i;
        }
    }

    if (temp > 1) s *= temp; // neu con so nguyen to cuoi cung

    long long res = sqrt(k / s);
    while (res * res > k / s) res--;
    while ((res + 1) * (res + 1) <= k / s) res++;
    cout << res;
}