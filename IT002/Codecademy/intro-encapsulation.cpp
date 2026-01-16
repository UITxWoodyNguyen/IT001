#include <iostream>
using namespace std;

class getData {
    private:
        int num; // num is a privare member variable, which cannot be accessed in the main

    public: // all functions declared in public class can be accessed in the main
        void set(int n) { // same as cin function
            num = n;
        }

        int get() { // same as cout function
            return num;
        }
    
};

int main () {
    getData u;
    u.set(36);
    cout << u.get() << endl;
    return 0;
}