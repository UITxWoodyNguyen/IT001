# OOP's Nature

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

## Inheritance (Tính kế thừa)
- **Tính kế thừa** là khả năng tạo một `class` mới dựa trên `class` hiện có, với các thuộc tính (attributes) và phương thức (method) hiện có. 
- Usage: Tính kế thừa hoạt động khi sử dụng cho 2 hay nhiều đối tượng có đặc điểm chung.
- Syntax:
    ```c++
    class BaseClass {
        access_modifer; // (private/public/protected)
            <data_type> <var_name>;
    };

    class SubClass: public BaseClass {
        access_modifer;
            <data_type> <var_name>;
    }
    ```

- Ví dụ:

    - Có 2 class `student` và `teacher` như sau:
        ```c++
        class student {
            public:
                string name;
                int age;
                string address;
                double gpa;
                string getName();
                int getAge();
                string getAddress();
                double getGPA();
                string setName (string new_name);
                int setAge (int new_age);
                string setAddress (string new_add);
                double setGPA (double new_gpa);
                void display();
        };
        ```

        ```c++
        class teacher {
            public:
                string name;
                int age;
                string address;
                int salary;
                string getName();
                int getAge();
                string getAddress();
                int getSalary();
                string setName (string new_name);
                int setAge (int new_age);
                string setAddress (string new_add);
                int setSalary (int new_salary);
                void display();
        };
        ```

    - Nhận xét: 2 class có khá nhiều attributes và method chung. Do đó ta có thể tạo một class mới `person` lưu những điểm chung của 2 class trên.
    - Khi đó, 2 class `student` và `teacher` sẽ kế thừa class `person` và 2 class này sẽ có những attributes và method của class `person`.
    - Nói cách khác, lúc này `person` là **base class** và `teacher`, `student` là **sub class/devire class**.
    - Source code:
        ```c++
        class Person {
            public:
                string name;
                int age;
                string address;

                string getName();
                int getAge();
                string getAddress();
                string setName (string new_name);
                int setAge (int new_age);
                string setAddress (string new_add);
                void display();
        };

        class student: public Person {
            public:
                double GPA;
                double getGPA();
                double setGPA (double new_gpa);
        };

        class teacher: public Person {
            public:
                int salary;
                int getSalary();
                int setSalary (int new_salary);
        };
        ```

## Polymorphism (Tính đa hình)
- Tính đa hình thể hiện khi một phương thức/đối tượng có nhiều hơn một hình thái/vai trò.
- Khi đó, một thao tác/thuộc tính có thể được định nghĩa tại nhiều class và có những cài đặt khác nhau cho mỗi class.

### Đa hình với nạp chồng phương thức
- Ví dụ: Ta có class `Calculator` với các phương thức là cộng 2 số nguyên, 3 số nguyên và 2 số thực. Có thể thấy, biểu hiện của tính đa hình thể hiện qua việc cả 3 thao tác đều là phương thức cộng nhưng có nhiều hình thái khác nhau.

    ```c++
    #include <iostream>
    using namespace std;

    class Calc {
        public:
            int add (int a, int b) {
                return a + b;
            }

            int add (int a, int b, int c) {
                return a + b + c;
            }

            double add (double a, double b) {
                return a + b;
            }
    };

    int main () {
        Calc calculator;

        cout << calculator.add(2, 5) << endl; // sum of 2 integers
        cout << calculator.add(2, 3, 4) << endl; // sum of 3 integers
        cout << calculator.add(1.2, 3.4) << endl; // sum of 2 doubles

        return 0;
    }
    ```

### Đa hình với ghi đè phương thức 
- Biểu hiện: Các class khác nhau sở hữu một hoặc nhiều phương thức giống nhau.
- Ví dụ: Xét phương thức `salary` trong 2 class sau
    ```c++
    #include <iostream>
    using namespace std;

    class Employee {
        private:
            string name;
            int salary;
        
        public:
            Employee(string _name, int _salary) {
                this->name = _name;
                this->salary = _salary;
            }

            string getName() { return name; }
            int getSalary() { return salary; }
            string setName (string _name) { this->name = _name; }
            int getSalary (int _salary) { this->salary = _salary; }

            void setInfo(string _name, int _salary) {
                this->name = _name;
                this->salary = _salary;
            }
    };

    class Manager : public Employee {
        private:
            int bonus;
        
        public:
            Manager(string _name, int _salary, int _bonus) : Employee(_name, _salary) {
                this->bonus = _bonus;
            }

            int getBonus() { return bonus; }
            void setBonus(int _bonus) { this->bonus = _bonus; }
            int getSalary() { return Employee::getSalary() + bonus; } // Overriding getSalary method
    };

    int main () {
        Employee emp("Alice", 50000);
        Manager mgr("Bob", 70000, 15000);

        cout << "Employee: " << emp.getName() << ", Salary: " << emp.getSalary() << endl;
        cout << "Manager: " << mgr.getName() << ", Salary: " << mgr.getSalary() << endl;

        return 0;
    }
    ```

    - Nhận xét: với cùng một phương thức `getSalary()` nhưng lại được định nghĩa theo 2 cách khác nhau trong 2 class.

### Đa hình thông qua các đối tượng đa hình
- Biểu hiện: Biến thuộc BaseClass có thể tham chiếu tới đối tượng của các SubClass, do đó biến này có thể có nhiều hình thái.
- Ví dụ: Ta có sơ đồ như sau
    ```
    Animal
    └── makeSound()
        ├── Dog   → bow wow
        ├── Cat   → meow meow
        └── Duck  → quack quack
    ```

    - Ở đây, phương thức `makeSound()` là phương thức chung cho tất cả các `Animal`, và mỗi SubClass của `Animal` sẽ có một đặc tính riêng đối với phương thức này.
    - Source code cụ thể:
        ```c++
        #include <iostream>
        using namespace std;

        class Animal {
            public:
                virtual void makeSound() {
                    cout << "Random Sound" << endl;
                }
        };

        class Dog : public Animal {
            public: 
                void makeSound() {
                    cout << "Woof" << endl;
                }
        };

        class Cat : public Animal {
            public:
                void makeSound() {
                    cout << "Meow" << endl;
                }
        };

        class Duck : public Animal {
            public:
                void makeSound() {
                    cout << "Quack" << endl;
                }
        };

        int main () {
            Animal* animal[] = {
                new Dog(),
                new Cat(),
                new Duck()
            };

            for(Animal* id : animal) id->makeSound(); // Polymorphic call
            return 0;
        }
        ```
## Abstraction (Tính trừu tượng)
- Trừu tượng hóa là cách nhìn khái quát hóa về một tập các đối tượng có chung các đặc điểm được quan tâm (bỏ qua những chi tiết không cần thiết). Nó cho phép ta giao tiếp với các thành phần của đối tượng mà không cần phải biết về cách mà các thành phần này được xây dựng. Trừu tượng hóa cũng có thể hiểu là cách chuyển một đối tượng trên thực tế thành các thành phần của OOP.