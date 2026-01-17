#include <iostream>
using namespace std;

class Student {
    private: 
        string name;
        char gender;

    public:
        Student() {
            name = "Unknown";
            gender = 'u';
        }

        Student (string _name) {
            this->name = _name;
            gender = 'u';
        }

        Student (char _gender) {
            this->gender = _gender;
            name = "Unknown";
        }

        Student (string _name, char _gender) {
            this->name = _name;
            this->gender = _gender;
        }

        void display() {
            cout << "Name: " << name << endl;
            cout << "Gender: ";
            switch (gender) {
                case 'm': cout << "Male" << endl; break;
                case 'f': cout << "Female" << endl; break;
                default: cout << "Unknown" << endl; break;
            }
        }
};

int main () {
    Student s1;
	s1.display();
	Student s2("Quang");
	s2.display();
	Student s3('m');
	s3.display();
	Student s4("Thu", 'f');
	s4.display();
	return 0;
}