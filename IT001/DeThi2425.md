# ĐỀ THI NHẬP MÔN LẬP TRÌNH UIT 2024 - 2025

###### Nguồn: https://drive.google.com/file/d/1AiY1Pzsih33KwkD6AVpKz538bwQZi-Io/view?usp=drive_link

### **Câu 1** (0.5 điểm)
```c++
#include <iostream>
using namespace std;
int main(){
    int a = 15%6;
    int b = (a++) + 2;
    int c = (a>b ? a-b : b-a);
    int d = 2 + (c >= 3);
    cout<<a<<b<<c<<d;
    return 0;
}
```
- Sau khi thực hiện xong chương trình, kết quả in ra màn hình là: 

### **Câu 2** (0.5 điểm)
```c++
#include <iostream>
using namespace std;
int main() {
    int x = 1, y = 0;
    if (!y || (x++))
        cout << x - y;
    else
        cout << y - x;
    return 0;
}
```
- Sau khi thực hiện xong chương trình, kết quả in ra màn hình là: 

### **Câu 3** (0.5 điểm)
```c++
#include <iostream>
using namespace std;
int main () {
    int x = 13, y = 4;
    switch(x % y) {
        case 0: y--;
        case 1: x -= y;
        case 2: y /= 2;
        case 3: x %= 3;
    }
    cout << y << x;
    return 0;
}
```
- Sau khi thực hiện xong chương trình, kết quả in ra màn hình là: 

### **Câu 4** (0.5 điểm)
- Cho lưu đồ như sau:
```
        (Begin)
           |
           v
    +--------------+
    |   N = 42367  |
    |   S = 0      |
    +--------------+
           |
           v
  /----------------\          False      +----------+
 /      N > 0       \------------------->|  Xuất S  |
 \    (Vòng lặp)    /                    +----------+
  \----------------/                          |
           | True                             v
           v                                (End)
  /----------------\
 /  N % 10 % 2 == 1 \         True       +--------------+
 \    (Số lẻ?)      /------------------->|  S += N % 10 |
  \----------------/                     +--------------+
           |                                     |
           | False                               |
           v                                     |
    +--------------+                             |
    |   N = N / 10 |<----------------------------+
    +--------------+
           |
           |
           +---------- ( Quay lại kiểm tra N > 0 )
```
- Sau khi thực hiện xong chương trình, kết quả in ra màn hình là: 

### **Câu 5** (0.5 điểm)
```c++
#include <iostream>
using namespace std;
int main () {
    int S=0, i=5;
    while (i > 0 && S < 10)
    {
        S += i;
        i++;
    }
    cout << i << S;
    return 0;
}
```
- Sau khi thực hiện xong chương trình, kết quả in ra màn hình là: 

### **Câu 6** (0.5 điểm)
```c++
#include <iostream>
using namespace std;
int main()
{
    int n=3085, t=0;
    do
    {
        n = n/10;
        if(n%10%2) continue;
        t += n%10;
    } while(n);
    cout << t;
    return 0;
}
```
- Sau khi thực hiện xong chương trình, kết quả in ra màn hình là: 

### **Câu 7** (0.5 điểm)
```c++
#include <iostream>
using namespace std;
void fun(int &a, int b)
{
    a = --b;
    b %= 2;
}

int main()
{
    int a=5, b=10;
    fun(b,a);
    cout<<a<<b;
    return 0;
}
```
- Sau khi thực hiện xong chương trình, kết quả in ra màn hình là: 

### **Câu 8** (0.5 điểm)
```c++
#include <iostream>
using namespace std;
int fun(int n)
{
    if (n == 0) return 0;
    return ((n % 10 % 7) ? 1 : n % 10) + fun(n / 10);
}

int main()
{
    cout << fun(731);
    return 0;
}
```
- Sau khi thực hiện xong chương trình, kết quả in ra màn hình là: 

### **Câu 9** (0.5 điểm)
```c++
#include <iostream>
using namespace std;

void fun(int a[], int &n, int k) {
    for (int i = k; i < n - 1; i++)
        a[i] = a[i + 1];
    n--;
}

int out(int a[], int n) {
    int S = 0;
    for (int i = 0; i < n; i++)
        S += a[i];
    return S;
}

int main() {
    int a[5] = {1, 2, 7, 0, 3};
    int n = 5;
    fun(a, n, 3);
    cout << out(a, n);
    return 0;
}
```
- Sau khi thực hiện xong chương trình, kết quả in ra màn hình là: 

### **Câu 10** (0.5 điểm)
```c++
#include <iostream>
using namespace std;

int fun(int a[][3], int n) {
    int t = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (a[i][j])
                t++;
    return t;
}

int main() {
    int a[3][3] = {{1, 0, 3},
                   {0, 3, 1},
                   {3, 2, 0}};
    cout << fun(a, 3);
    return 0;
}
```
- Sau khi thực hiện xong chương trình, kết quả in ra màn hình là: 

