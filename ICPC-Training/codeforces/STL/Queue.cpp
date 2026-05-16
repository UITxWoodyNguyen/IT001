#include <iostream>
using namespace std;

template <class T>
class Queue {
    private:
        T* data;    // queue's data storage
        int size;   // queue capacity
        int head;   // index of the first element
        int tail;   // index of the last element

        void resize (int newSize) {
            T* newData = new T[newSize];
            int currentSize = getSize();
            for(int i = 0; i < size; i++)
                newData[i] = data[(head + i) % size];

            delete[] data;
            data = newData;
            size = newSize;
            head = 0;
            tail = currentSize;
        }

    public:
        Queue() {
            size = 8;
            data = new T[size];
            head = 0;
            tail = 0;
        }

        Queue (int size) {
            this->size = size;
            data = new T[size];
            head = 0;
            tail = 0;
        }

        Queue& operator= (const Queue& other) {
            if (this == &other) return *this;

            delete[] data;
            size = other.size;
            data = new T[size];
            head = other.head;
            tail = other.tail;

            for(int i = 0; i < size; i++)
                data[i] = other.data[i];

            return *this;
        }

        bool isEmpty() {    // check if the queue is empty
            return head == tail;
        }

        int getSize() {     // return the number of elements in the queue
            return (tail - head + size) % size;
        }

        T& front() {    // return the first element in the queue
            if (isEmpty()) throw runtime_error("QUEUE IS EMPTY!!!");
            return data[head];
        }

        T& back() {   // return the last element in the queue
            if (isEmpty()) throw runtime_error("QUEUE IS EMPTY!!!");
            return data[(tail - 1 + size) % size];
        }

        void push (T value) {   // push back an element into the queue
            if (getSize() == size - 1) resize(size * 2);
            data[tail] = value;
            tail = (tail + 1) % size;
        }

        void pop() {    // pop the first element in the queue
            if (isEmpty()) throw runtime_error("QUEUE IS EMPTY!!!");
            head = (head + 1) % size;
        }
};