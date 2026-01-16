# ĐỀ THI THỰC HÀNH CUỐI KỲ UIT - LỚP IT001.Q121 - CA 1

**Học kỳ I - Năm học 2025-2026** 
---

## Các thông tin dùng chung cho các câu trong đề bài

```c
typedef int16 short; // kiểu số nguyên có dấu 2 byte
typedef int32 long;  // kiểu số nguyên có dấu 4 byte
typedef uint16 unsigned short; // kiểu số nguyên không dấu 2 byte
typedef uint32 unsigned long;  // kiểu số nguyên không dấu 4 byte
typedef uint64 long long;      // kiểu số nguyên không dấu 8 byte

typedef struct {
    int type; // 0/1: kiểu số nguyên không/có dấu 1B; 2/3: int16/uint16; 4/5: int32/uint32
    int mode; // giá trị xuất hiện nhiều nhất
    int avr;  // giá trị trung bình
    int dr;   // tỷ lệ % lệch chuẩn (0-100)
    int n;    // số phần tử
} FEATURE;

typedef struct {
    char name[15]; // tên của chân IC ("VCC" / "GND" / "I01" / ...)
    char type[10]; // Input / Output / Power
    int number;    // số thứ tự chân
} PIN; // mô tả về chân của IC

```

---

## Danh sách các câu hỏi

### Câu 1

Bổ sung các chỗ `/* ??? */` bởi các lệnh phù hợp theo yêu cầu (không được thêm/xóa/sửa các chỗ khác) để các hàm bên dưới thực hiện đúng như mô tả của comment đầu hàm.

```c
// Hàm kiểm tra số N có phải số Nguyên tố
bool is_prime(int n) {
    if (n <= 1) return false; // Số <= 1 không phải số nguyên tố
    if (n == 2 || n == 3) return true; // 2 và 3 là số nguyên tố
    if (n % 2 == 0 || n % 3 == 0) return false; // Loại bỏ các số chia hết cho 2 & 3

    int limit = sqrt(n);
    /* Bắt đầu kiểm tra từ 5 và bỏ qua các số chẵn
    for (int i = 5; i <= limit; i += 2)
        if (n % i == 0) return false;
    // vòng lặp For trên đã chạy đúng nhưng viết lại bằng cấu trúc Do..While
    */
    /* ??? */
    return true;
}

// Hàm Đếm Số lượng Số Nguyên tố trong 1 mảng
int count_prime(int a[], int n) {
    /* ??? */
    for (int i = 0; i < n; i++)
        if (is_prime(a[i])) count++;
    /* ??? */
}

```

### Câu 2

Viết hàm `double Cau_2(double F, int m, int huong)` làm tròn 1 số thực  đến  ( là số nguyên thuộc ), với tham số `huong` nếu không được truyền lúc gọi hàm thì mặc định là 0 – là làm tròn đúng, còn truyền số âm thì làm tròn xuống, truyền số dương làm tròn lên.
**Lưu ý:** không được dùng các hàm làm tròn có sẵn (`round`, `trunc`, `ceil`, `floor`,...).

### Câu 3

Quá trình số hóa tín hiệu âm thanh từ microphone vào máy tính có một bước rất quan trọng là Quantization (lượng tử hóa) chuyển giá trị điện áp liên tục (số thực) thành giá trị rời rạc, biểu diễn bằng số nguyên trong một phạm vi xác định bởi độ phân giải bit depth (với n bit thì miền điện áp sẽ chuyển thành  số nguyên).

Giả sử có 1 dãy các giá trị điện áp thu được (theo thời gian), biết các giá trị này là số thực thuộc đoạn  và cần lượng tử hóa thành số nguyên không dấu 16 bit theo cơ chế chia đều. Hãy viết hàm `void Cau_3(double inArr[], uint16 outArr[], int n)` thực hiện việc này (`uint16` là kiểu `unsigned short` – số nguyên không dấu 16bit).

### Câu 4

Viết hàm `FEATURE Cau_4(short Arr[], int n)` phân tích mảng nguyên để xác định và đưa vào struct `FEATURE` các thông tin: số phần tử của mảng, giá trị trung bình, giá trị lặp lại nhiều nhất, tỷ lệ lệch chuẩn (lệch hơn 25% so với trung bình).

### Câu 5

Viết hàm `Cau_5` chuyển struct `FEATURE` vào dãy 64 bit; trong đó các trường trong struct được bố trí trong các bit như sau:

* **type**: bit 0-2
* **dr**: bit 3-9
* **n**: bit 10-31
* **avr**: bit 32-63

### Câu 6

Viết hàm lưu mảng vào file; trong đó ngoài các tham số cơ bản hàm có thêm tham số `type` và khi truyền `type=true` hoặc không truyền lúc gọi hàm thì lưu vào file văn bản, `type=false` thì lưu vào file nhị phân.

### Câu 7

Viết hàm đệ quy tìm giá trị lớn nhất trong mảng và hàm tính tổng các phần tử mảng.

### Câu 8

**Manchester encoding** là một phương pháp mã hóa đường truyền trong đó mỗi bit dữ liệu được biểu diễn bằng hai bit mã hóa, nhằm đảm bảo luôn có chuyển mức trong mỗi chu kỳ bit; đây là kỹ thuật hữu dụng trong thiết kế vi mạch. Trong bài này, quy ước mã hóa được sử dụng như sau:

* Bit dữ liệu 0 được mã hóa thành cặp bit 01
* Bit dữ liệu 1 được mã hóa thành cặp bit 10
(ví dụ, dãy 8bit `10010011` sẽ mã hóa thành 16 bit `1001011001011010`, dãy N bit áp dụng tương tự).

Hãy viết hàm `uint32 encodeManchester(uint16 X)` mã hóa dãy 16bit lưu trong X và hàm cùng tên mã hóa 1 mảng mà mỗi phần tử là dãy 16bit.

### Câu 9

Viết hàm sắp xếp lại mảng các chân IC (mỗi phần tử có kiểu `PIN`) theo thứ tự chỉ số chân.

### Câu 10

**Run-Length Encoding (RLE)** là một phương pháp nén dữ liệu đơn giản, trong đó các phần tử giống nhau liên tiếp được biểu diễn bằng phần tử đó kèm theo số lần xuất hiện liên tiếp này. Hãy viết hàm nén chuỗi ký tự theo phương pháp RLE (**Quy tắc:** mỗi nhóm các ký tự giống nhau liên tiếp được mã hóa thành 2 byte `<ký tự><số_lần_lặp>`, ví dụ: `AAABBBCC` -> `A3B3C2`).

---