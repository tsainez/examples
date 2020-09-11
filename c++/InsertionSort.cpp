//
// Created by Anthony Sainez on 9/2/20.
//
// Sources Used
//  *   I used the textbook, notes taken during the lectures,
//      companion material from the textbook.
//  *   I used some prior code I wrote in an earlier class taken.
//      The specific code can be viewed at the following link:
//      https://github.com/tsainez/examples/blob/master/c%2B%2B/Sorting.cpp
//

#include <iostream>
using namespace std;

int main(int argc,char *argv[]) {
    int n;
    cin >> n;
    
    int* arr = new int[n];
    
    for(int i = 0; i < n; i++)
        cin >> arr[i];
        
    /* INSERTION SORT HAPPENS HERE */
    for(int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
     
        // If you wanted to reverse the order of sorting,
        // you can change the sign of the second condition.
        while(j >= 0 && arr[j] < key) {
            arr[j+1] = arr[j];
            j = j - 1;
        }
        
        arr[j + 1] = key;
    }
    /* INSERTION SORT ENDS HERE*/
        
    for(int i = 0; i < n; i++)
        cout << arr[i] << ";";
    
    return 0;
}
