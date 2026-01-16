#include <iostream>
using namespace std;

class Base {
    protected: 
        int proctedtedVar;

        void protectedMethod() {
            cout << "This method is protected" << endl;
        }
};

class Derived: public Base { // This is a subclass of Base
    public:
        void getProtectedInfo() { // Function to access protected members of Base
            proctedtedVar = 10; // Accessing protected member from base class
            cout << proctedtedVar << endl;
            protectedMethod(); // Calling protected method from base class
        }
};

int main () {
    Derived object;
    object.getProtectedInfo();
    return 0;
}