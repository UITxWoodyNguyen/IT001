#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const string FILE_NAME = "test";
const int MAXN = 1e5 + 36;
int n;
long long k, a[MAXN], Area[MAXN];

template <typename T> T getMid (T a, T b, T base) { return ((a + b) / base); }

void file_processing (string filename) {
    if (fopen((filename + ".inp").c_str(), "r")) {
        freopen((filename + ".inp").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
}

const int RANGE = 100;
bool check (long double x) { // check if we can have at least k pieces with area = x
    if (x <= 0) return true;
    long long cnt = 0;
    for(int i = 1; i <= n; i++) {
        cnt += Area[i] / x;
        if (cnt >= k) return true;
    }
    return cnt >= k;
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    file_processing (FILE_NAME);

    cin >> n >> k;
    long long maxArea = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        Area[i] = (long long) (a[i] * a[i]);
        maxArea = max(maxArea, Area[i]);
    }

    long double left = 0, right = maxArea, ans = 0.0;
    for(int time = 0; time < RANGE; time++) {
        long double mid = getMid(left, right, (long double) 2);
        // cout << mid << endl;
        if (check(mid)) left = mid;
        else right = mid;
    }

    cout << fixed << setprecision(3) << left << endl;
    return 0;
}