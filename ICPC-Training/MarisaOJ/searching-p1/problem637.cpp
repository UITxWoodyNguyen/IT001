#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const string FILE_NAME = "test";
const int MAXN = 2e5 + 36;
int n;
long long a[MAXN], pfs[MAXN], sum;

void file_processing (string filename) {
    if (fopen((filename + ".inp").c_str(), "r")) {
        freopen((filename + ".inp").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
}

long long getSum (int l, int r) {
    return pfs[r] - pfs[l-1];
}

bool compareByFirst (pair<long long, int> a, pair<long long, int> b) {
    return a.first < b.first;
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    file_processing (FILE_NAME);

    cin >> n >> sum;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        pfs[i] = pfs[i-1] + a[i];
    }

    int maxLength = -1;
    vector<pair<long long, int>> compress; // (prefix sum, index) - list of increasing pfs
    compress.emplace_back(0, 0);

    for(int i = 1; i <= n; i++) {
        long long target = pfs[i] - sum;
        // find the first prefix sum >= target
        int l = 0, r = (int)compress.size() - 1, pos = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (compress[mid].first >= target) {
                pos = mid;
                r = mid - 1;
            } else l = mid + 1;
        }

        if (pos != -1) {
            int curLength = i - compress[pos].second;
            maxLength = max(maxLength, curLength);
        }
        // maintain the increasing property of compress
        if(pfs[i] > compress.back().first) compress.emplace_back(pfs[i], i);
    }

    cout << maxLength << endl;
}