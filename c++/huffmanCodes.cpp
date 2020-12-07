//
//  huffmanCodes.cpp
//
//  Created by Anthony Sainez on 6 December 2020
//  Copyright © 2020 Anthony Sainez. All rights reserved.
//
//  Sources used:
//      *   For help on initializing a standard library priority queue, I found the
//          documentation to be unhelpful. This StackOverflow answer helped me
//          significantly. https://stackoverflow.com/questions/7912595/initialization-for-stl-priority-queue/7912764#7912764
//      *   I used the textbook, notes taken from during lectures, and companion
//          material from the textbook.
//

#include<bits/stdc++.h>

using namespace std;

// This is a global variable that is called by a helper function to manage
// the bit encodings of each letter. There is a better practice way of
// doing this, but I am unsure of how to approach the problem.
vector<int> globalBits;

struct Node {
    int freq;
    bool isLeaf;
    
    Node* left;
    Node* right;
    
    // Constructor
    Node(bool isLeaf, int freq) {
        left = right = nullptr;
        this->freq = freq;
        this->isLeaf = isLeaf;
    }
};

struct Min {
    // The 'Min' struct is actually a functor that serves to tell the
    // standard library priority queue object how to sort the elements.
    // This is set up to give us a min priority queue.
    
    bool operator() (Node* l, Node* r) {
        return (l->freq > r->freq);
    }
};

void printBits(int* b, int location, int tmp) {
    globalBits.push_back(-1);   // '-1' is a placeholder, see below
                                // The algorithm actively searches for '-1' tokens
    globalBits.push_back(tmp);
    
    for(int i = 0; i < location; i++)
        globalBits.push_back(b[i]);
}

void traverse(Node* root, int* arr, int location) {
    // This function places 0 or 1 into the array depending on if you are
    // travelling left or right on the tree, and will print out the binary
    // code if the node is a leaf.
    
    if (root == nullptr)
        return; // Probably... should never happen. Maybe.
    
    if (root->isLeaf)
        printBits(arr, location, root->freq);
    
    if (root->left) {
        arr[location] = 0;
        traverse(root->left, arr, location + 1);
    }
    
    // You cannot use an elseif here. I am not sure why, but it will not pass
    // the test cases unless you keep these if statements cleanly separated.
    
    if (root->right) {
        arr[location] = 1;
        traverse(root->right, arr, location + 1);
    }
}

Node* huffmanEncode(int* arr, int n) {
    priority_queue<Node*, vector<Node*>, Min> minPriorityQueue;
    
    for(int i = 0; i < n; i++)
        minPriorityQueue.push(new Node(true, arr[i])); // Mark all nodes that are leaf nodes
    
    for(int i = 0; i < n - 1; i++) {
        Node* x;
        Node* y;
        Node* z;
        
        x = minPriorityQueue.top(); minPriorityQueue.pop();
        y = minPriorityQueue.top(); minPriorityQueue.pop();
        
        // Now, we must begin to follow the actual Huffman tree structure.
        z = new Node(false, x->freq + y->freq); // This one is not a leaf.
        z->left = x;
        z->right = y;
        minPriorityQueue.push(z);
    }
    
    return minPriorityQueue.top();
}

int main() {
    
    int n;
    cin >> n;
    
    // You cannot declare the array in any other way,
    // for some reason it causes a segfault or it will
    // simply not yield the correct test results. Not sure
    // as to why this is the case. Really odd bug.
    int arr[n];
    int counter = 0;
    
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
        counter++;
    }
    
    int size = sizeof(arr) / sizeof(arr[0]);
    
    /*
    if (size != n) {
        cout << "Something went wrong. Dying!";
        return 0;
    }
    */
    
    Node* root = huffmanEncode(arr, n);
    int bits[n];
    int leaf = 0;
    
    // We gotta fill the tree, so we traverse it.
    traverse(root, bits, leaf);
    // Everything at this point is dynamic, so it is able
    // to find the other nodes of the tree like a loose linked list.
    
    int match = 0;
    int tmp = 0;
    vector<int>::iterator it;
    int end = 0;
    
    
    for(int i = n; i != 0; i--) {
        // The iterator returns an iterator to the first element in the range with
        // an equal value to the last parameter.
        it = find(globalBits.begin(), globalBits.end(), arr[tmp]);
        
        // Now we can ascertain to where the exact match is.
        match = distance(globalBits.begin(), it) + 1;
        
        for(int j = match; j < globalBits.size(); j++) {
            if(globalBits[j] == -1) {
                end = j;
                globalBits.erase(globalBits.begin() + match - 2,
                                 globalBits.begin() + end);
                break;
            }
            cout << globalBits[j];
        }
        cout << endl;
        tmp++;
    }
    
    return 0;
}
