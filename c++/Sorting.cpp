//
//  Sorting.cpp
//
//  Created by Anthony Sainez on 1 November 2019
//  Copyright © 2020 Anthony Sainez. All rights reserved.
//

#include <iostream>
using namespace std;

class EncapsulatedArray {
private:
    int *array; // dynamically allocated array;
    int number_of_elements;
public:
    EncapsulatedArray(int size);
    void add(int number_to_add);
    void show();
    void deleteNumber(int number_to_delete);
    void insertFirst(int number_to_insert);
    void swap(int index1, int index2);
    void bubbleSort();
    void selectionSort();
    void insertion_sort();
    void deleteIndex(int index_to_delete);
    void noDups();
    void insertInOrder(int number_to_insert);
};

EncapsulatedArray::EncapsulatedArray(int size) {
    array = new int[size]; // dynamic
    number_of_elements = 0;
}

void EncapsulatedArray::add(int number_to_add) {
    array[number_of_elements] = number_to_add;
    number_of_elements++;
}

// format {x, y, z}
void EncapsulatedArray::show() {
    if(number_of_elements == 1) {
        cout << "array = {" << array[0] << "}\n";
        return; // return is put here so that the function does not continue
    }
    
    int i;
    cout << "array = {";
    for (i=0; i < number_of_elements-1; i++)
        cout << array[i] << ", ";
    cout << array[i] << "}\n ";
}

void EncapsulatedArray::deleteNumber(int number_to_delete) {
    // find index to delete
    int index_to_delete;
    for (index_to_delete=0; index_to_delete<number_of_elements-1; index_to_delete++)
        if (array[index_to_delete] == number_to_delete)
            break; // stop when you find it
    
    if (index_to_delete == number_of_elements-1) // if number isn't found
        return; // leave
    
    // shift left all elements to right of index_to_delete starting leftmost
    for (int i = index_to_delete; i < number_of_elements-1; i++)
        array[i] = array[i+1];
    
    number_of_elements--; // resize
}

void EncapsulatedArray::insertFirst(int number_to_insert) {
    // shift right all elements to the right of index 0 starting rightmost
    for (int i = number_of_elements-1; i>=0; i--)
        array[i+1] = array[i];
    array[0] = number_to_insert;
    
    number_of_elements++; // resizing
}

void EncapsulatedArray::swap(int index1, int index2) {
    int temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}

void EncapsulatedArray::bubbleSort() {
    for (int i = 0; i < number_of_elements-1; i++) {
        for (int j = 0; j < number_of_elements-(i+1); j++) {
            if (array[j] > array[j+1])
                swap(j, j+1);
        }
    }
}

void EncapsulatedArray::selectionSort() {
    int min, min_index;
    
    
    for (int current_index = 0; current_index < number_of_elements-1; current_index++) {
        min_index = current_index; // min starts leftmost
        
        for (int i = current_index+1; i < number_of_elements; i++) {
            if (array[i] < array[min_index])
                min_index = i; // min is equal to arrays index (which is smaller)
        }
        
        swap(current_index, min_index); // swap outside 2nd loop
    }
}

void EncapsulatedArray::insertion_sort() {
    int in, out, temp;
    
    // left of out is a partially sorted array
    for (out = 1; out < number_of_elements; out++) {
        in = out; // haha
        temp = array[in]; // store
        
        // while stops when you
        // either reach far left or find number <temp
        while(in > 0 && array[in-1] > temp) {
            array[in] = array[in - 1];
            in--;
        }
        array[in] = temp;
    }
}

void EncapsulatedArray::deleteIndex(int index_to_delete) {
    // shift all elements on top of deleted
    for (int i = index_to_delete; i <= number_of_elements-2; i++)
        array[i] = array[i+1];
    
    number_of_elements--; // resize
}

void EncapsulatedArray::noDups() {
    // assume sorted
    
    for (int i = 0; i < number_of_elements-1; i++) {
        if (array[i] == array[i+1]) {
            deleteIndex(i+1);
            
            i--;
        }
    }
}

void EncapsulatedArray::insertInOrder(int number_to_insert) {
    // find where to insert
    int index_to_insert;
    for (index_to_insert=0; index_to_insert < number_of_elements; index_to_insert++) {
        if (array[index_to_insert] > number_to_insert)
            break; // stop right there!
    }
    
    for (int i = number_of_elements - 1; i >= index_to_insert; i--)
        array[i+1] = array[i];
    
    // insert it
    array[index_to_insert] = number_to_insert;
    
    // resize
    number_of_elements++;
}

int main() {
    cout << "initializing array... " << endl;
    EncapsulatedArray anArray(5);
    anArray.add(9);
    
    cout << "array made: " << endl;
    anArray.show(); // {9}
    
    cout << "add number: " << endl;
    anArray.add(101);
    anArray.add(9);
    anArray.show(); // {9, 101, 9}
    
    cout << "delete number: " << endl;
    anArray.deleteNumber(101);
    anArray.show(); // {9, 9}
    
    cout << "insert first" << endl;
    anArray.insertFirst(1);
    anArray.show(); // {1, 9, 9}
    
    cout << "selection sort: " << endl;
    anArray.selectionSort();
    anArray.show();  // {9, 9, 1}
    
    cout << "no dups: " << endl;
    anArray.noDups();
    anArray.show(); // {9, 1}
    
    cout << "insertion sort: " << endl;
    anArray.insertFirst(2);
    anArray.insertion_sort();
    anArray.show(); // {9, 2, 1}
    
    cout << "bubbleSort: " << endl;
    anArray.insertFirst(3);
    anArray.bubbleSort();
    anArray.show(); // {9, 3, 2, 1}
    
    cout << "insert in order: " << endl;
    anArray.insertInOrder(4);
    anArray.show(); // {9, 4, 3, 2, 1}
    
}
