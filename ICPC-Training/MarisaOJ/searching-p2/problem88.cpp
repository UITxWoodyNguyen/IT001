#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const string FILE_NAME = "test";
const int MAXN = 1e5 + 36;
long long n,m;
long long k;

void file_processing (string filename) {
    if (fopen((filename + ".inp").c_str(), "r")) {
        freopen((filename + ".inp").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
}

long long count (long long x, long long m) {
    long long cnt = 0;
    for(int i = 1; i <= n; i++) cnt += min(m, 1LL * (x / i));
    return cnt;
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    // file_processing (FILE_NAME);

    cin >> n >> m >> k;
    long long l = 1, r = m*n, ans = m*n;
    while (l <= r) {
        long long mid = (l + r) >> 1;
        if (count(mid, m) >= k) {
            ans = mid;
            r = mid - 1;
        } else l = mid + 1;
    }
    cout << ans;
}