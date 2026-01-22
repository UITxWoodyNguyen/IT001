#include <iostream>
using namespace std;

class Person {
    private:
        string name;
        int age;
        string address;

    public:
        Person(string _name, int _age, string _address) {
            this->name = _name;
            this->age = _age;
            this->address = _address;
        }

        void setName (string _name) { this->name = _name; }
        string getName() { return name; }
        void setAge (int _age) { this->age = _age; }
        int getAge() { return age; }
        void setAddress (string _address) { this->address = _address; }
        string getAddress() { return address; }

        void display() {
            cout << "Name: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "Address: " << address << endl;
        }
};

class Student : public Person {
    private:    
        double gpa;

    public:
        Student(string _name, int _age, string _address, double _gpa) : Person(_name, _age, _address) {
            this->gpa = _gpa;
        }

        void setGpa(double _gpa) { this->gpa = _gpa; }
        double getGpa() { return gpa; }

        void display() {
            Person::display();
            cout << "GPA: " << gpa << endl;
        }
};

class Teacher : public Person {
    private:
        int salary;

    public:
        Teacher(string _name, int _age, string _address, int _salary) : Person(_name, _age, _address) {
            this->salary = _salary;
        }

        void setSalary(int _salary) { this->salary = _salary; }
        int getSalary() { return salary; }

        void display() {
            Person::display();
            cout << "Salary: " << salary << endl;
        }
};

int main () {
    Student s("Khanh", 23, "Ha Noi", 9.0);
	s.display();
	Teacher t("Tung", 34, "Ha Noi", 1700);
	t.display();
	return 0;
}   