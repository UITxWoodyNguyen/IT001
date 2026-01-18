/*
    Template here:
    #include<iostream>

    using namespace std;

    class Person {
    private:
        int id;
        string name;
        int age;
        string address;
        ...
    };

    int main() {
        ...
        cout << "Id: " << p.getId() << endl;
        cout << "Name: " << p.getName() << endl;
        cout << "Age: " << p.getAge() << endl;
        cout << "Address: " << p.getAddress() << endl;
        return 0;
    }
*/

#include<iostream>
using namespace std;

class Person {
    private:
        int id;
        string name;
        int age;
        string address;
    
    public:
        Person(int _id, string _name, int _age, string _address) {
            this->id = _id;
            this->name = _name;
            this->age = _age;
            this->address = _address;
        }

        int getId() { return id; }
        string getName() { return name; }
        int getAge() { return age; }
        string getAddress() { return address; }
};

int main() {
	Person p(1001, "Quynh", 24, "Ha Noi");
	cout << "Id: " << p.getId() << endl;
	cout << "Name: " << p.getName() << endl;
	cout << "Age: " << p.getAge() << endl;
	cout << "Address: " << p.getAddress() << endl;
	return 0;
}
