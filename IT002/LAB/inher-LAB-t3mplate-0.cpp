#include<iostream>

using namespace std;

class Person {
    private:
        string name;
        int dob;
    public:
        Person(string name, int dob) {
            this->name = name;
            this->dob = dob;
        }
        
        string getName() { return name; }
        int getDob() { return dob; }
};

class Student : public Person {
	private:
        double gpa;
    
    public:
        Student(string _name, int _dob, double _gpa) : Person(_name, _dob) {
            this->gpa = _gpa;
        }
        double getGpa() { return gpa; }
};

int main() {
	Student s("Hai", 1999, 8.8);
	cout << "Name: " << s.getName() << endl;
	cout << "Date of birth: " << s.getDob() << endl;
	cout << "GPA: " << s.getGpa() << endl;
	return 0;
}
