#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const string FILE_NAME = "test";
const int MAXN = 1e5 + 36;
long long k;

void file_processing (string filename) {
    if (fopen((filename + ".inp").c_str(), "r")) {
        freopen((filename + ".inp").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
}

long long countDigits (long long x) { // count number of digits from 1 to x
    long long res = 0;
    int length = 1;
    for(long long start = 1; start <= x; start *= 10, length++) {
        long long end = start * 10 - 1;
        if (end > x) end = x;
        res += (end - start + 1) * length;
    }

    return res;
}

string convertToString (long long x) {
    string res = "";
    while (x) {
        res = char((x % 10) + '0') + res;
        x /= 10;
    }
    return res;
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    file_processing (FILE_NAME);

    cin >> k;
    long long l = 1, r = 1e18+7LL, ans = -1;
    while (l <= r) {
        long long mid = (l + r) >> 1;
        if (countDigits(mid) >= k) {
            ans = mid;
            r = mid - 1;
        } else l = mid + 1;
    }

    // cout << ans << endl;
    long long numDigitBe4 = countDigits(ans - 1);
    string ansStr = convertToString(ans);
    cout << ansStr[k - numDigitBe4 - 1] << endl;
}