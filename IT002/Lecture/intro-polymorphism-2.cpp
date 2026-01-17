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