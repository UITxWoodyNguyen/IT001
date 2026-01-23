#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const string FILE_NAME = "test";
const int MAXN = 1e5 + 36;
int n,q;
long long a[MAXN];
map<int, bool> mp;

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
    for(int i = 1; i <= n; i++) cin >> a[i], mp[a[i]] = true;
    while (q--) {
        int num;
        cin >> num;

        if (!mp[num]) {
            cout << -1 << endl;
            continue;
        }

        int l = 1, r = n, pos = -1; // pos is the minimun position that a[pos] = num
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (a[mid] < num) l = mid + 1;
            else {
                pos = mid;
                r = mid - 1;
            }
        }

        cout << pos << endl;
    }
}