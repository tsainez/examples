//
//  DoubleLinkedEndedPriorityQueue.cpp
//
//  Created by Anthony Sainez on 1 November 2019
//  Copyright © 2020 Anthony Sainez. All rights reserved.
//

#include <iostream>
using namespace std;

class DoubleEndedList {
	private:
	Link *pFirst;
	Link *pLast; // ptr to first link on list

	public:
	DoubleEndedList() {pFirst = NULL; pLast = NULL; } // nothing on the list yet
	void displayFirst() { cout << "First: "; pFirst->display(); }
	void displayLast() 	{ cout << "Last: "; pLast->display(); }

	void displayList() {
		Link *current = pFirst;
		cout << "Begin list: \n"; // display format by gabriel
		cout << "{ data\t:\t\t\tpPrev\t\t\tself\t\t\t\tpNext\t\t}\n";
		while (current!=NULL) {
			current->display();
			current = current->pNext;
		}
		cout << "/End List" << endl;
		displayFirst();
		displayLast();
		cout << endl;
	}

	void displayBackward() {
		Link *current = pLast;
		cout << "end: \n";
		cout << "{ data\t:\t\t\tpPrev:\t\t\tself\t\t\t\tpNext\t\t}\n";
		while(current != NULL) {
			current->display();
			current = current->pPrev;
		}
		cout << "Begin " << endl;
		displayFirst();
		displayLast();
		cout << endl;
	}

	void insert(int newValue) {
		Link *newLink = new Link(newValue); 

		// if no links
		if (pFirst == NULL) {
			cout << "Inserting the first and last link: \n";
			newLink->display();
			cout << endl;
			newLink->pNext = NULL;
			newLink->pPrev = NULL;
			pFirst = newLink;
			pLast = newLink;
			return;
		} //endif

		if (newValue < pFirst->data) {
			cout << "Inserting new First link: \n";
			newLink->display();
			pFirst->pPrev = newLink; // #1
			newLink->pPrev = NULL;		// #2
			newLink->pNext = pFirst; // #3
			pFirst = newLink;
			return;
		} //endif

		if (newValue > pLast->data ) {
			cout << "Inserting new Last Link: \n";
			newLink->display();
			pLast->pNext = newLink; // #1
			newLink->pPrev = pLast; // #2
			newLink->pNext = NULL; // #3
			pLast == newLink;
			return;
		}

		cout << "Inserting somewhere between first and last the new link: \n";
		newLink->display();

		Link *Next = pFirst;
		while (Next != pLast) { // stop at next where new value < data
			if (newValue < Next->data)
				break;
			Next = Next->pNext; // that's confusing but ok
		}
		newLink->pNext = Next;			//#1
		newLink->pPrev = Next->pPrev; // step 2
		Next->pPrev->pNext = newLink;
		Next->pPrev = newLink;
	}

	void removeFirst() {
		cout << "Removing First:\n";

		Link *toDelete = pFirst;
		pFirst = pFirst->pNext;
		pFirst->pPrev = NULL;
		delete toDelete;
	}

	void removeLast() {
		cout << "Removing last:\n";

		Link *toDelete = pLast;
		pLast = pLast->pPrev;
		pLast->pNext = NULL;
		delete toDelete;
	}

};

class Link {
public:
	int data;
	Link *pNext, *pPrev;
	Link (int newData) { data = newData; pNext = NULL; pPrev = NULL; }
	void display() {
		// shows memory address of previous and next pointers, as well as next
		cout << "{ " << setw(3) << data << "\t:\t"
			 << setw(14) << pPrev << "\t:\t\t" << &data
			 << "\t:\t" << setw(14) << pNext << " }\n";
	}
};
