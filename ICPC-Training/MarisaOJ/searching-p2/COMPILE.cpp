#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const string FILE_NAME = "test";
const int MAXN = 1e5 + 36;
int n,k;
struct Element {
    long long weight, value;
} a[MAXN];

template <typename T> T getMid (T a, T b, T base) { return ((a + b) / base); }

void file_processing (string filename) {
    if (fopen((filename + ".inp").c_str(), "r")) {
        freopen((filename + ".inp").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
}

const int RANGE = 100;
bool check (long double mid) { // check if we can have average >= mid
    vector<long double> f;
    for(int i = 1; i <= n; i++) {
        long double cur = (long double) a[i].value - mid * (long double) a[i].weight;
        f.push_back(cur);
    }

    long double sum = 0;
    sort(f.begin(), f.end(), greater<long double>());
    for(int i = 0; i < k; i++) sum += f[i];
    return sum >= 0;
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    file_processing (FILE_NAME);

    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> a[i].value >> a[i].weight;

    long double ans = 0;
    long double left = 0, right = 1e9;
    for(int i = 0; i < RANGE; i++) {
        long double mid = getMid(left, right, (long double) 2);
        if (check(mid)) {
            ans = mid;
            left = mid;
        } else right = mid;
    }

    cout << fixed << setprecision(10) << ans << endl;
    return 0;
}