//
//  DeQueue.cpp
//
//  Created by Anthony Sainez on 1 November 2019
//  Copyright © 2020 Anthony Sainez. All rights reserved.
//

#include <iostream>
using namespace std;

class Queue {
private:
    int size, front, rear, number_items;
    int *queueArray;
public:
    Queue(int newSize) { // constructor
        size = newSize;
        queueArray = new int[size];
        front = 0; // front moves forwards
        rear = -1; // theres nothing there so just make it -1
        number_items = 0; // no items yet
    }
    
    // rear++ upon insertion if rear is far right move it to far lef
    void insert_rear(int newValue) {
        if (rear == size - 1)
            rear = -1; // move to beginning to deal with wraparound
        
        rear++;
        queueArray[rear] = newValue; // insert
        number_items++; // resize
    }
    
    // upon insertion if front reaches far left move to far right
    void insert_front(int newValue) {
        if (front == 0) // if front reaches far left
            front = size; // move to far righ
        
        front--; // shift it
        queueArray[front] = newValue; // inserrt
        number_items++; // resize
    }
    
    int remove_front() {
        int temp = queueArray[front];
        if (front == size-1) // front is far right
            front = -1; // move to far left
        
        front++; // move right index of front
        number_items--; // resize
        return temp;
    }
    
    
    void remove_rear() {
        if (rear == 0)
            rear = size; // if rear reaches far left move to far right
        
        rear--; // move left
        number_items--; // resize
    }
    
    int peekFront() {
        return queueArray[front];
    }
    
    int peekRear() {
        return queueArray[rear];
    }
    
    bool isEmpty() {
        return (number_items == 0);
    }
    
    bool isFull() {
        return (number_items == size);
    }
    
    int qsize() { // stands for queue size
        return number_items;
    }
};

int main() {
    Queue aQueue(5);
    aQueue.insert_rear(10); // 10
    aQueue.insert_rear(20); // 10, 20
    aQueue.insert_rear(30); // 10, 20, 30
    aQueue.insert_rear(40); // 10, 20, 30, 40
    
    while (!aQueue.isEmpty()) {
        cout << aQueue.peekRear() << " ";
        aQueue.remove_rear(); // ghetto show queue that also clears it
    }
    
    aQueue.insert_rear(10); // 10
    cout << "\n" << aQueue.peekRear() << " "; // 10
    cout << "\n" << aQueue.peekFront() << " "; // also 10
    
    aQueue.insert_front(20); // 20, 10
    cout << "\n" << aQueue.peekFront() << " "; // 20
    
    aQueue.insert_front(30); // 30, 20, 10
    cout << "\n" << aQueue.peekFront() << " "; // 30
    
    aQueue.remove_front(); // remove 30
    cout << "\n" << aQueue.peekFront() << " "; // 20 is left
}
