#include <iostream>
#include <string>
using namespace std;

// ===== Class Person =====
class Person {
public:
    string name;
    int age;
    string address;

    string getName();
    int getAge();
    string getAddress();

    string setName(string new_name);
    int setAge(int new_age);
    string setAddress(string new_add);

    void display();
};

// Implement methods of Person
string Person::getName() {
    return name;
}

int Person::getAge() {
    return age;
}

string Person::getAddress() {
    return address;
}

string Person::setName(string new_name) {
    name = new_name;
    return name;
}

int Person::setAge(int new_age) {
    age = new_age;
    return age;
}

string Person::setAddress(string new_add) {
    address = new_add;
    return address;
}

void Person::display() {
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Address: " << address << endl;
}

// ===== Class Student =====
class student : public Person {
public:
    double GPA;

    double getGPA();
    double setGPA(double new_gpa);
};

// Implement methods of student
double student::getGPA() {
    return GPA;
}

double student::setGPA(double new_gpa) {
    GPA = new_gpa;
    return GPA;
}

// ===== Class Teacher =====
class teacher : public Person {
public:
    int salary;

    int getSalary();
    int setSalary(int new_salary);
};

// Implement methods of teacher
int teacher::getSalary() {
    return salary;
}

int teacher::setSalary(int new_salary) {
    salary = new_salary;
    return salary;
}

// ===== Main function =====
int main() {
    student s;
    teacher t;

    // Set student info
    s.setName("Nguyen Van A");
    s.setAge(20);
    s.setAddress("Ho Chi Minh City");
    s.setGPA(3.75);

    cout << "=== Student Information ===" << endl;
    s.display();
    cout << "GPA: " << s.getGPA() << endl;

    cout << endl;

    // Set teacher info
    t.setName("Tran Thi B");
    t.setAge(40);
    t.setAddress("Ha Noi");
    t.setSalary(1500);

    cout << "=== Teacher Information ===" << endl;
    t.display();
    cout << "Salary: " << t.getSalary() << endl;

    return 0;
}
