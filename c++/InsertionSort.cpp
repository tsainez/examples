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
    
    /* INSERTION SORT ENDS HERE*/
        
    for(int i = 0; i < n; i++)
        cout << arr[i] << ";";
    
    return 0;
}
