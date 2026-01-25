#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const string FILE_NAME = "test";
const int MAXN = 1e5 + 36;
string a,b;
int pfs[MAXN][26]; // pfs[i][c]: number of character ('a' + c) in a[0..i-1]

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

    cin >> a >> b;
    int n = a.size(), m = b.size();

    for(int i = 0; i < n; i++) {
        for(int c = 0; c < 26; c++) pfs[i + 1][c] = pfs[i][c];
        pfs[i + 1][a[i] - 'a']++;
    }

    int res = 0;
    int cntSubstring = n - m + 1; // number of substrings of a with length m
    for(int i = 0; i < m; i++) {
        int charIndex = b[i] - 'a';
        int lo = i, hi = i + cntSubstring - 1, pos = -1;
        // while (lo <= hi) { // binary search for the first substring that contains b[i]
        //     int mid = (lo + hi) / 2;
        //     int countInSubstring = pfs[mid + 1][charIndex] - pfs[i][charIndex];
        //     if (countInSubstring > 0) {
        //         pos = mid;
        //         hi = mid - 1;
        //     } else {
        //         lo = mid + 1;
        //     }
        // }

        // cout << "For b[" << i << "] = " << b[i] << ", first position in a: " << pos << endl;
        // int cntFound = (pos == -1) ? 0 : (cntSubstring - (pos - i)); // number of substrings containing b[i]
        // res += cntFound;

        int cntFound = pfs[hi+1][charIndex] - pfs[lo][charIndex]; // number of substrings containing b[i]
        res += cntFound;
    }
    cout << res;
}