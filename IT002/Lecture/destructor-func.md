# Constructor Function and Destructor Function (Hàm khởi tạo và Hàm huỷ)

## Constructor Function (Hàm khởi tạo) - có tham số
- Xét đoạn code sau:
    ```c++
    #include <iostream>

    using namespace std;

    class Customer {
    public:
        string name;
        Customer(string name) {
            this->name = name;
        }
    };

    int main() {
        Customer s;
        cout << "Welcome to Codelearn.io!";
        return 0;
    }
    ```

    - Trong đoạn code trên, class `Customer` đã được khai báo constructor (`Customer(string name) {}`) và đây là constructor có tham số nên trong hàm `main()` bạn không thể khởi tạo được đối tượng thuộc lớp `Customer` (do trong hàm main() bạn gọi tới constructor không tham số nhưng trong lớp `Customer` lại không có constructor này).
    - Do đó chương trình sẽ không chạy được.

- Nếu ta thực hiện gọi hàm constructor không tham số trong class `Customer`, khi đó code mới hoạt động. Hoặc thực hiện gọi tham số khi khai báo trong main
    ```c++
    // Case 1
    ...
        public:
            Customer() {}
    ...

    // Case 2
    int main() {
        Customer s("myName");
        ....
    }
    ```

## Destructor Function (Hàm huỷ) 
- Hàm huỷ được sử dụng để đơn giản hoá việc xoá data. Giả sử xét đoạn code sau:
    ```c++
    #include<iostream>
    using namespace std;

    class Array {
    public:
        int* arr;
        int n;
    };

    void someFunc1() {
        Array a;
        a.n = 3;
        a.arr = new int[a.n];
        // Some code
        delete[] a.arr;
    }

    void someFunc2() {
        Array a;
        a.n = 3;
        a.arr = new int[a.n];
        // Some code
        delete[] a.arr;
    }

    int main() {
        someFunc1();
        someFunc2();
        return 0;
    }
    ```

    - Ta nhận thấy mỗi lần sử dụng class `Array`, đoạn code `delete[] a.arr` sẽ lặp lại một lần.
- Ta có thể thay thế đoạn code này bằng **Destructor Function** trong class `Array`:
    ```c++
    class Array:
        public:
            int* a;
            int n;

            ~Array() {
                cout << "Delete Array" << endl;
                delete[] arr;
            }
    ```

    - Khi đó, toán tử delete sẽ được gọi tự động khi kết thúc chương tình.
