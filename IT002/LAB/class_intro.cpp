// No Template

#include <iostream>
#include <string>
using namespace std;

class Student {
    public:
        string name;
        int age;

        Student (string _name, int _age) {
            this->name = _name;
            this->age = _age;
        }

        void getInformation() {
            cin >> name >> age;
        }

        void display() {
            cout << "Name: " << name << endl;
            cout << "Age: " << age << endl;
        }
};

int main () {
    Student stu1("Default", 0);
    stu1.getInformation();
    stu1.display();
    return 0;
}