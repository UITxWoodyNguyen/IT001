#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const string FILE_NAME = "test";
const int MAXN = 1e5 + 36;
int n;
long long a[MAXN],l,r;
map<long long, int> countSum;

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

    cin >> n >> l >> r; // find the number of (i,j) that l <= a[i] + a[j] <= r
    for(int i = 1; i <= n; i++) cin >> a[i];
    
    sort(a + 1, a + n + 1);
    long long res = 0;
    for(int i = 1; i <= n; i++) {
        int low = l - a[i]; // a[i] + a[j] >= l  => a[j] >= l - a[i]
        int high = r - a[i]; // a[i] + a[j] <= r  => a[j] <= r - a[i]
        int left = lower_bound(a + 1, a + n + 1, low) - a; // first position that a[j] >= low
        int right = upper_bound(a + 1, a + n + 1, high) - a - 1; // last position that a[j] <= high
        res += max(0, right - left + 1);
        if (a[i] * 2 >= l && a[i] * 2 <= r) res--;
    }
    cout << res / 2;
}