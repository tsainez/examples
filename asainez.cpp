//
// Created by Anthony Sainez on 11/13/20.
//
// Sources Used
//  *   I used the textbook, notes taken during the lectures,
//      companion material from the textbook.
//  *   https://www.geeksforgeeks.org/bitsstdc-h-c/
//  *   I used some of my old code I wrote from my days at Gavilan college,
//      where my teacher had me write a hash table program in Java. It was horrible,
//      and worst of all: it didn't even count towards my degree.
//

#include <bits/stdc++.h>
using namespace std;

// The hashMap object contains a hash table and all the functions that
// enable it to modify the hashTable array. It also keeps track of the size.
// This object oriented programming technique I learned from my data structures
// class which I took quite a while ago at Gavilan college.

class hashMap {
    int* hashTable; // Dynamically allocated.
    int size;
    const int hashSize = 13;
public:
    void displayHash() {
        cout << "++++table printout++++" << endl;
        
        // You cannot do i < size, since some of the
        // entries are deleted. The assignment guarantees
        // that the size will be m = 13.
        for (int i = 0; i < hashSize; i++) {
            if (hashTable[i] != -1)
                cout << hashTable[i] << endl;
            else
                cout << "" << endl;
        }
    }

    void search(int key) {
        for(int i = 0; i < hashSize; i++) {
            if(hashTable[i] == key) {
                cout << i << "\n";
            }
        }
        
        // Passed the entire array without finding it.
        // This algorithm has a linear complexity.
        cout << "NOT_FOUND" << endl;
    }

    void deleteKey(int key) {
        for(int i = 0; i < hashSize; i++) {
            if(hashTable[i] == key) {
                hashTable[i] = -1;
            }
        }
    }
    
    // Constructor function. Initalizes an empty hash table.
    hashMap() {
        hashTable = new int[hashSize];
        size = 0;
        for (int i = 0; i < hashSize; i++)
            hashTable[i] = -1; // Every value is empty.
    }
    
    int hash(int key) {
        return (key % 13);
    }
    
    int doubleHash(int key) {
        return (1 + (key % 11));
    }

    bool isFull() {
        return (size == hashSize);
    }

    void insertHash(int key) {
        if (isFull())
            return; // Leave early.

        int index = hash(key);
        
        // If there is a collision, we must deal with it
        // with open addressing using double hashing.
        if (hashTable[index] != -1) {
            int index2 = doubleHash(key);
            int i = 1;  // Must be declared outside the loop,
                        // else, runs forever.
            
            while(true) {
                int newIndex = (index + i * index2) % 13;
                
                // If no collision, store.
                if (hashTable[newIndex] == -1) {
                    hashTable[newIndex] = key;
                    break;
                }
                i++;    // There was a collision, so we must move
                        // onto the next value.
            }
        } else {
            // There wasn't a collision, so we don't have to
            // implement double hashing. Simply insert!
            hashTable[index] = key;
        }
        size++;
    }
};

int main() {
    hashMap h; // Create a new hash table object.
    int i;
    
    while(true) {
        cin >> i;
        if(i == -1)
            break;
        h.insertHash(i);
    }
    
    h.displayHash();

    cout << "++++searching++++" << endl;
    while(true) {
        cin >> i;
        if(i == -2)
            break;
        h.search(i);
    }
    // deleting some keys
    cout << "++++deleting++++" << endl;
    while(true) {
        cin >> i;
        if(i == -3)
            break;
        h.deleteKey(i);
    }

    h.displayHash();
    return 0;
}
