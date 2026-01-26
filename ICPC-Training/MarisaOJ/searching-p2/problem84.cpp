#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const string FILE_NAME = "test";
const int MAXN = 1e5 + 36;

long long cntNum (long long mid) {
    long long cnt3 = mid / 3;
    long long cnt5 = mid / 5;
    long long cnt7 = mid / 7;

    long long cnt35 = mid / 15;
    long long cnt37 = mid / 21;
    long long cnt57 = mid / 35;

    long long cnt357 = mid / 105;
    long long total = cnt3 + cnt5 + cnt7 - cnt35 - cnt37 - cnt57 + cnt357;
    return total;
}

void file_processing (string filename) {
    if (fopen((filename + ".inp").c_str(), "r")) {
        freopen((filename + ".inp").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    file_processing (FILE_NAME);

    long long k;  
    cin >> k;

    long long l = 1, r = 2e18+36, ans = -1;
    while (l <= r) {
        long long mid = (l + r) >> 1;
        if (cntNum(mid) >= k) {
            ans = mid;
            r = mid - 1;
        } else l = mid + 1;
    }

    cout << ans << endl;
}