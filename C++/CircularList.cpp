#include <iostream>
using namespace std;

class Link {
public:
	int iData;
	Link *pNext;

	Link(int newData) {
		iData = newData;
		pNext = NULL;
	}

	void show() {
		cout << "{ " << iData << "} "; 
	}
};

class CircList {
private:
	Link *pCurrent;
	int numLinks;
public:
	CircList() {
		pCurrent = NULL; // none yet
		numLinks = 0;
	}

	void showCurrent() {
		cout << "current iData = " << pCurrent->iData;
	}

	void num_links() {
		cout << "numLinks = " << numLinks << endl;
	}

	void displayList() {
		cout << "\nShowing entire list: ";
		for (int countLinks = 0; countLinks < numLinks; countLinks++) {
			pCurrent->show();
			pCurrent = pCurrent->pNext;
		}
	}

	bool search(int value) {
		for (int countLinks = 0; countLinks < numLinks; countLinks++) {
			if (pCurrent->iData == value)
				return true; // found it!
			pCurrent = pCurrent->pNext;
		}
		return false; // for statement didn't find it, it's not here!
	}

	void insertAfterValueFound(int newValue, int valueToFind) {
		// no links? make current equal to new link
		Link *newLink = new Link(newValue);

		if (numLinks == 0) {
			cout << "Inserting " << newValue << " as first link." << endl;
			pCurrent = newLink; // make pCurrent equal to newLink
			pCurrent->pNext=pCurrent; // only one link that points to itself
			numLinks++;
			return; // path for this route ends here, return void.
		}

		// dont insert if valuetofind isn't found
		if (!search(valueToFind)) {
			cout << "Couldn't find, not inserting.";
			return;
		}
        
		cout << "\nInserting " << newValue << " after the link: ";
		pCurrent->show();

		newLink->pNext = pCurrent->pNext;
		pCurrent->pNext = newLink;
		numLinks++;
	}

	bool deleteLink(int value) {
		// do nothing if there is nothing there
		if (numLinks == 0)
			return false; // no links, nothing to delete. therefore couldn't complete operation

		// if value is found
		if( search(value)) {
			// only one link? make current and current.next = null. link list is now empty
			if (numLinks == 1) {
				pCurrent->pNext = NULL;
				pCurrent = NULL;
				return true; // empty list now.
			} else { // there is more than one link in the list, it won't empty
				Link *toDelete = pCurrent;
				int countLinks;

				// stop toDelete One link before link to delete
				for (countLinks=0; countLinks<numLinks; countLinks++) {
					if (toDelete->pNext->iData == value)
						break;
					toDelete = toDelete->pNext;
				}
				if(countLinks == numLinks) // didn't find the link
					return false; 

				// to delete is link 1
				// todelete.next is link2 which is what we delete
				// to delete next next is link3
				pCurrent = toDelete->pNext; // store link2 in pCur
				toDelete->pNext = toDelete->pNext->pNext; // point l1 to l3
				toDelete = pCurrent;
				delete toDelete;

				pCurrent = pCurrent->pNext;
				numLinks--;
				return true;
			}
		}
		return false;
	}

}; // class circle list

int main() {
	CircList *aCircList = new CircList(); // empty
	aCircList->insertAfterValueFound(10, 0);
	aCircList->num_links();
	aCircList->showCurrent();

	cout << "\nThe value " << 10 << " was found: ";
	cout << aCircList->search(10) << endl;
	cout << "The value " << 11 << " was found: ";
	cout << aCircList->search(11) << endl;
	aCircList->showCurrent();
	aCircList->displayList();
	aCircList->insertAfterValueFound(20, 10);
	aCircList->displayList();
	aCircList->insertAfterValueFound(15, 10);
	aCircList->displayList();
	aCircList->insertAfterValueFound(30, 20);
	aCircList->displayList();
	aCircList->insertAfterValueFound(45, 30);
	aCircList->displayList();
	cout << "\nTrying to delete 99: \n";
	cout << aCircList->deleteLink(99);
	aCircList->displayList();
	cout << "\nTrying to delete 30: \n";
	cout << aCircList->deleteLink(30);
	aCircList->displayList();
	cout << "\nTrying to delete 45: \n";
	cout << aCircList->deleteLink(45);
	aCircList->displayList();
	cout << "\nTrying to delete 20: \n";
	cout << aCircList->deleteLink(20);
	aCircList->displayList();
	cout << "\nAgain, trying to delete 20: \n";
	cout << aCircList->deleteLink(20);
	aCircList->displayList();
	aCircList->insertAfterValueFound(15, 10);
	aCircList->displayList();
}

/* test run
Inserting 10 as first link.
numLinks = 1
current iData = 10
The value 10 was found: 1
The value 11 was found: 0
current iData = 10
Showing entire list: { 10} 
Inserting 20 after the link: { 10} 
Showing entire list: { 10} { 20} 
Inserting 15 after the link: { 10} 
Showing entire list: { 10} { 15} { 20} 
Inserting 30 after the link: { 20} 
Showing entire list: { 20} { 30} { 10} { 15} 
Inserting 45 after the link: { 30} 
Showing entire list: { 30} { 45} { 10} { 15} { 20} 
Trying to delete 99: 
0
Showing entire list: { 30} { 45} { 10} { 15} { 20} 
Trying to delete 30: 
1
*/
