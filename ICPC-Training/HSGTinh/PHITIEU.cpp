#include <bits/stdc++.h>
using namespace std;

const string FILE_NAME = "test";
const int MAXN = 350+36;
int n,m,k;
bool board[MAXN][MAXN]; // board[i][j] = 1 neu o (i,j) co bong no
int dp[MAXN][MAXN]; // dp[i][j] = kich thuoc o vuong lon nhat co goc duoi phai la (i,j)

int get_min (int a, int b, int c) {
    return min(a, min(b,c));
}

int update () {
    int curMax = -1;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
        if (!board[i][j]) {
            dp[i][j] = get_min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1;
            curMax = max(curMax, dp[i][j]);
        } else dp[i][j] = 0;
    }

    return curMax;
}
    

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    if (fopen((FILE_NAME + ".inp").c_str(), "r")) {
        freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
        freopen((FILE_NAME + ".out").c_str(), "w", stdout);
    }

    cin >> n >> m >> k;
    memset(board, 0, sizeof(board));
    int res = update();
    while (k--) {
        int row, col;
        cin >> row >> col;
        board[row][col] = 1;

        if (dp[row][col] > 0) res = update();
        cout << res << "\n";
    }
}