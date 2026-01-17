# Static in OOP

## Biến static trong OOP
- Biến tĩnh sẽ được khai báo với từ khoá `static` và giá trị của biến sẽ được chia sẻ với tất cả các đối tượng trong chương trình. Khi đó biến `static` trong mọi đối tượng là biến dùng chung nên giá trị chỉ có một.
- Ví dụ: Xét 2 đoạn code sau:
    ```c++
    class Num {
        private:
            int n;

        public:
            int siz;
            Num (int _n) {
                this->n = _n;
            }
    };

    int main () {
        Num a(2);
        Num b(4);
        a.siz = 1;
        b.siz = 2;
        cout << a.siz << " " << b.siz;
    }
    ```

    ```
    // Output here:
    1 2
    ```

    ```c++
    class Num {
        private:
            int n;

        public:
            static int siz;
            Num (int _n) {
                this->n = _n;
            }
    };

    int main () {
        Num a(2);
        Num b(4);
        a.siz = 1;
        b.siz = 2;
        cout << a.siz << " " << b.siz;
    }
    ```

    ```
    // Output here:
    2 2
    ```

- Nhận xét:
    
    - Ở đoạn code đầu tiên, giá trị `siz` ở 2 đối tượng `a` và `b` là khác nhau do đây là thuộc tính riêng của từng đối tượng.
    - Ở đoạn code thứ hai, do `siz` lúc này là biến `static` nên đây là biến dùng chung và không mang đặc tính của bất kì đối tượng nào. Do đó giá trị chỉ có một.
- Biến `static` thường được dùng để lưu giá trị chung của các đối tượng hoặc dùng làm hằng số, và **KHÔNG** được xem là thuộc tính của 1 class.
- Cách truy xuất biến `static`:
    ```c++
    <class_name>::<variable_name>
    ```

## Hàm static trong OOP
- Cách sử dụng tương tự biên `static`