### **Câu 11** (0.5 điểm)
```c++
#include <iostream>
#include <string.h>
using namespace std;
#define MAX 300

int main()
{
    char S[MAX] = "2025UitCs";
    strrev(S);
    puts(strstr(S, "20"));
    return 0;
}
```
- Sau khi thực hiện xong chương trình, kết quả in ra màn hình là: 

### **Câu 12** (0.5 điểm)
```c++
#include <iostream>
using namespace std;
int main()
{
    int n = 10;
    int* p1 = &n;
    int* p2 = p1;
    p1 = new int (50);
    n--;
    cout << (*p1) << (*p2);
    return 0;
}
```
- Sau khi thực hiện xong chương trình, kết quả in ra màn hình là: 

### **Câu 13** (0.5 điểm)
```c++
#include <iostream>
using namespace std;
void fun(int* a, int* b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}
int main()
{
    int* p1 = new int(5);
    int* p2 = new int(7);
    fun(p1, p2);
    cout << *p1 << " " << *p2;
    return 0;
}
```
- Sau khi thực hiện xong chương trình, kết quả in ra màn hình là: 

### **Câu 14** (0.5 điểm)
```c++
#include <iostream>
using namespace std;
struct Account
{
    int id;
    char type;
};
int main()
{
    Account Arr[3] = {{10, 'A'}, {20, 'B'}, {30, 'C'}};
    Account* x = Arr;
    Account* y = x + 2;
    cout << x - y;
    cout << (y->id) - (x->id);
    return 0;
}
```
- Sau khi thực hiện xong chương trình, kết quả in ra màn hình là: 

### **Câu 15** (2 điểm)
**Mô tả bài toán:**
Viết chương trình quản lý danh sách các tài khoản User gồm ID (số nguyên), Pass (Chuỗi) và thực hiện các yêu cầu sau:

1. Khai báo kiểu dữ liệu cấu trúc User
2. Nhập thông tin cho N User
3. Hãy cho biết Pass nào KHÔNG hợp lệ trong danh sách. Biết rằng Pass chỉ hợp lệ khi thỏa tất cả các điều kiện sau:
* Pass phải có trên 5 ký tự.
* Pass phải có chữ cái, chữ số và ký tự đặc biệt (Ký tự đặc biệt là các ký tự ! @ # $ % ^ & *)



Chương trình cho sẵn hàm main như bên dưới. Ý nghĩa các hàm trong main như sau:

* Hàm `Input` dùng để nhập N user và lưu trữ trong Arr
* Hàm `Find` dùng để tìm và xuất ra màn hình các Pass không hợp lệ trong Arr. Nếu tất cả các Pass đều hợp lệ thì xuất ra `NoFound`

```cpp
int main()
{
    User Arr[MAX];
    int N;
    Input(Arr, N);
    Find(Arr, N);
    return 0;
}

```

**Input:**

* Nhập số lượng N User trong Arr
* N dòng tiếp theo, mỗi dòng sẽ là thông tin của 1 User gồm ID và Pass

**Output:**

* Xuất ra các Pass không hợp lệ trong Arr.
* Nếu tất cả các Pass trong Arr đều hợp lệ thì xuất ra `NoFound`.

---

**Ví dụ:**

| Input | Output |
| --- | --- |
| 3 | abc!@#$ |
| 100 abc!@#$ | xyz@1 |
| 101 xyz@1 | 123%^&^ |
| 102 123%^&^ |  |
| **2** | **NoFound** |
| 100 abc*88 |  |
| 101 xyz%123 |  |

### **Câu 16** (1 điểm)
**Mô tả bài toán:**
Viết chương trình cho phép người dùng liên tục nhập vào các số nguyên. Việc nhập chỉ DỪNG khi nhập số 0 (không tính số 0 vào dãy số nguyên) và xuất ra màn hình số nguyên có giá trị **lớn thứ hai** và **nhỏ thứ 2** trong dãy số nguyên đã nhập.

**Ví dụ:**

| Input | Output |
| --- | --- |
| 50920 | 50920 |
| 25923 | 50920 |
| 159223 |  |
| 0 |  |
| 12 | 9220 |
| 9220 | 653 |
| 120000 |  |
| 653 |  |
| 0 |  |

**Lưu ý:** không sử dụng các cấu trúc mảng, tập hợp để giải quyết bài toán, cũng như không được sử dụng các từ khóa này trong bài làm: `vector`, `set`, `map`, `[ ]`, `INT_MAX`, `INT_MIN`.
