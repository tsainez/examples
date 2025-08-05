//
//  CharStack.cpp
//
//  Created by Anthony Sainez on 1 November 2019
//  Copyright © 2020 Anthony Sainez. All rights reserved.
//

#include <iostream>
using namespace std;

class CharStack {
private:
    int size;
    int top;
    char *stackArray;
public:
    CharStack(int newSize) {
        size = newSize;
        stackArray = new char[size];
        top = -1; // no items yets
    }
    
    void push(char newLetter) {
        stackArray[++top] = newLetter;
    }
    
    char pop() {
        return stackArray[top--];
    }
    
    char peek() {
        return stackArray[top];
    }
    
    bool isEmpty() {
        return (top == -1);
    }
    
    bool isFull() {
        return (top == size - 1);
    }
};

int main() {
    char a[] = {'h', 'e', 'l', 'l', 'o', ',', 'w', 'o', 'r', 'l', 'd', '!'};
    CharStack reverse(12);
    
    for (int i = 0; i < 12; i++)
        reverse.push(a[i]);
    
    while (!reverse.isEmpty())
        cout << reverse.pop();
    
    cout << endl;
}
