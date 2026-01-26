#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const string FILE_NAME = "test";
const int MAXN = 1e5 + 36;
int n;
long long k,a[MAXN];

void file_processing (string filename) {
    if (fopen((filename + ".inp").c_str(), "r")) {
        freopen((filename + ".inp").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
}

bool check (long long dist, int k) { // check if we can choose k element with the minimum distance of each element is higher or equal to dist
    int cnt = 1;
    long long lastPos = a[1];

    for(int i = 2; i <= n; i++) {
        if (a[i] - lastPos >= dist) {
            cnt++;
            lastPos = a[i];
            if (cnt >= k) return true;
        }
    }
    return cnt >= k;
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    file_processing (FILE_NAME);

    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);

    long long left = 1, right = a[n] - a[1], ans = 0;
    while (left <= right) { // bsearch for the maximum minimum dist
        long long mid = (left + right) / 2;
        if (check(mid, k)) {
            ans = mid;
            left = mid + 1;
        } else right = mid - 1;
    }
    cout << ans << endl;
}