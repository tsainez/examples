#include <iostream>
using namespace std;

class Link {
	public:
		int 	iData; // data
		double 	dData; // data
		Link 	*pNext; // pointer to next Link

		Link(int id, double dd) {
			iData = id;
			dData = dd;
			pNext = NULL; // nothing! until connected
		}

		void displayLink() {
			cout << "{ " << iData << ", ";
			cout << dData << "} ";
		}
		
};

class LinkList {
	private:
		Link *pFirst; // ptr to first link on list

	public:
		LinkList() {
			pFirst = NULL; // nothing there yet
		}

		bool isEmpty() {
			return pFirst == NULL; // true if list is empty
		}

		// other methods go here
		void insertFirst(int id, double dd) {
			Link *pNewLink = new Link(id, dd); // new link
			pNewLink->pNext = pFirst;
			pFirst = pNewLink; 
		}

		Link *getFirst() { 
			return pFirst; 
		}

		void removeFirst() {// delete first
			Link *pTemp = pFirst;
			pFirst = pFirst->pNext;
			delete pTemp;
		}

		void displayList() {
			cout << "List (first-->last): "; // give format
			Link *pCurrent = pFirst; // start at beginning
			while (pCurrent != NULL) {// until the end
				pCurrent->displayLink(); // show me!
				pCurrent = pCurrent->pNext; // move to next link
			}

			cout << endl;
		}

		Link *find(int key) {// find link given key
			Link *pCurrent = pFirst;
			while (pCurrent->iData != key) { // until we find it
				if (pCurrent->pNext == NULL) // end of list
					return NULL; // couldn't find it
				else
					pCurrent = pCurrent->pNext;
			}
			return pCurrent;
		}

		bool remove(int key) {
			Link *pCurrent = pFirst; // assuming not empty...
			Link *pPrevious = pFirst;
			while (pCurrent->iData != key) { // looking
				if (pCurrent->pNext == NULL)
					return false; // can't find it
				else {
					pPrevious = pCurrent; // go to the next
					pCurrent = pCurrent->pNext;
				}
			}
			// found it!
			if (pCurrent == pFirst) // if first link
				pFirst = pFirst->pNext; // change first
			else
				pPrevious->pNext = pCurrent->pNext; // bypass current

			delete pCurrent;
			return true; // as in: yes we did delete it
		}

		int sumIdata() {
			int sum = 0;
			Link *pCurrent = pFirst;

			while ( !(pCurrent==NULL) ) {
				sum += pCurrent->iData;
				pCurrent = pCurrent->pNext;
			}
			// sum += pCurrent->iData;
			return sum;
		}

		int min(){ 
			Link *pCurrent = pFirst;
			int min = pFirst->iData;
			while ( !(pCurrent==NULL) ) {
				if (pCurrent->iData < min)
					min = pCurrent->iData;
				pCurrent = pCurrent->pNext;
			}
			return min;
		}

		int numLinks() {
			Link *pCurrent = pFirst;
			int count = 0;
			while ( !(pCurrent==NULL) ) {
				count++;
				pCurrent = pCurrent->pNext;
			}
			return count;
		}
};

int main() {
	LinkList theList; // make new list
	theList.insertFirst(22, 2.99);
	theList.insertFirst(44, 4.99);
	theList.insertFirst(66, 6.99);
	theList.insertFirst(88, 8.99);

	theList.displayList(); // show the list

	while (!theList.isEmpty()) {
		Link *pTemp = theList.getFirst(); // get first link
		cout << "\nRemoving link with data";
		pTemp->displayLink(); // display links data
		theList.removeFirst(); // remove it
	}

	cout << endl << "empty list: ";
	theList.displayList(); // list (first --> last)

	theList.insertFirst(22, 2.99); // reinsert 4 items
	theList.insertFirst(44, 4.99);
	theList.insertFirst(66, 6.99);
	theList.insertFirst(88, 8.99);
	cout << "\nReinserting the links back" << endl;
	theList.displayList();

	int findKey = 44;
	Link *pFind = theList.find(findKey);
	if (pFind != NULL)
		cout << "Found link with key: " << pFind->iData << endl;
	else
		cout << "Can't find link with key " << findKey << endl;

	if (theList.remove(findKey))
		cout << "Deleted " << findKey << " from the list.\n";
	else
		cout << "Did not delte " << findKey << " from the list.\n";

	cout << "Link list after deletion\n";
	theList.displayList();

	cout << "\nThe sum of all links is" << theList.sumIdata() << endl;
	cout << "The smallest link is: " << theList.min() << endl;
	cout << "The number of links is: " << theList.numLinks() << endl;
}

/*  TEST RUN

List (first-->last): { 88, 8.99} { 66, 6.99} { 44, 4.99} { 22, 2.99} 

Removing link with data{ 88, 8.99} 
Removing link with data{ 66, 6.99} 
Removing link with data{ 44, 4.99} 
Removing link with data{ 22, 2.99} 
empty list: List (first-->last): 

Reinserting the links back
List (first-->last): { 88, 8.99} { 66, 6.99} { 44, 4.99} { 22, 2.99} 
Found link with key: 44
Deleted 44 from the list.
Link list after deletion
List (first-->last): { 88, 8.99} { 66, 6.99} { 22, 2.99} 

The sum of all links is176
The smallest link is: 22
The number of links is: 3
[Finished in 0.2s]
*/