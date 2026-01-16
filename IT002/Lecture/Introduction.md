# OOP Introduction

## Encapsulation (Tính đóng gói)
- **Đóng gói** là cách tổ chức các thành viên data (thuộc tính) và các thành viên functions (phương thức) bằng cách đóng gói chúng trong một lớp duy nhất (`class`)
- Ví dụ:
    ```c++
    /* Template mẫu cho một lớp (class) */
    class Example {
        // attributes (thuộc tính)
        // methods (phương thức)
    };

    /* Ví dụ cụ thể với đối tượng là một hình chữ nhật */
    class Rectangle {
        public: // attributes --> thuộc tính của HCN
            int length; // chiều dài
            int width; // chiều rộng
        
        int getArea() { // method --> tính diện tích
            return length * width; 
        }
    };
    ```

- **Data Hiding** (che giấu dữ liệu): đây là thao tác sử dụng các từ khoá chỉ định quyền truy cập được hỗ trợ trong `C++` để xác định phạm vi truy cập của các thành phần trong `class`

    - `public`: Các members thuộc lớp `public` có thể được truy cập ở bất kì đâu trong chương trình (giống với biến/hàm toàn cục).
    - `private`: Các members lớp private chỉ có thể truy cập ở bên trong `class` (giống với biến/hàm cục bộ)
- Data Hiding được thực hiện qua việc khai báo các thuộc tính của lớp `private`.
- Ví dụ:
    ```c++
    #include <iostream>
    using namespace std;

    class getData {
        private:
            int num; // num is a privare member variable, which cannot be accessed in the main

        public: // all functions declared in public class can be accessed in the main
            void set(int n) { // same as cin function
                num = n;
            }

            int get() { // same as cout function
                return num;
            }
        
    };

    int main () {
        getData u;
        u.set(36);
        cout << u.get() << endl;
        return 0;
    }
    ```

    - Về ví dụ này:
    
        - Biến `num` chỉ có giá trị sử dụng bên trong class `getData` (tức bất cứ method nào nằm trong class `getData` đều có thể sử dụng biến này).
        - Hàm `set(n)` và `get()` có công dụng như `cin - cout`, và có thể sử dụng ở bất cứ vị trí nào trong chương trình vì đặt dưới `public` class. 

- **`protected`**: là một access specifer trong `C++` dùng để xác định đối tượng có thể truy cập các `members` của 1 `class`. Cụ thể, các `members` của `protected` chỉ có thể được truy cập trong `class` có khai báo chúng hoặc các `subclasses` (lớp kế thừa).
- Ví dụ:
    ```c++
    #include <iostream>
    using namespace std;

    class Base {
        protected: 
            int proctedtedVar;

            void protectedMethod() {
                cout << "This method is protected" << endl;
            }
    };

    class Derived: public Base { // This is a subclass of Base
        public:
            void getProtectedInfo() { // Function to access protected members of Base
                proctedtedVar = 10; // Accessing protected member from base class
                cout << proctedtedVar << endl;
                protectedMethod(); // Calling protected method from base class
            }
    };

    int main () {
        Derived object;
        object.getProtectedInfo();
        return 0;
    }
    ```

    - Về ví dụ này:
        
        - Biến `protectedVar` và hàm `protectedMethod()` là 2 members được protect trong class `Base`. Do đó các members này sẽ không sử dụng được trong `main`.
        - class `Derived` là `subclass` của `Base`, do đó các members được protect trong class `Base` có thể được sử dụng trong subclass `Derived`. 
