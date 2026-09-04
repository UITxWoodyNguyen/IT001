// LAB0302.cpp
#include <bits/stdc++.h>
using namespace std;

#define JUDGE(name) if (fopen(name".inp", "r")) { freopen(name".inp","r",stdin); freopen(name".out","w",stdout); }

int getGcd (int a, int b) {
    while (b) {
        int tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

int getLcm (int a, int b) {
    return a / getGcd(a, b) * b;
}

int getSecondGcd (int a, int b) {
    int gcd = getGcd(a, b);
    for(int i = gcd-1; i >= 1; i--) 
        if (a % i == 0 && b % i == 0) {
            return i;
            break;
        }
    
    return 1; // No second GCD found --> answer is 1
}

void solve () {
    int a,b;
    cin >> a >> b;
    cout << "Uoc chung lon nhat la: " << getGcd(a, b) << '\n';
    cout << "Boi chung nho nhat la: " << getLcm(a, b) << '\n';
    cout << "Uoc chung lon nhi la: " << getSecondGcd(a, b) << '\n';
}

int main () {
    JUDGE("woody");
    solve();
}
