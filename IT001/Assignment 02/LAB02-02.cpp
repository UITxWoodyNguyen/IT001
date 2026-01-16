#include <bits/stdc++.h>
using namespace std;

const string hexs = "0123456789ABCDEF";

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cout << "Hello" << endl << "\033[31mInfoSec\033[0m" << endl << "👥🌐🔒🔑💻" << endl;
    int N = 2025;
    
    // hex change
    int n = N;
    string res = "";
    while (n) {
        res += hexs[n % 16];
        n /= 16;
    }
    for (int i = res.size() - 1; i >= 0; i--) cout << res[i];
    cout << endl;

    // bin change
    n = N;
    res = "";
    while (n) {
        res += (n % 2) + '0';
        n /= 2;
    }
    for (int i = res.size() - 1; i >= 0; i--) cout << res[i];
    cout << endl;
    return 0;
}
