//
//  quickSort.cpp
//
//  Created by Anthony Sainez on 9 October 2020.
//
//  Sources Used
//      *   I used the textbook, notes taken during the lectures,
//          companion material from the textbook.
//      *   I used the helpful link that was provided in the lab
//          file. http://www.cplusplus.com/reference/cstdlib/rand/
//      *   I used the http://www.cplusplus.com/reference as a
//          source when I look at examples online. That, and w3schools.
//          They provide pretty easy to read and clear documentation.
//

#include <iostream> /* cout, cin */
#include <cstdlib>  /* rand */

using namespace std;

// from CLRS page 171
int partition(int arr[], int p, int r) {
    // x in the psuedocode is the pivot
    int x = arr[r];
   
    // i is the index of the smaller element
    int i = p-1;
 
    for(int j = p; j <= (r-1); j++) {
        if(arr[j] <= x) {
            i++;
            swap(arr[i], arr[j]);   // in CLRS it is 'exchange'
        }
    }
    
    swap(arr[i + 1], arr[r]);
    return (i+1);
}
 
// from CLRS page 179
int randomizedPartition(int arr[], int p, int r) {
    srand(time(NULL));  // generate random seed
    int i = p + rand() % (r - p);   // random(p, r) in CLRS
 
    // exchange A[r] with A[i]
    swap(arr[i], arr[r]);
 
    return partition(arr, p, r);
}

// from CLRS page 171, moved to the bottom for procedural function
// declaration issues (not defined if in order presented in book)
void quickSort(int arr[], int p, int r) {   // (randomized)
    if (p < r) {
        int q = randomizedPartition(arr, p, r);
        quickSort(arr, p, q-1); // can't use -- or ++
        quickSort(arr, q+1, r);
    }
}

int main() {
    int n;
    cin >> n;
    
    int* arr = new int[n];

    for(int i = 0; i < n; i++)
        cin >> arr[i];
    
    quickSort(arr, 0, n-1);
    
    for(int i = 0; i < n; i++)
        cout << arr[i] << ";";
    
    return 0;
}
