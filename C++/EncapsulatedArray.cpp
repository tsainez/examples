#include <iostream>
using namespace std;

class EncapsulatedArray {
	private:
		int *array; // dynamically allocated array;
		int number_of_elements;
	public:
		EncapsulatedArray(int size);
		void add(int number_to_add);
		void show();
		void deleteNumber(int number_to_delete);
		void insertFirst(int number_to_insert);
};

EncapsulatedArray::EncapsulatedArray(int size) {
	array = new int[size]; // dynamic
	number_of_elements = 0;
}

void EncapsulatedArray::add(int number_to_add) {
	array[number_of_elements] = number_to_add;
	number_of_elements++;
}

// format {x, y, z}
void EncapsulatedArray::show() {
	if(number_of_elements == 1) {
		cout << "array = {" << array[0] << "}\n";
		return; // return is put here so that the function does not continue
	}

	int i;
	cout << "array = {";
	for (i=0; i < number_of_elements-1; i++)
		cout << array[i] << ", ";
	cout << array[i] << "}\n ";
}

void EncapsulatedArray::deleteNumber(int number_to_delete) {
	// find index to delete
	int index_to_delete;
	for (index_to_delete=0; index_to_delete<number_of_elements-1; index_to_delete++)
		if (array[index_to_delete] == number_to_delete)
			break; // stop when you find it

	if (index_to_delete == number_of_elements-1) // if number isn't found
		return; // leave

	// shift left all elements to right of index_to_delete starting leftmost
	for (int i = index_to_delete; i < number_of_elements-1; i++)
		array[i] = array[i+1];

	number_of_elements--; // resize 
}

void EncapsulatedArray::insertFirst(int number_to_insert) {
	// shift right all elements to the right of index 0 starting rightmost
	for (int i = number_of_elements-1; i>=0; i--)
		array[i+1] = array[i];
	array[0] = number_to_insert;

	number_of_elements++; // resizing
}


int main() {
	EncapsulatedArray anArray(5);
	anArray.add(9);
	anArray.show();
	anArray.add(101);
	anArray.add(9);
	anArray.show();
	anArray.deleteNumber(101);
	anArray.show();
	anArray.insertFirst(50);
	anArray.show();
}

/* test run results
array = {9}
array = {9, 101, 9}
 array = {9, 9}
 array = {50, 9, 9}
 [Finished in 0.3s]
 */