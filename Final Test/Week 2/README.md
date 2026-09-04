# ĐỀ THI THỰC HÀNH CUỐI KỲ UIT - LỚP IT001.Q121 - CA 2

**Học kỳ I - Năm học 2025-2026** 

---

ĐỀ 2 

**Các thông tin dùng chung cho các câu trong đề bài:** 

```c
typedef uint8 unsigned char;     [cite_start]// kiểu số nguyên không dấu 1 byte [cite: 6]
typedef int16 short;             [cite_start]// kiểu số nguyên có dấu 2 byte [cite: 7]
typedef int32 long;              [cite_start]// kiểu số nguyên có dấu 4 byte [cite: 8]
typedef uint16 unsigned short;    [cite_start]// kiểu số nguyên không dấu 2 byte [cite: 9]
typedef uint32 unsigned long;     [cite_start]// kiểu số nguyên không dấu 4 byte [cite: 10]
typedef uint64 long long;        [cite_start]// kiểu số nguyên không dấu 8 byte [cite: 10, 11]

typedef struct {
    uint8 day;                   [cite_start]// [cite: 13]
    uint8 month;                 [cite_start]// [cite: 14]
    int16 year;                  [cite_start]// [cite: 15]
} DATE;                          [cite_start]// [cite: 12, 16]

typedef struct {
    char name [15];              [cite_start]// tên của chân IC ("VCC" / "GND" / "101" /... [cite: 18]
    char type [10];              [cite_start]// Input/Output / Power [cite: 19]
    int number;                  [cite_start]// số thứ tự chân [cite: 20]
} PIN;                           [cite_start]// mô tả về chân của IC [cite: 17, 21]

```

---

**Câu 1:** Bổ sung các chỗ `/* ??? [cite_start]*/` bởi các lệnh phù hợp theo yêu cầu (không được thêm/xóa/sửa các chỗ khác) để các hàm bên dưới thực hiện đúng như mô tả của comment đầu hàm. 

```c
[cite_start]// Hàm kiểm tra số N có phải số Nguyên tố: [cite: 24]
bool is_prime(int n) {
    if (n <= 1) return false;      [cite_start]// Số <= 1 không phải số nguyên tố [cite: 26]
    if (n == 2 || n == 3) return true; [cite_start]// 2 và 3 là số nguyên tố [cite: 27]
    if (n % 2 == 0 || n % 3 == 0) return false; [cite_start]// Loại bỏ các số chia hết cho 2 & 3 [cite: 28, 29]
    
    int limit = sqrt(n);           [cite_start]// [cite: 30]
    // Bắt đầu kiểm tra từ 5 và bỏ qua các số chẵn
    [cite_start]for (int i = 5; i <= limit; i += 2) { // [cite: 33]
        if (/*???*/) return /*???*/;      [cite_start]// [cite: 34]
    }
    return true; [cite_start]// [cite: 35]
}

[cite_start]// Hàm Đếm Số lượng Số Nguyên tố trong 1 mảng [cite: 36]
[cite_start]int count_prime(int a[], int n) { // [cite: 37]
    int count = 0;               [cite_start]// [cite: 38]
    /* for (int i = 0; i < n; i++)
        if (is_prime(a[i])) count ++; [cite_start]// [cite: 39, 40]
    */
    [cite_start]// viết lại lệnh If và vòng lặp For trên bằng 2 cấu trúc While [cite: 41]
    [cite_start]/*???*/                      // [cite: 42]
    return count;                [cite_start]// [cite: 43]
}

```

**Câu 2:** Viết hàm `int Cau_2 (int N, int m, int huong)` làm tròn số nguyên  đến  ( là số nguyên thuộc ), với tham số hướng nếu không được truyền lúc gọi hàm thì mặc định là 0 – là làm tròn đúng, còn truyền số âm thì làm tròn xuống, truyền số dương làm tròn lên. 

* **Lưu ý:** KHÔNG ĐƯỢC DÙNG BẤT CỨ HÀM CÓ SẴN NÀO. 



**Câu 3:** Viết hàm trả về số phần tử của dãy Collatz bắt đầu từ  và kết thúc tại 1 (bao gồm cả  và 1) và có cho biết thời gian chạy của hàm là bao nhiêu micro giây – hàm có prototype: `int collatz_length(long n, long & t);` ( là thời gian chạy). 

* **Ghi chú:** Quy tắc sinh dãy Collatz: Bắt đầu từ số nguyên dương `N`: 

    * Nếu `N` lẻ: `n = 3n + 1`
    * Nếu `N` chẵn: `n = n / 2`
* Lặp lại cho đến khi `n = 1`. 
* *Ví dụ:* Với `n = 6` thì dãy là  `6 → 3 → 10 → 5 → 16 → 8 → 4 → 2 → 1`.

**Câu 4:** Viết 2 hàm đệ quy thực hiện: 

1. Đếm phần tử âm trong mảng. 


2. Tính phần tử thứ  của dãy Fibonaci (2 phần tử đầu là 1 và 1, các phần tử sau bằng tổng 2 phần tử trước đó). 



**Câu 5:** Viết hàm giải nén chuỗi ký tự theo phương pháp **Run-Length Encoding (RLE)**. 

* **Quy tắc:** Mỗi nhóm ký tự giống nhau được mã hóa thành 2 byte: `<ký_tự><số_lần_lặp>`. 


* *Ví dụ:* Input `HA2HA10`  Output `HAAHAAAAAAAAAA`. 



**Câu 6:** Viết hàm `Cau_6` chuyển struct `DATE` vào dãy 16 bit, các trường được bố trí như sau: 

* `day`: bit 0-4 
* `month`: bit 5-8 
* `year - 2000`: bit 9-16 

**Câu 7:** Viết hàm đọc mảng `DATE` từ file. Ngoài các tham số cơ bản, hàm có thêm tham số `type`: 

* `type = true` (hoặc mặc định): Đọc từ file nhị phân. 
* `type = false`: Đọc từ file văn bản, mỗi dòng là 1 ngày dạng `dd/mm/yy` (VD: `26/12/2025`). 



**Câu 8:** Viết hàm `uint32 decodeManchester (uint64 X)` để giải mã Manchester encoding: 

* Bit dữ liệu `0` được mã hóa thành cặp bit `01`. 
* Bit dữ liệu `1` được mã hóa thành cặp bit `10`. 
* Viết thêm hàm cùng tên để giải mã một mảng các phần tử 64-bit. 



**Câu 9:** Viết hàm sắp xếp lại mảng `DATE` (theo thứ tự: `year`  `month`  `day`). 

**Câu 10:** Viết hàm tạo 1 mảng nguyên từ mảng thực bằng cách: Lấy mỗi phần tử trừ đi giá trị trung bình của mảng  làm tròn đúng đến 0.01  nhân với 100 để ra giá trị nguyên tương ứng. 

---