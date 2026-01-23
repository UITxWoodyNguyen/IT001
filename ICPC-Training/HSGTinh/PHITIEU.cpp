#include <bits/stdc++.h>
using namespace std;

const string FILE_NAME = "test";
const int MAXN = 350+36;
int n,m,k;
bool board[MAXN][MAXN]; // board[i][j] = 1 neu o (i,j) co bong no
int dp[MAXN][MAXN]; // dp[i][j] = kich thuoc o vuong lon nhat co goc duoi phai la (i,j)

class subtask_1 {
    /* N, M <= 50*/
    private: 
        int get_min (int a, int b, int c) {
            return min(a, min(b,c));
        }

        void update (int &res) {
            int curMax = -1;
            for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
                if (!board[i][j]) {
                    dp[i][j] = get_min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1;
                    curMax = max(curMax, dp[i][j]);
                } else dp[i][j] = 0;
            }

            res = curMax;
        }

    public:
        void solve() {
            memset(board, 0, sizeof(board));
            int res;
            update(res);
            while (k--) {
                int row, col;
                cin >> row >> col;
                board[row][col] = 1;

                if (dp[row][col] > 0) update(res);
                cout << res << "\n";
            }
        }
};  

class SEGTREE {
    private:
        int segTree[4*MAXN][4*MAXN];

    public:
        // Update col
        void update_y(int nodeX, int leftX, int rightX, int nodeY, int leftY, int rightY, int x, int y, int val) {
            if (leftY == rightY) {
                if (leftX == rightX) segTree[nodeX][nodeY] = val;
                else segTree[nodeX][nodeY] = max(segTree[nodeX * 2][nodeY], segTree[nodeX * 2 + 1][nodeY]);
            } else {
                int midY = (leftY + rightY) / 2;
                if (y <= midY) update_y(nodeX, leftX, rightX, nodeY * 2, leftY, midY, x, y, val);
                else update_y(nodeX, leftX, rightX, nodeY * 2 + 1, midY + 1, rightY, x, y, val);
                segTree[nodeX][nodeY] = max(segTree[nodeX][nodeY * 2], segTree[nodeX][nodeY * 2 + 1]);
            }
        }

        // Update row
        void update_x(int nodeX, int leftX, int rightX, int x, int y, int val) {
            if (leftX != rightX) {
                int midX = (leftX + rightX) / 2;
                if (x <= midX) update_x(nodeX * 2, leftX, midX, x, y, val);
                else update_x(nodeX * 2 + 1, midX + 1, rightX, x, y, val);
            }
            update_y(nodeX, leftX, rightX, 1, 1, m, x, y, val);
        }

        // Truy vấn Max trong vùng theo chiều Y
        int query_y(int nodeX, int nodeY, int treeLeftY, int treeRightY, int leftY, int rightY) {
            if (leftY > rightY) return 0;
            if (leftY == treeLeftY && rightY == treeRightY) return segTree[nodeX][nodeY];
            int treeMidY = (treeLeftY + treeRightY) / 2;
            return max(query_y(nodeX, nodeY * 2, treeLeftY, treeMidY, leftY, min(rightY, treeMidY)),
                query_y(nodeX, nodeY * 2 + 1, treeMidY + 1, treeRightY, max(leftY, treeMidY + 1), rightY));
        }

        // Truy vấn Max trong vùng theo chiều X
        int query_x(int nodeX, int treeLeftX, int treeRightX, int leftX, int rightX, int leftY, int rightY) {
            if (leftX > rightX) return 0;
            if (leftX == treeLeftX && rightX == treeRightX) return query_y(nodeX, 1, 1, m, leftY, rightY);
            int treeMidX = (treeLeftX + treeRightX) / 2;
            return max(query_x(nodeX * 2, treeLeftX, treeMidX, leftX, min(rightX, treeMidX), leftY, rightY),
                query_x(nodeX * 2 + 1, treeMidX + 1, treeRightX, max(leftX, treeMidX + 1), rightX, leftY, rightY));
        }
};

bool check(int L) {
    if (L <= 0) return true;
    SEGTREE segtree;
    for (int i = 1; i <= n - L + 1; ++i) {
        for (int j = 1; j <= m - L + 1; ++j) {
            if (segtree.query_x(1, 1, n, i, i + L - 1, j, j + L - 1) == 0) return true;
        }
    }
    return false;
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    if (fopen((FILE_NAME + ".inp").c_str(), "r")) {
        freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
        freopen((FILE_NAME + ".out").c_str(), "w", stdout);
    }

    cin >> n >> m >> k;
    
    // if (n <= 50 && m <= 50) {
    //     subtask_1 solver;
    //     solver.solve();
    //     return 0;
    // } 

    vector<pair<int,int>> query;
    while (k--) {
        int r,c;
        cin >> r >> c;
        query.push_back({r,c});
    }

    SEGTREE segtree;
    for (const auto& p : query) {
        int row = p.first;
        int col = p.second;
        segtree.update_x(1, 1, n, row, col, 1); // Đánh dấu có bóng nổ tại (row, col)

    /*
        int left = 0, right = min(n, m), ans = 0;
        while (left <= right) { // Binary search kich thuoc L
            int mid = (left + right) >> 1;
            if (check(mid)) {
                ans = mid;
                left = mid + 1;
            } else right = mid - 1;
        }
    */

        int ans = min(n,m);
        while(ans > 0 && !check(ans)) ans--;

        cout << ans << "\n";
    }
}