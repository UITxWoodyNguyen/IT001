# Introduction to Binary Search

## Information
- OJ: [MarisaOJ](https://marisaoj.com/)
- Tag: Binary Search

## Tìm kiếm nhị phân
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

