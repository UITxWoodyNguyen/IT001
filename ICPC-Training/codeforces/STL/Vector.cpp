#include <iostream>
using namespace std;

template <class T>
class Vector {
    private:
        T* data;    // vector's data storage
        int size;     // number of elements in the vector
        int capacity; // vector's capacity

        void resize (int newCapacity) {
            T* newData = new T[newCapacity];
            for(int i = 0; i < size; i++)
                newData[i] = data[i];

            delete[] data;
            data = newData;
            capacity = newCapacity;
        }

    public:
        Vector() {
            size = 0;
            capacity = 1;
            data = new T[capacity];
        }

        Vector (int capacity) {
            size = 0;
            this->capacity = capacity;
            data = new T[capacity];
        }

        
};