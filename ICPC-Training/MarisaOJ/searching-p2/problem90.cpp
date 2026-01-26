#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const string FILE_NAME = "test";
const int MAXN = 1e5 + 36;
int n,k;
long long a[MAXN];

template <typename T> T getMid (T a, T b) { return (a + b) / 2; }

void file_processing (string filename) {
    if (fopen((filename + ".inp").c_str(), "r")) {
        freopen((filename + ".inp").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
}

const int RANGE = 100;
long double getMin (long double a, long double b) {
    return (a < b) ? a : b;
}

/* (a[l...r] / (r - l + 1)) >= x <--> (pfs[r] - pfs[l-1]) / (r - l + 1) >= x <--> (pfs[r] - pfs[l-1] - x) >= 0 */
bool check (long double x) { // is there a subarray with average >= x
    vector<long double> curPfs(n + 1, 0);
    for(int i = 1; i <= n; i++) curPfs[i] = curPfs[i - 1] + (long double)a[i] - x; 
    long double minPfs = 0; // minimum prefix sum up to index i - k
    for(int i = k; i <= n; i++) { // check subarrays ending at i
        minPfs = getMin(minPfs, curPfs[i - k]);
        if (curPfs[i] - minPfs >= 0) return true;
    }
    return false;
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    file_processing (FILE_NAME);

    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    long double l = 0, r = 1e9;
    for(int time = 0; time < RANGE; time++) { // binary search to find the maximum average
        long double mid = (l + r) / 2.0;
        if (check(mid)) l = mid; // can find a subarray with average >= mid
        else r = mid;
    }

    cout << fixed << setprecision(3) << l << endl;
    return 0;
}