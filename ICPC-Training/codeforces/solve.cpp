// Sticking to <iostream> only, until I pass DSA at UIT!!!!!
#include <iostream>
using namespace std;

const string FILE_NAME = "test";

// include <queue>
template <class T>
class Queue {
    private:
        T* data;
        int size;
        int head;
        int tail;

        void resize(int newSize);

    public:
        Queue();
        Queue(int size);
        int getSize();
        bool isEmpty();
        T& front();
        T& back();
        void push (const T& value);
        void pop();
};

struct Point {
    int x, y;
};



int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    if (fopen((FILE_NAME + ".inp").c_str(), "r")) {
        freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
        freopen((FILE_NAME + ".out").c_str(), "w", stdout);
    }

    
}