#include <iostream>
using namespace std;

class Student {
    private:    
        int id;
        string name;
        int age;
        string address;
        int score;

    public:
        Student() {}
        Student (int _id, string _name, int _age, string _address, int _score) {
            this->id = _id;
            this->name = _name;
            this->age = _age;
            this->address = _address;
            this->score = _score;
        }

        void setId (int _id) { this->id = _id; }
        int getId() { return id; }
        void setName (string _name) { this->name = _name; }
        string getName() { return name; }
        void setAge (int _age) { this->age = _age; }
        int getAge() { return age; }
        void setAddress (string _address) { this->address = _address; }
        string getAddress() { return address; }
        void setScore(int _score) {
            if (_score < 0) _score = 0;
            else if (_score > 10) _score = 10;

            this->score = _score;
        }
        int getScore() { return score; }
};

int main () {
    Student s(1001, "Trung", 24, "Ha Noi", 5);
	cout << s.getId() << endl;;
	cout << s.getName() << endl;;
	cout << s.getAge() << endl;;
	cout << s.getAddress() << endl;;
	cout << s.getScore() << endl;;
	s.setScore(-7);
	cout << s.getScore() << endl;;
	s.setScore(15);
	cout << s.getScore() << endl;;
	return 0;
}   