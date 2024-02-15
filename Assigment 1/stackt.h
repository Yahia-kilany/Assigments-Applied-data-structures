#ifndef STACKT_H

#define STACKT_H 
#include <iostream>
using namespace std;
const int MAX_SIZE = 1000; 

template <class T>
class Stackt {
private:
    T elements[MAX_SIZE];
    int topIndex;

public:
    Stackt() : topIndex(-1) {}

    bool isEmpty() const {
        return topIndex == -1;
    }

    bool isFull() const {
        return topIndex == MAX_SIZE - 1;
    }

    void push(const T& value) {
        if (isFull()) {
            throw runtime_error("Error:STACK OVERFLOW");
            exit(1);
        }
        topIndex++;
        elements[topIndex] = value;
    }

    void pop() {
        if (isEmpty()) {
            throw runtime_error("Error:STACK UNDERFLOW");
            exit(1);
        }
        topIndex--;
    }
    void display() const {
        for ( int i = topIndex; i >= 0; i--) {
            std::cout << elements[i] << std::endl;
        }
        std::cout << "---" << std::endl;
    }

    const T& top() const {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return elements[topIndex];
    }
};
#endif // STACKT_H