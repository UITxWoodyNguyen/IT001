#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const string FILE_NAME = "test";
const int MAXN = 1e5 + 36;
int n,k;
long long a[MAXN];

void file_processing (string filename) {
    if (fopen((filename + ".inp").c_str(), "r")) {
        freopen((filename + ".inp").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
}

bool check (long long limit, int k) { // check if we can split into <= k groups with max sum <= limit
    int cntGroups = 0;
    long long curSum = 0;

    for(int i = 1; i <= n; i++) {
        if (curSum + a[i] <= limit) curSum += a[i];
        else {
            cntGroups++;
            curSum = a[i];
        }
    }
    cntGroups++;
    return cntGroups <= k;
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    file_processing (FILE_NAME);

    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> a[i];

    long long maxVal = -1, sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += a[i];
        maxVal = max(maxVal, a[i]);
    }

    long long left = maxVal, right = sum, ans = sum;
    while (left <= right) {
        long long mid = (left + right) >> 1;
        if (check(mid, k)) {
            ans = mid;
            right = mid - 1;
        } else left = mid + 1;
    }

    cout << ans;
}