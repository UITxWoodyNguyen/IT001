#include "Person.cpp"
using namespace std;

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