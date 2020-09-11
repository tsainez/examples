//
//  Recursion.cpp
//
//  Created by Anthony Sainez on 1 November 2019
//  Copyright © 2020 Anthony Sainez. All rights reserved.
//

#include <iostream>
#include <iomanip>
using namespace std;

class DArray {
private:
    double * array; // array of doubles
    int nElms; // number of elements
public:
    DArray(int max) {
        array = new double[max];
        nElms = 0; // empty so far
    }
    
    void insert(double value) {
        array[nElms++] = value;
    }
    
    void display() {
        for (int j = 0; j < nElms; j++)
            cout << array[j] << " ";
        cout << endl;
    }
    
    void mergeSort() {
        double *workSpace = new double[nElms]; // provides place to merge
        recMergeSort(workSpace, 0, nElms-1);
    }
    
    void recMergeSort(double *workSpace, int lowerBound, int upperBound) {
        if (lowerBound == upperBound)
            return;
        else {
            int mid = (lowerBound + upperBound) / 2;
            recMergeSort(workSpace, lowerBound, mid); // sort lower half
            recMergeSort(workSpace, mid+1, upperBound); // sort upper half
            
            merge(workSpace, lowerBound, mid+1, upperBound); // merge them
        } // endelse
    }// end recmergesort
    
    void merge(double *workSpace, int lowPtr, int highPtr, int upperBound) {
        int j = 0;
        int lowerBound = lowPtr;
        int mid = highPtr-1;
        int n = upperBound-lowerBound+1;
        while (lowPtr <= mid && highPtr <= upperBound) {
            if (array[lowPtr] < array[highPtr])
                workSpace[j++] = array[lowPtr++];
            else
                workSpace[j++] = array[highPtr++];
        }
        
        while (lowPtr <= mid)
            workSpace[j++] = array[lowPtr++];
        
        while(highPtr <= upperBound)
            workSpace[j++] = array[highPtr++];
        
        for(j=0; j<n; j++)
            array[lowerBound+j] = workSpace[j];
    }
};

class Recursion {
public:
    int triangleIterative(int num) {
        int total = 0;
        while (num > 0) {
            total = total + num;
            num--;
        }
        return total;
    }
    
    int triangleRecursive(int num) {
        if (num == 1)
            return 1;
        else
            return (num + triangleRecursive(num - 1));
    }
    
    int factorialIterative(int num) {
        int total = 1;
        while (num > 0) {
            total = total * num;
            num--;
        }
        return total;
    }
    
    int factorialRecursive(int num) {
        if (num == 0)
            return 1;
        else
            return num * factorialRecursive(num-1);
    }
    
    void binarySearchIterative(int guess, int numToGuess, int count, int upperLimit, int lowerLimit) {
        // assumes that guess is between upper and lower limit
        // and assumes that numtoguess is between upper and lower limit
        // these are the limitations to this search function
        while (true) {
            if (guess == numToGuess) {
                cout << "\nYou guessed it in " << count << " iterative tries.\n";
                break;
            } else if ( guess > numToGuess ) {
                upperLimit = guess;
                guess = (upperLimit + lowerLimit) / 2; // average
            } else if (guess < numToGuess ) {
                lowerLimit = guess;
                guess = (upperLimit + lowerLimit) / 2; // average again
            }
            count++;
        }
    } // end iterative search
    
    void binarySearchRecursive(int guess, int numToGuess, int count, int upperLimit, int lowerLimit) {
        // assumes that guess and numtoguess are between upper and lower limits
        if (guess == numToGuess)
            cout << "\nYou guessed it in " << count << " recursive tries\n";
        else if (guess > numToGuess) {
            upperLimit = guess;
            guess = (upperLimit + lowerLimit) / 2;
            binarySearchRecursive(guess, numToGuess, count+1, upperLimit, lowerLimit);
        } else if (guess < numToGuess) {
            lowerLimit = guess;
            guess = (upperLimit + lowerLimit) / 2;
            binarySearchRecursive(guess, numToGuess, count+1, upperLimit, lowerLimit);
        }
    }
    
