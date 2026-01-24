#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const string FILE_NAME = "test";
const int MAXN = 1e5 + 36;
int q;
vector<long long> hammingNumber;

void generateNum() {
    set<long long> s;
    s.insert(1);
    hammingNumber.push_back(1);
    for (auto it = s.begin(); it != s.end(); ++it) {
        long long current = *it;
        if (current > 1e18) break;
        for (int factor : {2, 3, 5}) {
            long long next = current * factor;
            if (next <= 1e18 && s.find(next) == s.end()) {
                s.insert(next);
                hammingNumber.push_back(next);
            }
        }
    }
    sort(hammingNumber.begin(), hammingNumber.end());
}

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

    generateNum();
    cin >> q;
    while (q--) {
        long long m;
        cin >> m;
        auto it = lower_bound(hammingNumber.begin(), hammingNumber.end(), m);
        if (it != hammingNumber.end() && *it == m) cout << (it - hammingNumber.begin() + 1) << endl;
        else cout << -1 << endl;
    }
}