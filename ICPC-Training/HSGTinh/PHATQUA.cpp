#include <bits/stdc++.h>
using namespace std;

const string FILE_NAME = "test";
const int MAXN = 1e5 + 36;
int n,a[MAXN];

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    if (fopen((FILE_NAME + ".inp").c_str(), "r")) {
        freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
        freopen((FILE_NAME + ".out").c_str(), "w", stdout);
    }

    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];

    int res = 0;
    unordered_map<int,int> countSum;
    for(int k = 3; k < n; k++) {
        int j = k-1;
        for(int i = 1; i < j; i++) countSum[a[i] + a[j]]++;
        for(int p = k + 1; p <= n; p++) res += countSum[a[p] - a[k]];
    }

    cout << res;
}