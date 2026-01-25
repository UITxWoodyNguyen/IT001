# Introduction to Binary Search

## Information
- OJ: [MarisaOJ](https://marisaoj.com/)
- Tag: Binary Search

## [Tìm kiếm nhị phân](https://marisaoj.com/problem/515)
- Tóm tắt đề: Cho mảng $A$ gồm $N$ phần tử được sắp xếp **tăng dần** và $Q$ truy vấn có dạng "$x$". Xác định vị trí của $x$ trong mảng $A$.
- Giới hạn: $1 \le N, Q \le 10^5$,  $1 \le A[i], x \le 10^9$
- Solution: Thực hiện binary search để tìm kiếm giá trị theo yêu cầu của đề bài.
    ```c++
        int num;
        cin >> num;

        int lo = 1, hi = n, pos = -1;
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            if (a[mid] == num) {
                pos = mid;
                break;
            } else if (a[mid] < num) lo = mid + 1;
            else hi = mid - 1;
        }

        cout << pos << endl;
    ```
- Source code: [BSEARCH01.cpp](https://github.com/UITxWoodyNguyen/Courses-Self-Learning/blob/main/ICPC-Training/MarisaOJ/searching-p1/problem515.cpp)

## [Tìm kiếm nhị phân 2](https://marisaoj.com/problem/76)
- Tóm tắt đề: Cho mảng $A$ gồm $N$ số nguyên và $Q$ truy vấn. Với mỗi truy vấn có dạng "$x$", tìm $index$ nhỏ nhất sao cho $A[index] = x$
- Giới hạn: $1 \le N, Q \le 10^5$,  $1 \le x \le 10^9$
- Solution:

    - Tạo một `map` (do giới hạn của $A[i]$ lên đến $10^9$ nên không thể sử dụng mảng thường) để thực hiện đánh dấu sự xuất hiện của các giá trị trong $A$:
        ```c++
        map<bool, long long> mark;
        mark[a[i]] = true;
        ```
    - Với những giá trị `k` có `map[k] = false`, in ra `-1` và thực hiện truy vấn tiếp theo.
    - Ngược lại, thực hiện binary search để tìm giá trị `index` nhỏ nhất sao cho `a[index] == x`.
        ```c++
        int l = 1, r = n, pos = -1; // pos is the minimun position that a[pos] = num
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (a[mid] < num) l = mid + 1;
            else {
                pos = mid;
                r = mid - 1;
            }
        }
        ```
- Source code: [BSEARCH02.cpp](https://github.com/UITxWoodyNguyen/Courses-Self-Learning/blob/main/ICPC-Training/MarisaOJ/searching-p1/problem76.cpp)

## [Tìm kiếm nhị phân 3](https://marisaoj.com/problem/77)
- Tóm tắt đề: Cho mảng $A$ gồm $N$ số nguyên và $Q$ truy vấn. Với mỗi truy vấn có dạng "$x$", tìm $index$ lớn nhất sao cho $A[index] \le x$
- Giới hạn: $1 \le N, Q \le 10^5$,  $1 \le x \le 10^9$
- Solution: Thực hiện binary search để tìm giá trị `index` lớn nhất sao cho `a[index] <= x`.
    ```c++
    int l = 1, r = n, pos = -1; // pos is the maximum index that a[pos] <= num
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (a[mid] > num) r = mid - 1;
        else {
            pos = mid;
            l = mid + 1;
        }
    }
    ```
- Source code: [BSEARCH03.cpp](https://github.com/UITxWoodyNguyen/Courses-Self-Learning/blob/main/ICPC-Training/MarisaOJ/searching-p1/problem77.cpp)

## [Mảng con lớn](https://marisaoj.com/problem/78)
- Tóm tắt đề: Cho dãy $A$ gồm $N$ phần tử và số nguyên $k$. Đếm số lượng subsequences có tổng lớn hơn hoặc bằng $k$
- Giới hạn: $1 \le N \le 10^5$, $1 \le A[i], k \le 10^9$
- Solution:

    - Gọi `pfs[i] = a[1] + a[2] + ... + a[i]`. Ta dễ dàng có công thức tính `a[l] + a[l+1] + ... + a[r]` với mọi $[l, r]$:
        ```c++
        a[l] + a[l+1] + ... + a[r] = (a[1] + ... + a[r]) - (a[1] + ... + a[l-1]) = pfs[r] - pfs[l-1]
        ``` 
    - Theo đề bài, với mọi $[l, r]$ thoả mãn, $pfs[r] - pfs[l - 1] \ge k$. Thực hiện chuyển vế, ta có được $pfs[l - 1] \le pfs[r] - k$
    - Với mỗi $r$, thực hiện binary search trong khoảng $[0, r - 1]$ để đếm số lượng $l - 1$ thoả mãn điều kiện trên. Số dãy con thoả mãn sẽ là `pos + 1` (với `pos` là index lớn nhất thoả mãn điều kiện trên).
        ```c++
        for(int i = 1; i <= n; i++) {
            long long target = pfs[i] - k;
            int l = 0, r = i-1, ans = -1;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (pfs[mid] <= target) {
                    ans = mid;
                    l = mid + 1;
                } else r = mid - 1;

            }

            if (ans != -1) res += (ans + 1);
        }
        ```
- Source code: [LARGEARRAY.cpp](https://github.com/UITxWoodyNguyen/Courses-Self-Learning/blob/main/ICPC-Training/MarisaOJ/searching-p1/problem78.cpp)

## [Truy vấn đếm](https://marisaoj.com/problem/79)
- Tóm tắt đề: Cho dãy $A$ gồm $N$ phần tử và $Q$ truy vấn có dạng $(l, r, x)$. Đếm số giá trị $x$ trong đoạn $[l, r]$
- Giới hạn: $1 \le N, Q, x, A[i] \le 10^5$, $1 \le l \le r \le N$.
- Solution:

    - Gọi $pos[x]$ là danh sách các index sao cho $A[index] = x$. Lúc này ta chỉ cần đểm số giá trị $pos[x]$ sao cho $l \le pos[x][i] \le r$
    - Với mỗi giá trị $x$, thực hiện binary search để tìm index nhỏ nhất sao cho $pos[x][index] \ge l$ (đặt là $en_{pos}$) và index lớn nhất sao cho $pos[x][index] \le r$ (đặt là $st_{pos}$).
    - Kết quả cần tìm là $en_{pos} - st_{pos} + 1$.
- Source code: [COUNTQUERY.cpp](https://github.com/UITxWoodyNguyen/Courses-Self-Learning/blob/main/ICPC-Training/MarisaOJ/searching-p1/problem79.cpp)

## [Đếm cặp](https://marisaoj.com/problem/80)
- Tóm tắt đề: Cho dãy $A$ gồm $N$ phần tử. Đếm số cặp $(i,j)$ sao cho $i < j$, $l \le A[i] + A[j] \le r$
- Giới hạn: $1 \le N \le 10^5$, $1 \le A[i], l, r \le 10^9$
- Solution:

    - Từ đề bài ta có $l \le A[i] + A[j] \le r \Rightarrow l - A[i] \le A[j] \le r - A[i]$. Đặt $low = l - A[i]$ và $high = r - A[i]$. 
    - Lúc này problem trở thành đếm số vị trí $j$ sao cho $low \le A[j] \le high$ (Giống với bài "[Truy vấn đếm](https://marisaoj.com/problem/79)")
- Source code: [DEMCAP.cpp](https://github.com/UITxWoodyNguyen/Courses-Self-Learning/blob/main/ICPC-Training/MarisaOJ/searching-p1/problem80.cpp)

## [Viên kẹo thứ k](https://marisaoj.com/problem/81)
- Tóm tắt đề: Cho $N$ số nguyên trong khoảng $[1...N]$ và $Q$ truy vấn. Tạo một dãy mới (đặt là $newA[]$) với yêu cầu sau:

    - Với mỗi số nguyên $i$ ($1 \le i \le N$), thực hiện viết lại $a[i]$ lần cho mỗi số $i$
    - Trọng số của mỗi số nguyên $i$ là $w[i]$
    - Ví dụ:
        ```
        i = 1: a[1] = 2, w[1] = 1
        i = 2: a[2] = 1, w[2] = 0
        --> Mảng viết lại là [1, 1, 2]. 
        --> Trọng số với mỗi phần tử là [1, 1, 0]
        ```
    - Với mỗi truy vấn có dạng $k$, xác định trọng số của $newA[k]$
- Giới hạn: 

    - $1 \le N, Q \le 10^5$
    - $1 \le A[i], w[i] \le 10^9$, 
    - $1 \le k \le A[1] + A[2] + ... + A[n] \le 10^{14}$
- Solution:
    - Tạo một `struct` để quản lý đối với mỗi giá trị $i$ (đặt là 1 $node$) bao gồm 2 đối tượng là $num$ và $weight$:
        ```c++
        struct Candies {
            long long num, weight;
        };
        ```
    - Gọi $pfs[i]$ là số lượng giá trị trong dãy $newA[]$ sau khi thêm vào $a[i]$ giá trị $i$. Công thức: $pfs[i] = pfs[i-1] + node[i].num$
    - Với mỗi truy vấn, binary search để tìm index lớn nhất sao cho $pfs[index] \ge k$ (tức số lượng phần tử trong $newA$ vượt quá $k$). 
    - Khi đó, trọng số cần tìm sẽ là $node[index].weight$
- Source code: [CANDIES.cpp](https://github.com/UITxWoodyNguyen/Courses-Self-Learning/blob/main/ICPC-Training/MarisaOJ/searching-p1/problem81.cpp)

## [Cạnh tam giác](https://marisaoj.com/problem/85)
- Tóm tắt đề: Cho dãy $A$ gồm $N$ số nguyên. Đếm bộ số $(i,j,k)$ sao cho $i < j < k$ và $(A[i], A[j], A[k])$ tạo thành một tam giác
- Giới hạn: $1 \le N \le 1500$, $1 \le A[i] \le 10^9$
- Solution:

    - Nhận xét: Theo bất đẳng thức tam giác, tổng 2 cạnh bất kì lớn hơn cạnh còn lại sẽ tạo thành một tam giác. Do đó trong bộ ba $(i,j,k)$ bất kì, ta có thể chọn 2 trong 3 số mà không cần quan tâm tới vị trí.
    - Thực hiện sort lại dãy $A$, dùng vòng lặp để tính $A[i] + A[j]$ và binary search từ $j+1$ tới $N$ để tìm index lớn nhất sao cho $A[index]$ thoả mãn bất đẳng thức. Số giá trị $A[k]$ thoả mãn với mỗi cặp $(i, j)$ sẽ là $index - j$.
- Source code: [TRIANGLE.cpp](https://github.com/UITxWoodyNguyen/Courses-Self-Learning/blob/main/ICPC-Training/MarisaOJ/searching-p1/problem85.cpp)

## [Số Hamming](https://marisaoj.com/problem/82)
- Tóm tắt đề: **Số Hamming** là số có dạng $x = 2^a \cdot 3^b \cdot 5^c$. Cho $Q$ truy vấn, mỗi truy vấn có dạng $m$. Tìm vị trí của $m$ trong dãy số Hamming.
- Giới hạn: $1 \le Q \le 10^5$, $1 \le m \le 10^{18}$
- Solution:

    - Nhận xét: Do số lượng số hamming là rất ít nên ta thực hiện sinh ra một list số Hamming và thực hiện binary search để tìm vị trí của m trên list đó.
    - Cách sinh số Hamming:
        ```c++
        void generateNum() {
            set<long long> s;
            s.insert(1);
            hammingNumber.push_back(1);
            for (auto it = s.begin(); it != s.end(); ++it) {
                long long current = *it;
                if (current > 1e18) break;
                for (int factor : {2, 3, 5}) {
                    long long next = current * factor;
                    if (next <= 1e18 && s.find(next) == s.end()) {
                        s.insert(next);
                        hammingNumber.push_back(next);
                    }
                }
            }
            sort(hammingNumber.begin(), hammingNumber.end());
        }
        ```
- Source code: [HAMMING.cpp](https://github.com/UITxWoodyNguyen/Courses-Self-Learning/blob/main/ICPC-Training/MarisaOJ/searching-p1/problem82.cpp)

## Số nguyên liên tiếp
- Tóm tắt đề: Cho dãy $A$ gồm $N$ số nguyên. Tìm số lượng phần tử cần thay đổi ít nhất để $A$ gồm các số nguyên liên tiếp.
- Giới hạn: $1 \le N \le 10^5$, $1 \le A[i] \le 10^9$
- Solution:

    - Nhận xét:

        - Một dãy số nguyên liên tiếp sẽ không có 2 phần tử nào trùng nhau.
        - Với mỗi số $x$ bất kì, để tạo một dãy các số nguyên liên tiếp độ dài $n$ thì số lớn nhất thuộc dãy là $x + n - 1$.
    - Từ nhận xét, ta thực hiện `sort()` lại dãy $A$ và xoá các phần tử trùng lặp.
    - Với mỗi $A[i]$, từ nhận xét trên, ta tính được giá trị lớn nhất cần phải giữ là $maxVal = A[i] + N - 1$. Thực hiện binary search để tìm index nhỏ nhất sao cho $A[index] > maxVal$
    - Từ đó ta tính được số lượng phần tử cần giữ lại là $keep[i] = index - i + 1$.
    - Đáp án của bài toán là $N - max(keep[1], keep[2], ..., keep[n])$
- Source code: [CONTNUM.cpp](https://github.com/UITxWoodyNguyen/Courses-Self-Learning/blob/main/ICPC-Training/MarisaOJ/searching-p1/problem197.cpp)

## [Khoảng cách Gnimmah](https://marisaoj.com/problem/83)
- Tóm tắt đề: Cho 2 xâu $a$ và $b$. Tính khoảng cách Grimnah của các xâu con độ dài $|b|$ của $a$.
    > Khoảng cách Grimnah của 2 xâu $s$ và $t$ là số vị trí mà tại đó $s[i] = t[i]$
- Giới hạn: Độ dài xâu không vượt quá $10^5$
- Solution:

    - Gọi $pfs[i][c] : (0 < i < |a|, 0 \le c < 26)$ là số lần xuất hiện của kí tự $c$ trong $a[0...i-1]$
    - Với mỗi $b[i]$, ta tính được số lượng substring chứa $b[i]$ trong $a$ là $pfs[i + cntSubtring][b[i]] - pfs[i][b[i]]$ với $cntSubstring = |a| - |b| + 1$ là số substring độ dài $|b|$ của $a$.
- Source code: [GRIMAH.cpp](https://github.com/UITxWoodyNguyen/Courses-Self-Learning/blob/main/ICPC-Training/MarisaOJ/searching-p1/problem83.cpp)

## [Đoạn con](https://marisaoj.com/problem/637)
- Tóm tắt đề: Cho dãy $A$ gồm $N$ số nguyên và số $S$. Tìm cặp $[l,r]$ sao cho $r - l + 1$ đạt max và $A[l] + A[l+1] + ... + A[r] \le S$
- Giới hạn: $1 \le N \le 2 \cdot 10^5$, $0 \le |a|, |S| \le 10^9$
- Solution:

    - Gọi $pfs[i] = a[1] + a[2] + ... + a[i]$
    - Từ đề bài ta thực hiện biến đổi $pfs[r] - pfs[l-1] \le S \Rightarrow pfs[l-1] \ge pfs[r] - S$
    - Nhận xét: với mọi $k$ sao cho $pfs[k]$ thoả mãn điều kiện trên, nếu $pfs[k+1] < pfs[k]$, $pfs[k+1]$ sẽ không thoả điều kiện, do đó ta có thể bỏ qua không cần xét tới những giá trị tương tự trường hợp này
    - Từ nhận xét trên, tạo một danh sách các $pfs[i]$ với điều kiện $i < j$ và $pfs[i] < pfs[j]$, tức duy trì các giá trị $pfs[i]$ tăng dần. Dùng `struct` để lưu lại vị trí gốc của các $pfs[i]$
    - Thực hiện binary search trên list giá trị này để tìm index nhỏ nhất sao cho $pfs[index] \ge pfs[r] - S$. Truy xuất lại vị trí gốc để tính được độ dài subsequences và lấy max.
- Source code: [SUBSEQ.cpp](https://github.com/UITxWoodyNguyen/Courses-Self-Learning/blob/main/ICPC-Training/MarisaOJ/searching-p1/problem637.cpp)