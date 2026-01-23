#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const string FILE_NAME = "test";
const int MAXN = 1e5 + 36;
int n, q, a[MAXN];
vector<int> pos[MAXN];

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
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    while (q--) {
        int l,r,x;
        cin >> l >> r >> x; // find the number of element equal x in a[l..r]
       
        int res = 0;
        if (pos[x].empty()) {
            cout << 0 << endl;
            continue;
        }

        // auto lo = lower_bound(pos[x].begin(), pos[x].end(), l); // first position >= l
        // auto hi = upper_bound(pos[x].begin(), pos[x].end(), r); // last position <= r

        int left = 0, right = (int)pos[x].size() - 1, st_pos = -1;
        while (left <= right) { // find first position >= l
            int mid = (left + right) >> 1;
            if (pos[x][mid] >= l) {
                st_pos = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        left = 0, right = (int)pos[x].size() - 1;
        int en_pos = -1;
        while (left <= right) { // find last position <= r
            int mid = (left + right) >> 1;
            if (pos[x][mid] <= r) {
                en_pos = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        // cout << st_pos << " " << en_pos << endl;
        if (st_pos == -1 || en_pos == -1) {
            cout << 0 << endl;
            continue;
        }
        res = en_pos - st_pos + 1;
        cout << res << endl;
    }
}