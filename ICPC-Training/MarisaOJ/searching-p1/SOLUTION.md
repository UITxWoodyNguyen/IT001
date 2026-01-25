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
