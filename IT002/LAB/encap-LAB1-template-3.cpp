#include <iostream>
using namespace std;

class Employee {
    private:    
        int id;
        string firstName;
        string lastName;
        int salary;

    public:
        Employee (int _id, string _firstName, string _lastName, int _salary) {
            this->id = _id;
            this->firstName = _firstName;
            this->lastName = _lastName;
            this->salary = _salary;
        }

        void setId (int _id) { this->id = _id; }
        int getId() { return id; }
        void setFirstName (string _firstName) { this->firstName = _firstName; }
        string getFirstName() { return firstName; }
        void setLastName (string _lastName) { this->lastName = _lastName; }
        string getLastName() { return lastName; }
        void setSalary (int _salary) { this->salary = _salary; }
        int getSalary() { return salary; }
        string getFullName() { return firstName + " " + lastName; }
};

int main() {
    Employee e(1, "Kien", "Hoang", 1000);
	cout << "Id: " << e.getId() << endl;
	cout << "Name: " << e.getFullName() << endl;
	cout << "Salary: " << e.getSalary() << endl;
	return 0;
}