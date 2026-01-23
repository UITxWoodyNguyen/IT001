# Solution Đề thi HSG Tỉnh Đồng Nai - Bảng A - 2025-2026
###### Author: Woody Nguyen - VNUHCM - UIT

## Bài 1: PHATQUA
- Tóm tắt đề: Cho số nguyên $N$ và dãy $A[1], A[2], ..., A[N]$. Sắp xếp lại dãy $A$ và đếm số phần tử thoả mãn điều kiện với mọi `i` thoả $1 \le i \le n$; $i = A[i]$.
- Giới hạn: $0 \le N \le 10^6$, $0 \le A[i] \le 10^9$
- Solution:
    
    - Thực hiện sắp xếp lại dãy $A$ (dùng hàm `sort()`)
    - Sau khi sắp xếp, duyệt lại qua dãy $A$ và đếm số phần tử thoả mãn điều kiện trên.
- Source code: [`PHATQUA.cpp`](https://github.com/UITxWoodyNguyen/Courses-Self-Learning/blob/main/ICPC-Training/HSGTinh/CAMBIEN.cpp)

## Bài 2: HANGRAO
- Tóm tắt đề: Cho 2 số nguyên $N$ và $K$. Đếm số lượng số nguyên $M$ ($1 \le M \le K$) sao cho $N \cdot M$ là một số chính phương.
- Giới hạn:

    - Subtask 1: $K \le 10^6, N \le 10^3$
    - Subtask 2: $0 \le K \le 10^{18}, 0 \le N \le 10^9$
- Solution:

    - Nhận xét:
        
        - Lấy ví dụ $x = 36$ là một số chính phương. Ta thực hiện tách $x = 36$ thành tích của 2 số có dạng $a \cdot b$, dễ dàng nhận thấy $36 = 12 \cdot 3 = 18 \cdot 2$
        - Thực hiện phân tích từng cặp `(a,b)` ra thừa số nguyên tố, ta có:

            - `(a,b) = (12, 3)`: $12 = 2^2 \cdot 3$; $3 = 3$
            - `(a,b) = (18, 2)`: $18 = 3^2 \cdot 2$; $2 = 2$
        - Từ ví dụ trên, ta có nhận xét tổng quát với 2 số $N$ và $M$ bất kì. Nếu $N$ có thể phân tích dưới dạng $N = S \cdot u^2$ và $M$ có thể phân tích dưới dạng $M = S \cdot v^2$, thì $N \cdot M = S \cdot u^2 \cdot S \cdot v^2 = (S \cdot u \cdot v)^2$.
        - Khi đó $N \cdot M$ là **số chính phương**

    - Thuật toán:

        - Gọi $S$ là số nguyên nhỏ nhất sao cho $S \cdot N$ là **số chính phương**. Ta dễ dàng phân tích được $S$ chính là tích của các thừa số nguyên tố mũ lẻ của $N$.
        - Sau khi tìm được $S$, ta dễ dàng xác định được số $M$ cần tìm sẽ có dạng $M = S \cdot x^2 \le K \Rightarrow x^2 \le \frac{K}{S} \Rightarrow x \le \sqrt{\frac{K}{S}}.$ 
        
    - Số lượng số nguyên $M$ thoả mãn sẽ là số giá trị nguyên của $x$.

- Source code: [`HANGRAO.cpp`](https://github.com/UITxWoodyNguyen/Courses-Self-Learning/blob/main/ICPC-Training/HSGTinh/HANGRAO.cpp)

## Bài 3: CAMBIEN
- Tóm tắt đề: Cho số nguyên $N$ và dãy $A[1], A[2], ..., A[N]$. Đếm bộ số $(i, j, k, t)$ thoả mãn yêu cầu sau:

    - $i < j < k < t$
    - $A[i] + A[j] + A[k] = A[t]$
- Giới hạn:

    - Subtask 1: $N \le 100$
    - Subtask 2: $N \le 2000$
    - Subtask 3: $4 \le N \le 10^5, 1 \le A[i] \le 100$

- Solution:

    - Gọi `countSum[s]` là số lượng bộ số $(i,j)$ sao cho $A[i] + A[j] = s$
    - Nhận xét: Từ $A[i] + A[j] + A[k] = A[t]$, ta biến đổi thành $A[i] + A[j] = A[t] - A[k]$
    - Sử dụng vòng lặp với biến $k$ để thực hiện đếm tất cả các tổng $s = A[i] + A[j]$ (*tính vế trái của biểu thức trong "Nhận xét"*), trong đó $i < j < k$. 
    - Tuy nhiên với mỗi $k$, việc sử dụng thêm 2 vòng lặp lần lượt cho $i$ và $j$ sẽ làm tăng độ phức tạp. Do đó, ta cố định $j = k-1$ để thực hiện đếm, vì khi $k$ tăng, $j$ cũng sẽ tăng kéo theo việc `countSum[s]` sẽ được tính thêm một lần.
    - Sau khi tính xong vế trái, dùng thêm một vòng for với biến $t$ để cộng dồn tổng số lượng các cặp số thoả mãn.
- Source code: [`CAMBIEN`](https://github.com/UITxWoodyNguyen/Courses-Self-Learning/blob/main/ICPC-Training/HSGTinh/PHATQUA.cpp)

## Bài 4: PHITIEU
- Tóm tắt đề: Cho một bảng $A$ kích thước $N \cdot M$ gồm các ô $(i,j)$ có $A[i][j] = 0$ và $K$ truy vấn. Với mỗi truy vấn có dạng $(r,c)$, thực hiện đổi trạng thái $A[r][c] = 1$. Sau mỗi truy vấn, tính kích thước hình vuông lớn nhất chứa toàn trạng thái $0$.
- Giới hạn:

    - Subtask 1: $N, M \le 10$
    - Subtask 2: $N, M \le 50$
    - Subtask 3: $1 \le N, M \le 350$, $1 \le K \le N \cdot M$

- Solution:

    - Với 2 subtask đầu, dọi $dp[i][j]$ là độ dài cạnh hình vuông lớn nhất có góc phải dưới là $(i,j)$. Với mỗi truy vấn, thực hiện đánh dấu trạng thái và update lại $dp[i][j]$ để lấy max.
    - Với subtask 3, việc thực hiện như 2 subtask đầu là không thể do độ phức tạp sẽ trở thành $O(K \cdot M \cdot N)$. Khi đó $max_{O(K \cdot M \cdot N)} = O(350 ^ 4)$ dễ dẫn đến TLE.
    - Ta sử dụng **Segment Tree 2D** với 2 cây lồng nhau để tối ưu hoá việc update, với main tree dùng để quản lý các dòng thuộc khoảng $[1...N]$ và mỗi node thuộc main tree sẽ quản lý một list các dòng thuộc vùng $[left_x, right_x]$; và inner tree quản lý các cột $j$ thuộc khoảng $[1...M]$ của vùng $[left_x, right_x]$. 
        ```c++
        tree[i][j] = 0/1 (left_x <= i <= right_x; 1 <= j <= M)
        ```
    - Khi đó với một vùng có dạng $(r1, c1, r2, c2)$, nếu như max của vùng là $0$ thì vùng đó chưa có ô bị flip trạng thái.
    - Với mỗi truy vấn, ta thực hiện update trạng thái của bảng và thực hiện tính kích thước bảng con lớn nhất thoả điều kiện (`query_x() == 0`).
    - Cách cài đặt Segment tree:
        ```c++
        class SEGTREE {
            private:
                int segTree[4*MAXN][4*MAXN];

            public:
                // Update inner tree
                void update_y(int nodeX, int leftX, int rightX, int nodeY, int leftY, int rightY, int x, int y, int val) {
                    if (leftY == rightY) {
                        if (leftX == rightX) segTree[nodeX][nodeY] = val;
                        else segTree[nodeX][nodeY] = max(segTree[nodeX * 2][nodeY], segTree[nodeX * 2 + 1][nodeY]);
                        return;
                    } 

                    int midY = (leftY + rightY) / 2;
                    if (y <= midY) update_y(nodeX, leftX, rightX, nodeY * 2, leftY, midY, x, y, val);
                    else update_y(nodeX, leftX, rightX, nodeY * 2 + 1, midY + 1, rightY, x, y, val);
            
                    segTree[nodeX][nodeY] = max(segTree[nodeX][nodeY * 2], segTree[nodeX][nodeY * 2 + 1]);
                }

                // Update main tree
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
        ```
- Source code: [`PHITIEU.cpp`](https://github.com/UITxWoodyNguyen/Courses-Self-Learning/blob/main/ICPC-Training/HSGTinh/PHITIEU.cpp)