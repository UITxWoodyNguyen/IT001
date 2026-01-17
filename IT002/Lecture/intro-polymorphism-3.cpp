#include <iostream>
using namespace std;

class Animal {
    public:
        virtual void makeSound() {
            cout << "Random Sound" << endl;
        }
};

class Dog : public Animal {
    public: 
        void makeSound() {
            cout << "Woof" << endl;
        }
};

class Cat : public Animal {
    public:
        void makeSound() {
            cout << "Meow" << endl;
        }
};

class Duck : public Animal {
    public:
        void makeSound() {
            cout << "Quack" << endl;
        }
};

int main () {
    Animal* animal[] = {
        new Dog(),
        new Cat(),
        new Duck()
    };

    for(Animal* id : animal) id->makeSound(); // Polymorphic call
    return 0;
}