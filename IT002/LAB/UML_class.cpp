#include <iostream>
using namespace std;

class Student {
    private:
        string name;
        int age;
        string gender;
        double gpa;

    public:
        Student(string _name, int _age, string _gender, double _gpa) {
            this->name = _name;
            this->age = _age;
            this->gender = _gender;
            this->gpa = _gpa;
        }

        void display() {
            cout << "Name: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "Gender: " << gender << endl;
            cout << "GPA: " << gpa << endl; 
        }
};

int main () {
    Student s("Quang", 24, "Male", 7.7);
    s.display();
    return 0;
}