    void compoundInterestIterative(double monthlyDeposit, double interest, int years) {
        double total=0, payments=0, interestEarned;
        cout << endl;
        for (int year = 1; year <= years; year++) {
            total += monthlyDeposit*12;
            total = total + total*(interest/100);
            payments += monthlyDeposit*12;
            interestEarned = total - payments;
            cout << "at end of year " << setw(2) << year;
            cout << " : total savings " << setw(7) << total;
            cout << " : total payments " << setw(5) << payments;
            cout << " : interestEarned " << interestEarned;
            cout << endl;
        }
    }
    
    void compoundInterestRecursive(double monthlyDeposit, double interest,
                                   int years, int year, double total,
                                   double payments, double interestEarned) {
        if (year == years+1)
            return; // leave!
        else {
            total += monthlyDeposit*12;
            total = total + total*(interest/100);
            payments += monthlyDeposit*12;
            interestEarned = total - payments;
            cout << "REC at end of year " << setw(2) << year;
            cout << " : total savings " << setw(7) << total;
            cout << " : total payments " << setw(5) << payments;
            cout << " : interestEarned " << interestEarned;
            cout << endl;
            year = year +1;
            compoundInterestRecursive(monthlyDeposit, interest, years, year, total, payments, interestEarned);
        }
    }
};

int main() {
    // Here's a demonstration of the above code.
    DArray *arr = new DArray(100);
    arr->insert(64);
    arr->insert(21);
    arr->insert(33);
    arr->insert(70);
    arr->insert(12);
    arr->insert(85);
    arr->insert(44);
    arr->insert(3);
    arr->insert(99);
    arr->insert(0);
    arr->insert(108);
    arr->insert(36);
    arr->display();
    arr->mergeSort();
    arr->display();
    
    cout << "\n\nDONE WITH DArray STUFF\n\n";
    
    Recursion *rec = new Recursion;
    cout << "triangleIterative(1): " << rec->triangleIterative(1) << endl;
    cout << "triangleIterative(2): " << rec->triangleIterative(2) << endl;
    cout << "triangleIterative(3): " << rec->triangleIterative(3) << endl;
    cout << "triangleIterative(4): " << rec->triangleIterative(4) << endl;
    
    cout << endl;
    
    cout << "triangleRecursive(1): " << rec->triangleRecursive(1) << endl;
    cout << "triangleRecursive(2): " << rec->triangleRecursive(2) << endl;
    cout << "triangleRecursive(3): " << rec->triangleRecursive(3) << endl;
    cout << "triangleRecursive(4): " << rec->triangleRecursive(4) << endl;
    
    cout << endl;
    
    cout << "factorialIterative(1): " << rec->factorialIterative(1) << endl;
    cout << "factorialIterative(2): " << rec->factorialIterative(2) << endl;
    cout << "factorialIterative(3): " << rec->factorialIterative(3) << endl;
    cout << "factorialIterative(4): " << rec->factorialIterative(4) << endl;
    
    cout << endl;
    
    cout << "factorialRecursive(1): " << rec->factorialRecursive(1) << endl;
    cout << "factorialRecursive(2): " << rec->factorialRecursive(2) << endl;
    cout << "factorialRecursive(3): " << rec->factorialRecursive(3) << endl;
    cout << "factorialRecursive(4): " << rec->factorialRecursive(4) << endl;
    
    cout << "\n\nDONE WITH FACTORIALS, TRIANGLES AND WHATNOT\n\n";
    
    rec->binarySearchIterative(5,2,1,100,1);
    rec->binarySearchRecursive(5,2,1,100,1);
    
    cout << "\n\nDONE WITH BINARY SEARCH\n\n";
    
    rec->compoundInterestIterative(200.00, 5, 20);
    rec->compoundInterestRecursive(200.00, 5, 20, 1, 0, 0, 0);
    
    cout << "\n\nDONE WITH ALL.\n\n";
}
