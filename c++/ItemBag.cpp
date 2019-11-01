#include <iostream>
using namespace std;

class Item {
	private:
		string name;
		double cost;
	public:
		Item() {
			name = "";
			cost = 0.0;
		}

		Item(string newName, double newCost) {
			name = newName;
			cost = newCost;
		}

		void show() { cout << "- " << name << " $" << cost << endl; }

		string get_name() { return name; }
		double get_cost() { return cost; }

		void set_item(string newName, double newCost) {
			name = newName;
			cost = newCost;
		}

		void setItem(Item item) { // set item but replace with new item, different function
			name = item.get_name();
			cost = item.get_cost();
		}
};

class Bag {
	private:
		Item *items;
		int number_items;
		int max;

	public:
		Bag(int Max) {
			items = new Item[Max]; // an array of items
			number_items = 0; // index of cur item
			max = Max; // size of bag/array
		}

		void insert_item(string name, double cost) {
			items[number_items].set_item(name, cost);
			number_items++;
		}

		void insertItem(Item item) {
			// items[number_items].set_item( item.get_name(), item.get_cost() );
			items[number_items].setItem(item);
			number_items++;
		}

		int size() { return max; }

		void showItems() {
			for (int i = 0; i < number_items; i++)
				items[i].show();
		}

		void delete_first() {
			// shift all one to left
			for (int i = 0; i < max-1; i++) {
				items[i] = items[i+1];
			}
			number_items--; // resize bag
		}

		bool contains(string name_to_find) {
			for (int i = 0; i < number_items; i++) {
				if (name_to_find == items[i].get_name())
					return true;
			}

		return false;
		}

		void sort_by_cost_ascending() {
			for (int i = 0; i < number_items-1; i++) {
				for (int j = 0; j < number_items-1; i++) {
					if (items[j].get_cost() > items[j+1].get_cost())
						swap(j,j+1);
				}
			}
		}

		void swap(int index1, int index2) {
			Item temp = items[index1];
			items[index1] = items[index2];
			items[index2] = temp;
		}

		/// requirements
		void most_expensive() {
			int max_index = 0;
			for (int i = 1; i < number_items; i++) {
				if (items[i].get_cost() > items[max_index].get_cost() )
					max_index = i;
			}

		cout << "\n The most expensive item is: ";
		cout << items[max_index].get_name() << " $";
		cout << items[max_index].get_cost() << endl;
		}

		void show_reverse() {
			for (int i = number_items-1; i>0; i++) {
				items[i].show();
			}
		}

		void get_frequency(Item item) {
			int count = 0;
			for (int i = 0; i < number_items; i++) {
				if (items[i].get_name() == item.get_name() )
					count++;
			}

		cout << "\nThere are " << count << " ";
		cout << item.get_name() << "'s";
		}

		bool delete_item(Item item) {
			int index_to_delete; // find it!
			for (index_to_delete = 0; index_to_delete < number_items; index_to_delete++ ) {
				if (items[index_to_delete].get_name() == item.get_name())
					break; // you found it!
			}

			// you didn't find it?
			if (index_to_delete == number_items)
				return false; // sorry bud couldn't delete it

			// shift all elements left on top of index_to_delete
			for (int i = index_to_delete; i<number_items-1; i++)
				items[i] = items[i+1];

			number_items--; // resize
			return true; // you did it
		}

		int get_index_of(Item item) {
			for (int i = 0; i < number_items; i++) {
				if (items[i].get_name() == item.get_name() )
					return i;
			}
		}

		double sum_of_all() {
			double sum=0;
			for (int i = 0; i < number_items; i++)
				sum += items[i].get_cost();
			return sum; // that was easy
		}
};



int main() {
	// Test to see if it works!
	cout << "Testing Item: ";
	Item fujiApple("Fuji Apple", 4.99);
	fujiApple.show();

	int max_items_in_bag = 4;
	Bag bag(max_items_in_bag); // make a new mixed bag with 4 items

	cout << "\nAdded following items to the bag: \n";
	bag.insert_item("Oranges", 5.99);
	bag.insertItem(fujiApple); // already have one defined just place it in

	Item cheese("Cheese", 6.79);
	bag.insertItem(cheese);
	bag.insert_item("Olives", 4.49);
	bag.insert_item("Bananas", 0.79);
	bag.showItems();
	bag.most_expensive();
	bag.get_frequency(fujiApple);

	if (bag.delete_item(fujiApple) == true)
		cout << "\n\n" << fujiApple.get_name() << " deleted." << endl;
	else
		cout << "Could not delete item" << endl;

	cout << "\nAfter deleting fujiApple:\n";
	bag.showItems();
	cout << "\nThe index of Cheese is: " << bag.get_index_of(cheese) << endl;

	cout << "\nShow in reverse: " << endl;
	bag.show_reverse();
}
