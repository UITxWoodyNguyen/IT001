/*
    Template here:
        #include <iostream>

        using namespace std;

        class Student {
            ...
        };

        int main() {
            Student s1("Long", 24);
            Student s2("Kien", 29);
            s1.display();
            s2.display();
            return 0;
        }
*/

#include <iostream>
using namespace std;

class Student {
    public:
        string name;
        int age;

        Student(string _name, int _age) {
            this->name = _name;
            this->age = _age;
        }

        void display() {
            cout << "Name: " << name << endl;
            cout << "Age: " << age << endl;
        }
};

int main() {
    Student s1("Long", 24);
    Student s2("Kien", 29);
    s1.display();
    s2.display();
    return 0;
}