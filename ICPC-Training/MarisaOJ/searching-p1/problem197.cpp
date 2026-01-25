#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const string FILE_NAME = "test";
const int MAXN = 1e5 + 36;
int n;

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

    cin >> n;
    vector<long long> a;
    for(int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        a.push_back(x);
    }
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    int numElement = n, maxKeep = 0;
    n = a.size();
    for(int i = 0; i < n; i++) {
        long long target = a[i] + numElement - 1; // max value to keep
        auto it = upper_bound(a.begin(), a.end(), target); // first element > target
        int idx = it - (a.begin() + i);
        maxKeep = max(maxKeep, idx);
    }
    cout << numElement - maxKeep << endl;

    return 0;
}