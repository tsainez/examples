//
// Created by Anthony Sainez on 10/16/20.
//
// Sources Used
//  *   I used the textbook, notes taken during the lectures,
//      companion material from the textbook.
//  *   I had to look at the library for vector.
//  *   I used the http://www.cplusplus.com/reference as a
//      source when I look at examples online. That, and w3schools.
//      They provide pretty easy to read and clear documentation.
//  *   I sought some advice from the ACM discord, and had an anonymous
//      user tutor me on how to this by sharing my screen.
//

#include <iostream>
#include <vector>

using namespace std;

const int length = 10;

// Using vector<vector<int>> notation helps us utilize the vector library
// functions such as pushback, resize, and more.

vector<vector<int>> countingSort(vector<vector<int>> arr, vector<int> exp) {
    // This was featured in the homework, so I used some of that to help me here.
    // I did the homework before the lab submission.
    vector<int> counting(length, 0);
    vector<vector<int>> keys;
    keys.resize(exp.size());
    
    // Half of this is just working with vectors.
    for(int i = 0; i < exp.size(); i++) {
        counting[exp[i]]++;
    }
    
    for( int i = 1; i < counting.size(); i++) {
        counting[i] = counting[i] + counting[i-1];
    }
    
    for (int i = 0; i < exp.size(); i++) {
        keys[i].resize(length);
    }
    
    for(int i = exp.size()-1; i >= 0; i--) {
        swap(keys[counting[exp[i]]-1], arr[i]);
        counting[exp[i]] = counting[exp[i]] - 1;
    }
    
    return keys;
}

void radixSort(vector<vector<int>> arr) {
    for (int i = length-1; i >= 0; i--) {
        vector<int> temp;   // Although I'd like to declare this outside,
                            // if I don't, i get a billion errors about malloc.
        
        for (int j = 0; j < arr.size(); j++ ) {
            temp.push_back(arr[j][i]);
        }
        
        arr = countingSort(arr,temp);
    }
    
    // Weird bug here, not sure how to solve, but it compiles fine and
    // solves things well.
    for(int i = 0; i < arr.size(); i++){
        for (int j = 0; j < arr[i].size(); j++){
            cout << arr[i][j] << ";";
        }
        cout << endl;
    }
}

int main() {
    int n;
    
    cin >> n;
    
    vector<vector<int>> arr;
    arr.resize(n);
    
    int temp;
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < length; j++) {
            cin >> temp;
            arr[i].push_back(temp);
        }
    }
    
    radixSort(arr);
    
    return 0;
}

