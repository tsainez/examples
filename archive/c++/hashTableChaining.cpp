//
//  hashTableChaining.cpp
//
//  Created by Anthony Sainez on 30 October 2020.
//  Copyright © 2020 Anthony Sainez. All rights reserved.
//
//  Sources Used
//      *   I used the textbook, notes taken during the lectures,
//          companion material from the textbook.
//              * page 258
//      *   https://en.cppreference.com/w/Main_Page
//      *   https://www.cplusplus.com/reference/sstream/stringstream/
//      *   I used some of my old code I wrote from my days at Gavilan college,
//          where my teacher had me write a hash table program in Java. It was horrible,
//          and worst of all: it didn't even count towards my degree.
//

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Node {
    int key;
    Node *next;

    Node() {
        key = -1;
        next = NULL;
    }
};

// taken from CLRS page 258
void chainedHashInsert(Node *row, int key) {
    if (row->key < 0) {
        row->key = key;
    } else {
        Node *curr, *temp;

        curr = new Node();
        curr->key = key;

        temp = new Node();
        temp->key = row->key;
        temp->next = row->next;

        row->key = key;
        row->next = temp;
    }

    return;
}

// taken from CLRS page 258
void chainedHashDelete(Node *row, int key) {
    if (row->next == NULL) {
        if (row->key == key) {
            row->key = -1;
            cout << key << " : DELETED" << endl;
        } else {
            cout << key << " : DELETE FAILED" << endl;
        }

        cout << "++++++++++++++++++++" << endl;

        return;
    }

    Node *curr, *prev;
    curr = row;

    while (curr != NULL) {
        if (curr->key == key) {
            if (curr->next == NULL) {
                delete curr;
                prev->next = NULL;
            } else {
                curr->key = curr->next->key;
                curr->next = curr->next->next;
            }

            cout << key << " : DELETED" << endl;
            cout << "++++++++++++++++++++" << endl;

            return;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    cout << key << " : DELETE FAILED" << endl;
    cout << "++++++++++++++++++++" << endl;

    return;
}

// taken from CLRS page 258
void chainedHashSearch(Node *row, int key, int location) {
    int index = 0;

    if (row->key == key) {
        cout << key << " : FOUND AT " << location << "," << index << endl;
        cout << "++++++++++++++++++++" << endl;

        return;
    }

    Node *curr = row->next;

    while (curr != NULL) {
        index++;

        if (curr->key == key) {
            cout << key << " : FOUND AT " << location << "," << index << endl;
            cout << "++++++++++++++++++++" << endl;

            return;
        }

        curr = curr->next;
    }

    cout << key << " : NOT FOUND" << endl;
    cout << "++++++++++++++++++++" << endl;

    return;
}

/*
 The input contains one of the following commands on a line:
 • i key: Insert key into the hash table. For example, “i 2” means “Insert key 2 into the hash table”. For collisions, insert the colliding key at the beginning of the linked list. You just need to insert the key and do not have to output anything in this case.
 • d key: Delete key from the hash table. For example, “d 2” means “Delete key 2 from the hash table”. Do nothing if the hash table does not contain the key. If there are multiple elements with the same key value, delete just one element. If the delete is successful, you have to output:
 key : DELETED
 If not (since there was no element with the given key), output:
      key : DELETE FAILED
 • s key: Search key in the hash table. If there is an element with the key value, then you
 have to output:
      key : FOUND AT i,j
 where i is the hash table index and j is the linked list index. If there are multiple elements with the same key value, choose the first one appearing in the linked list. If you do not find the key, then output:
      key : NOT FOUND
 • o: Output the hash table. Output the entire hash table. Each line should begin with the slot/hash table index followed by key values in the linked list. For example, if m = 3 and we inserted 3, 6, and 1 into an empty table in this order, then you should output:
 0 : 6->3 1:1 2:
 • e: Finish your program.
 */

int main() {
    int size, key, location;
    cin >> size;
    cin.ignore();

    const int len = size;

    Node *table[len];

    for (int i = 0; i < len; i++)
        table[i] = new Node();

    string str; stringstream ss; Node *temp;

    // This is where a sstream comes in handy: for a running loop program.
    while (getline(cin, str)) {
        if (str.length() > 1) {
            ss << str.substr(2, str.length() - 1);
            ss >> key;
            ss.clear();

            location = key % len;
        }
        
        // Main input sequence where the Grader.sh file tells the program
        // how to input the values into the hash table.
        if (str[0] == 'i')
            chainedHashInsert(table[location], key);
        else if (str[0] == 'd')
            chainedHashDelete(table[location], key);
        else if (str[0] == 's')
            chainedHashSearch(table[location], key, location);
        else if (str[0] == 'o') {
            for (int i = 0; i < len; i++) {
                temp = table[i];
                cout << i << " : ";
                
                while (temp != NULL) {
                    if (temp->key < 0) {
                        cout << endl;
                    } else {
                        cout << temp->key;
                        if (temp->next != NULL)
                            cout << "->";
                        else
                            cout << endl;
                    }
                    temp = temp->next;
                } // end while
            } // end for
            cout << "++++++++++++++++++++" << endl;
        } else // end elif chain
            break;
    } // end of the entire input sequence loop

    return 0;
}
