#include<iostream>

using namespace std;

class Person {
private:
	string name;
	string gender;

public:
	Person(string name, string gender) {
		this->name = name;
		this->gender = gender;
	}

	string getName() {
		return name;
	}

	void setName(string name) {
		this->name = name;
	}

	string getGender() {
		return gender;
	}

	void setGender(string gender) {
		this->gender = gender;
	}

	void display() {
		cout << "Name: " << name << endl;
		cout << "Gender: " << gender << endl;
	}
};

class Student : Person {
	private:
        int salary;

    public:
        Student(string _name, string _gender, int _salary) : Person(_name, _gender) {
            this->salary = _salary;
        }

        void display() {
            Person::display();
            cout << "Salary: " << salary << endl;
        }
};

int main() {
	Student s("Trung", "Male", 1700);
	s.display();
	return 0;
}