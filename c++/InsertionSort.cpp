//
// Created by Anthony Sainez on 9/2/20.
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
        int curr = arr[i];
        int j = i--;
        
        while(j >= 0 && arr[j] < curr) {
            arr[j+1] = arr[j];
            j--;
        }
        
        arr[j+1] = curr;
    }
        
    for(int i = 0; i<n; i++)
        cout << arr[i] << ";";
    
    return 0;
}

