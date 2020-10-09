//
// Created by Anthony Sainez on 10/6/20.
//
// Sources Used
//  *   I used the textbook, notes taken during the lectures,
//      companion material from the textbook.
//  *   I watched this video here for a refresher on the topic,
//      and I used the lecture slides he linked in the video
//      description. https://www.youtube.com/watch?v=2DmK_H7IdTo
//  *   I used the standard library swap function because I thought
//      that writing out what it does in full is significantly
//      less readable.
//

#include <iostream>

using namespace std;

// From 6.2 Maintaining the heap property
void maxHeapify(int arr[], int n, int i){
    // Similar to buildMaxHeap but assumes part
    // of the array is already sorted.
    int largest = i;
    int left = 2*i, right = 2*i + 1;
    
    // If left child is larger than the root...
    if (left < n && arr[left] > arr[largest])
        largest = left;
    else
        largest = i;
    
    // If right child is larger than the largest so far...
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    // If the largest isn't the root...
    if (largest != i) {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
    
}

// From 6.3 Building a heap
void buildMaxHeap(int arr[], int n){
    // Creates a max heap from an unsorted array.
    for (int i = (n/2)-1; i >= 0; i--){
        maxHeapify(arr, n, i);
    }
}

// From 6.4 The heapsort algorithm
void heapSort(int arr[], int heapSize){
    buildMaxHeap(arr, heapSize);
    
    // Don't use heapSize--, it will decrement the heapsize
    // and you don't want that happening.
    for (int i = heapSize - 1; i >= 0; i--){
        swap(arr[i], arr[0]);
        maxHeapify(arr, i, 0);
    }
}

int main() {
    int n;
    cin >> n;
    
    int* arr = new int[n];

    for(int i = 0; i < n; i++)
        cin >> arr[i];
    
    heapSort(arr, n);
    
    for(int i = 0; i < n; i++)
        cout << arr[i] << ";";
    
    return 0;
}
