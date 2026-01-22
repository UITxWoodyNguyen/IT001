#include "Person.cpp"
using namespace std;

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