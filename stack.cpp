#include <iostream>
#include "stack.h"

using namespace std;

Stack::Stack(int stackCapacity) {
    capacity = stackCapacity;
    stack = new char[capacity];
    tail = -1;
}

Stack::~Stack() {
    delete[] stack;
}

bool Stack::isEmpty() {
    return (tail == -1);
}

char& Stack::top() {
    if(isEmpty()) {
        throw "Stack is Empty";
    }
    return stack[tail];
}

void Stack::push(char item) {
    if(tail == capacity -1) {
        char* stack = new char[capacity]; 
    }
    stack[++tail] = item;
}

void Stack::pop() {
    if(isEmpty()) {
        throw "Stack is empty. Cannot delete";
    } else {
        tail--;
    }
}
