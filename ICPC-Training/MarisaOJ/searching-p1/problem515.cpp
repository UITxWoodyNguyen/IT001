#include <bits/stdc++.h>
using namespace std;

const string FILE_NAME = "test";
const int MAXN = 1e5 + 36;
int n,q;
long long a[MAXN];

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

    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> a[i];
    while (q--) {
        int num;
        cin >> num;

        int lo = 1, hi = n, pos = -1;
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            if (a[mid] == num) {
                pos = mid;
                break;
            } else if (a[mid] < num) lo = mid + 1;
            else hi = mid - 1;
        }

        cout << pos << endl;
    }
}