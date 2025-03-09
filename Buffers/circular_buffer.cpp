/*
6. Implement a C++ Fixed-Size Circular Buffer
Question:
Create a circular buffer (ring buffer) that supports push/pop operations efficiently.
Follow-ups:
What are the advantages of circular buffers over dynamic arrays?
How would you make your implementation thread-safe?
Modify the implementation to support blocking and non-blocking behavior.

*/

#include <iostream>

using namespace std;

template <typename T>
class CircularBuffer{
    public:
        CircularBuffer(size_t capacity) : capacity{capacity}{
            buffer = new T[capacity];
            head = 0;
            tail = 0;
            size = 0;
        }

        void push(T element){
            buffer[tail] = element;
            
            if(isFull())
                head = (head + 1) % capacity;
            else
                ++size;
                

            tail = (tail + 1) % capacity;
        }

        void pop(){
            if(size > 0){
                head = (head + 1) % capacity;
                --size;
            }
        }

        bool isFull() const {
            return size == capacity;
        }

        bool isEmpty() const {
            return size == 0;
        }

        size_t getSize() const {
            return size;
        }

        ~CircularBuffer(){
            delete[] buffer;
        }

    private:
        T* buffer;
        size_t head;
        size_t tail;
        size_t capacity;
        size_t size;
};

int main(){

    CircularBuffer<int> cb(5);
    cout << cb.getSize() << endl;
    cb.push(10);
    cb.push(7);
    cout << cb.getSize() << endl;
    cb.pop();
    cout << cb.getSize() << endl;
    cb.push(10);
    cb.push(7);
    cb.push(10);
    cb.push(7);
    cout << cb.getSize() << endl;


    return 0;
}