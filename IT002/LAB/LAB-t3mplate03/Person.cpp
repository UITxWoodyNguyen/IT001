#pragma once // prevent multiple inclusions
#include <iostream>
using namespace std;

class Person {
    private:
        string name;
        int age;
        string address;

    public:
        Person(string _name, int _age, string _address) {
            this->name = _name;
            this->age = _age;
            this->address = _address;
        }

        void setName (string _name) { this->name = _name; }
        string getName() { return name; }
        void setAge (int _age) { this->age = _age; }
        int getAge() { return age; }
        void setAddress (string _address) { this->address = _address; }
        string getAddress() { return address; }

        void display() {
            cout << "Name: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "Address: " << address << endl;
        }
};