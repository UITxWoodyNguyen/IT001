#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const string FILE_NAME = "test";
const int MAXN = 1e5 + 36;
struct Candies {
    long long num, weight;
} a[MAXN];
int n,q;
long long pfs[MAXN];

void file_processing (string filename) {
    if (fopen((filename + ".inp").c_str(), "r")) {
        freopen((filename + ".inp").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
}

bool compare (const Candies u, const Candies v) {
    return u.weight <= v.weight;
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    file_processing (FILE_NAME);

    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> a[i].num >> a[i].weight;
    sort(a+1,a+n+1,compare);
    for(int i = 1; i <= n; i++) pfs[i] = pfs[i-1] + a[i].num; // prefix sum of number of candies
    while (q--) {
        long long k;
        cin >> k; // find the k-th candies in the sorted list

        int l = 1, r = n, type = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (pfs[mid] >= k) { // find the first position that pfs[mid] >= k
                type = mid;
                r = mid - 1;
            } else l = mid + 1;
        }

        cout << a[type].weight << endl;
    }
}