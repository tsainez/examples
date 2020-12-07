//
//  rodCutting.cpp
//
//  Created by Anthony Sainez on 20 November 2020.
//  Copyright © 2020 Anthony Sainez. All rights reserved.
//
//  Sources Used
//      *   I used the textbook, notes taken during the lectures,
//          companion material from the textbook.
//      *   https://en.cppreference.com/w/Main_Page
//      *   https://web.stanford.edu/class/archive/cs/cs161/cs161.1168/lecture12.pdf
//

#include <iostream>
using namespace std;

// See the Stanford.edu source I listed.
int cutRods(int a[], int n){
    int r[n + 1]; r[0] = 0;
    int s[n + 1];
    
    for(int i = 0; i <= n + 1; i++ ){
        int q = 0;
        for(int j = 1; j <= i; j++){
            if(q < a[j] + r[i - j]){
                q = a[j] + r[i - j];
                s[i] = j;
            }
        }
        r[i] = q;
    }
    
    cout << r[n] << endl;
    
    int x = n;
    while (x > 0){
        cout << s[x] << " ";
        x = x - s[x];
    }
    
    return -1; // End of output
}

int main() {
    int n;
    cin >> n;
    
    int a[n + 1];
    
    for(int i = 1; i< n + 1; i++)
        cin >> a[i];
    
    cout << cutRods(a, n) << endl;
    return 0;
}
