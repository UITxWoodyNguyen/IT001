#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const string FILE_NAME = "test";
const int MAXN = 1e5 + 36;
int n;
long long a[MAXN], pfs[MAXN], k;

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

    cin >> n >> k;
    for(int i = 0; i < n; i++) cin >> a[i];

    long long res = 0;
    pfs[0] = 0;
    for(int i = 1; i <= n; i++) pfs[i] = pfs[i-1] + a[i-1];

    for(int i = 1; i <= n; i++) {
        long long target = pfs[i] - k;
        int l = 0, r = i-1, ans = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (pfs[mid] <= target) {
                ans = mid;
                l = mid + 1;
            } else r = mid - 1;

        }

        if (ans != -1) res += (ans + 1);
    }

    cout << res;
}