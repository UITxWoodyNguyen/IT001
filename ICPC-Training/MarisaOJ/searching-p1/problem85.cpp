#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const string FILE_NAME = "test";
const int MAXN = 1e5 + 36;
int n,a[MAXN];

void file_processing (string filename) {
    if (fopen((filename + ".inp").c_str(), "r")) {
        freopen((filename + ".inp").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

//    file_processing (FILE_NAME);

    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    int res = 0; // number of triple (i, j, k) that (i < j < k) and (a[i], a[j], a[k]) is a triangle

    for(int j = 2; j < n; j++) {
        for(int i = 1; i <= j-1; i++) {
            int sum = a[i] + a[j];

            int l = j + 1, r = n, pos = j;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (a[mid] < sum) {
                    pos = mid;
                    l = mid + 1;
                } else r = mid - 1;
            }

            res += (pos - j);
        }
    }

    cout << res << endl;
    return 0;
}