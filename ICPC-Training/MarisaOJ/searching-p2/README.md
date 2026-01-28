# Binary search for answer

## Information
- OJ: [MarisaOJ](https://marisaoj.com/)
- Tag; Binary search

## [Đọc sách](https://marisaoj.com/problem/86)
- Tóm tắt đề: Cho dãy $A$ gồm $N$ phần tử và số nguyên $K$. Chọn ra $K$ số từ $A$ sao cho khoảng cách nhỏ nhất giữa 2 phần tử liên tiếp là lớn nhất.
- Giới hạn: $1 \le N \le 10^5$, $1 \le A[i], K \le 10^9$
- Solution:

    - Thực hiện sắp xếp lại mảng và binary search để tìm khoảng cách thoả mãn.
    - Với mỗi khoảng cách $dist$, ta kiểm tra xem liệu có thể chọn đủ $K$ số với khoảng cách tối thiểu là $dist$ hay không.
        ```c++
        bool check (long long dist, int k) { // check if we can choose k element with the minimum distance of each element is higher or equal to dist
            int cnt = 1;
            long long lastPos = a[1];

            for(int i = 2; i <= n; i++) {
                if (a[i] - lastPos >= dist) {
                    cnt++;
                    lastPos = a[i];
                    if (cnt >= k) return true;
                }
            }
            return cnt >= k;
        }
        ```
- Source code: [BOOK.cpp]()

## [Giá trị lớn nhất nhỏ nhất](https://marisaoj.com/problem/87)
- Tóm tắt đề: Cho dãy $a$ gồm $n$ phần tử và số nguyên $k$. Tìm $min_x$ sao cho khi chia $a$ thành $k$ đoạn con $[l, r]$ thì với mọi $[l, r]$, $a[l] + a[l+1] + ... + a[r] \le x$
- Giới hạn: $1 \le k \le n \le 10^5$, $1 \le a[i] \le 10^9$
- Solution:

    - Nhận xét: Giá trị **nhỏ nhất** thoả mãn điều kiện trên là $Low = max(a[1]...a[n])$, giá trị lớn nhất thoả mãn điều kiện trên là $High = sum(a[1]..a[n])$
    - Ta thực hiện binary search trên vùng $[Low, High]$. Với mỗi giá trị $mid$, thực hiện kiểm tra xem có thể chia dãy $a$ thành $k$ dãy với tổng mỗi dãy không vượt quá $mid$.
        ```c++
        bool check (long long limit, int k) { // check if we can split into <= k groups with max sum <= limit
            int cntGroups = 0;
            long long curSum = 0;

            for(int i = 1; i <= n; i++) {
                if (curSum + a[i] <= limit) curSum += a[i];
                else {
                    cntGroups++;
                    curSum = a[i];
                }
            }
            cntGroups++;
            return cntGroups <= k;
        }
        ```
- Source code: [MINMAX.cpp]()

## [Số đẹp](https://marisaoj.com/problem/84)
- Tóm tắt đề: Tìm số đẹp thứ $k$
    > Số đẹp là số chia hết cho 3, 5 hoặc 7
- Giới hạn: $1 \le k \le 10^{9}$
- Solution: 

    - Nhận xét: Gọi $cnt[i]$ là số phần tử chia hết cho $i$. Số các số nguyên chia hết cho 3, 5 hoặc 7 là 
    $cnt[3] + cnt[5] + cnt[7] - (cnt[3*5] + cnt[5*7] + cnt[3*7]) + cnt[3*5*7]$. 
    - Dựa trên nhận xét, ta có hàm đếm số lượng số đẹp không vượt quá $mid$:
        ```c++
        long long cntNum (long long mid) {
            long long cnt3 = mid / 3;
            long long cnt5 = mid / 5;
            long long cnt7 = mid / 7;

            long long cnt35 = mid / 15;
            long long cnt37 = mid / 21;
            long long cnt57 = mid / 35;

            long long cnt357 = mid / 105;
            long long total = cnt3 + cnt5 + cnt7 - cnt35 - cnt37 - cnt57 + cnt357;
            return total;
        }
        ```
    - Thực hiện binary search trong khoảng $[1...2 \cdot 10^{18}]$ để xác định số thứ $k$ bằng cách tìm giá trí pos nhỏ nhất mà số lượng số đẹp từ 3 đến pos lớn hơn hoặc bằng $k$.
- Source code: [BEAUTYNUM.cpp]()

## [Bảng cửu chương](https://marisaoj.com/problem/88)
- Tóm tắt đề: Cho ma trận $a$ kích thước $n \cdot m$ với $a_{ij} = i \cdot j$. Sắp xếp các phần tử trong ma trận theo chiều tăng dần và tìm phần tử thứ $k$.
- Giới hạn: $1 \le n, m \le 10^5$, $1 \le k \le n \cdot m$
- Solution: Ta thực hiện binary search trên khoảng $[1...n \cdot m]$. Với mỗi giá trị $mid$, thực hiện đếm số lượng phần tử có giá trị nhỏ hơn hoặc bằng $mid$ rồi đem so sánh với $k$ để thu hẹp phạm vi tìm kiếm.
- Source code: [MATH.cpp]()

## [Chữ số thứ K](https://marisaoj.com/problem/89)
- Tóm tắt đề: Viết các số nguyên thành 1 dãy $123456789101112...$. Xác định chữ số thứ $k$ của dãy
- Giới hạn: $1 \le k \le 10^{18}$
- Solution:

    - Thực hiện binary search trong khoảng $[1...10^{18}]$. Với mỗi giá trị $mid$, đếm số chữ số trong dãy $123456...mid$ và so sánh với k.
    - Gọi $ans$ là giá trị nhỏ nhất sao cho số chữ số của dãy $12345...ans$ lớn hơn hoặc bằng $k$. Ta đếm số chữ số của dãy $12345...(ans-1)$ (đặt là $cnt[ans-1]$) và chữ số thứ $k$ của dãy gốc là kí tự thứ $k - cnt[ans-1] - 1$ của $ans$.
- Source code: [KTHNUM.cpp]()

## [Trung bình cộng lớn nhất](https://marisaoj.com/problem/90)
- Tóm tắt đề:  Cho mảng $A$ gồm $n$ phần tử. Tìm dãy con liên tiếp có độ dài ít nhất $k$ sao cho trung bình cộng các phần tử trong dãy đó là lớn nhất.
- Giới hạn: $1 \le k \le n \le 10^5$, $1 \le a[i] \le 10^9$
- Solution:

    - Từ đề bài, ta cần tìm $max_x$ sao cho tồn tại một cặp $[i, j]$ thoả
        $$\frac{\sum_{p=i}^{j} a_p}{j - i + 1} \ge x$$ 
        > với $x$ là trung bình cộng của dãy con
    - Thực hiện biến đổi bằng cách trừ 2 vế cho $x$, ta có được $\sum (a_p - x) \ge 0$ (do mẫu luôn khác 0). Gọi $b_i = a_i - x$, ta cần kiểm tra xem có tồn tại dãy con nào của $b$ có độ dài lớn hơn hoặc bằng $k$ và có tổng không âm hay không.
    - Tại mỗi $i$, gọi $pfs[i] = b[1] + ... + b[i]$, $minPfs = min(pfs[1],...,pfs[i - k])$. Lúc này ta cần tìm $index$ thoả $pfs[index] - minPfs \ge 0$. 
    - Thực hiện binary search giá trị $x$ để tìm $index$ thoả mãn.
- Source code: [AVERAGE.cpp]()

## [Sinh nhật](https://marisaoj.com/problem/91)
- Tóm tắt đề: Có $n$ chiếc bánh hình vuông với cạnh là $A_i$ (chiều cao đều là 1). Cần chia cho $k$ người bạn sao cho mỗi người nhận được một phần bánh có kích cỡ (thể tích) bằng nhau. Ràng buộc quan trọng: mỗi phần bánh phải được cắt từ tối đa 1 chiếc bánh nguyên vẹn (không ghép các miếng nhỏ từ nhiều bánh khác nhau). Tìm kích cỡ phần bánh lớn nhất có thể.
- Giới hạn: $1 \le n, A_i \le 10^5$, $1 \le k \le 10^9$
- Solution:

    - Nhận xét: Nếu mỗi người nhận được phần bánh kích cỡ $x$ mà vẫn đủ cho $k$ người, thì với kích cỡ nhỏ hơn $x$, ta chắc chắn cũng chia đủ. Nếu với kích cỡ $x$ mà không đủ chia, thì mọi kích cỡ lớn hơn $x$ cũng sẽ không đủ.
    - Ta thực hiện binary search với mỗi $mid$, kiểm tra xem liệu có thể chia được ít nhất $k$ phần bánh từ $n$ cái bánh với kích thước $mid$ hay không.
    - Tổng số phần bánh có kích cỡ $x$ có thể cắt được từ $n$ chiếc bánh: $Total = \sum_{i=1}^{n} \lfloor \frac{A_i^2}{x} \rfloor$.
- Source code: [CAKE.cpp]()

## [Sắp xếp hiệu](https://marisaoj.com/problem/445)
- Tóm tắt đề: Cho mảng $A$ gồm $n$ phần tử. Có tất cả $\frac{n(n-1)}{2}$ cặp giá trị tuyệt đối $|A_i - A_j|$. Cần tìm giá trị nhỏ thứ $k$ trong tất cả các hiệu này sau khi đã sắp xếp không giảm.
- Giới hạn: $1 \le n \le 10^5$, $1 \le k \le \frac{n(n-1)}{2}$, $1 \le A_i \le 10^9$
- Solution:

    - Ta cần xác định giá trị $X$ sao cho có ít nhất $k$ cặp $(i, j)$ sao cho $|A_i - A_j| \le X$.
    - Thực hiện sắp xếp mảng $A$ tăng dần. Ta có nhận xét, khi mảng đã được sắp xếp tăng dần $|A_i - A_j| \le X \Rightarrow A_j - A_i \le X \Rightarrow A_j \le A_i + X$. Từ đó ta cần tìm số giá trị $j$ tương ứng với mỗi vị trí $i$. (Dùng **2 pointers**)
    - Binary search để tìm giá trị $X$ thoả mãn.
- Source code: [SUB.cpp](https://github.com/UITxWoodyNguyen/Courses-Self-Learning/blob/main/ICPC-Training/MarisaOJ/searching-p2/problem445.cpp)

## [Thu thập](https://marisaoj.com/problem/440)
- Tóm tắt đề: Cho $n$ món đồ, mỗi món có giá trị $v_i$ và cân nặng $w_i$. Cần chọn đúng $k$ món sao cho tỉ số giữa tổng giá trị và tổng cân nặng là lớn nhất: $\frac{\sum v_{selected}}{\sum w_{selected}} \to \max$.
- Giới hạn:

    - $n, k$ ($1 \le k \le n \le 10^5$).
    - $n$ cặp $(v_i, w_i)$ ($1 \le v_i, w_i \le 10^9$).
- Solution: 

    - Giả sử tỉ số tối ưu là $X$. Ta cần tìm $X$ lớn nhất sao cho tồn tại một cách chọn $k$ món thỏa mãn:
        $$\frac{\sum v_i}{\sum w_i} \ge X \iff \sum v_i \ge X \cdot \sum w_i \iff \sum (v_i - X \cdot w_i) \ge 0$$
    - Với mỗi giá trị $X$ cố định, ta tính giá trị mới $f_i = v_i - X \cdot w_i$ cho từng món đồ. Để tổng $k$ món lớn nhất, ta chỉ cần chọn $k$ món có $f_i$ lớn nhất. Nếu tổng này $\ge 0$, nghĩa là tỉ số $X$ có thể đạt được hoặc cao hơn.
- Source code: [DIV.cpp](https://github.com/UITxWoodyNguyen/Courses-Self-Learning/blob/main/ICPC-Training/MarisaOJ/searching-p2/problem440.cpp)

