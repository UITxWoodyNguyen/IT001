#include <bits/stdc++.h>
using namespace std;

const string FILE_NAME = "test";
const int MAXN = 1e6 + 36;

long long n, a[MAXN];

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    if (fopen((FILE_NAME + ".inp").c_str(), "r")) {
        freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
        freopen((FILE_NAME + ".out").c_str(), "w", stdout);
    }

    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    sort(a+1, a+n+1);
    int res = 0;
    for(int i = 1; i <= n; i++) if (i == a[i]) res++;
    cout << res;
    return 0;
}