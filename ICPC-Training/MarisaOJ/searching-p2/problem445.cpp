#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const string FILE_NAME = "test";
const int MAXN = 1e5 + 36;
int n;
long long k, a[MAXN];

template <typename T> T getMid (T a, T b, T base) { return ((a + b) / base); }

void file_processing (string filename) {
    if (fopen((filename + ".inp").c_str(), "r")) {
        freopen((filename + ".inp").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
}

long long countPair (long long x) {
    long long cnt = 0;
    int l = 1;
    for(int r = 1; r <= n; r++) {
        while (l <= n && a[r] - a[l] > x) l++;
        cnt += (r - l);
    }
    return cnt;
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    file_processing (FILE_NAME);

    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    
    int l = 0, r = a[n] - a[1];
    int ans = r;
    while (l <= r) {
        long long mid = getMid(l, r, 2);
        if (countPair(mid) >= k) {
            ans = mid;
            r = mid - 1;
        } else l = mid + 1;
    }

    cout << ans;
    return 0;
}