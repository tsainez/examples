//
//  ItemBag.cpp
//
//  Created by Anthony Sainez on 1 November 2019
//  Copyright © 2020 Anthony Sainez. All rights reserved.
//

#include <iostream>
using namespace std;

/**
 * Represents an item with a name and a cost.
 */
class Item {
private:
    /** The name of the item. */
    string name;
    /** The cost of the item. */
    double cost;
public:
    /**
     * Default constructor.
     * Initializes an empty item with cost 0.0.
     */
    Item() {
        name = "";
        cost = 0.0;
    }

    /**
     * Parameterized constructor.
     *
     * @param newName The name of the new item.
     * @param newCost The cost of the new item.
     */
    Item(string newName, double newCost) {
        name = newName;
        cost = newCost;
    }

    /**
     * Displays the item's details to stdout.
     */
    void show() { cout << "- " << name << " $" << cost << endl; }

    /**
     * Gets the name of the item.
     * @return The item's name.
     */
    string get_name() { return name; }

    /**
     * Gets the cost of the item.
     * @return The item's cost.
     */
    double get_cost() { return cost; }

    /**
     * Sets the item's properties.
     *
     * @param newName The new name for the item.
     * @param newCost The new cost for the item.
     */
    void set_item(string newName, double newCost) {
        name = newName;
        cost = newCost;
    }

    /**
     * Copies properties from another item.
     *
     * @param item The item to copy from.
     */
    void setItem(Item item) { // set item but replace with new item, different function
        name = item.get_name();
        cost = item.get_cost();
    }
};

/**
 * Represents a bag that can hold a collection of Items.
 */
class Bag {
private:
    /** Array of items in the bag. */
    Item *items;
    /** Current number of items in the bag. */
    int number_items;
    /** Maximum capacity of the bag. */
    int max;

public:
    /**
     * Constructor.
     *
     * @param Max The maximum number of items the bag can hold.
     */
    Bag(int Max) {
        items = new Item[Max]; // an array of items
        number_items = 0; // index of cur item
        max = Max; // size of bag/array
    }

    /**
     * Inserts a new item into the bag using name and cost.
     *
     * @param name The name of the item.
     * @param cost The cost of the item.
     */
    void insert_item(string name, double cost) {
        items[number_items].set_item(name, cost);
        number_items++;
    }

    /**
     * Inserts an existing Item object into the bag.
     *
     * @param item The Item object to insert.
     */
    void insertItem(Item item) {
        // items[number_items].set_item( item.get_name(), item.get_cost() );
        items[number_items].setItem(item);
        number_items++;
    }

    /**
     * Gets the capacity of the bag.
     * @return The maximum number of items.
     */
    int size() { return max; }

    /**
     * Displays all items in the bag.
     */
    void showItems() {
        for (int i = 0; i < number_items; i++)
            items[i].show();
    }

    /**
     * Deletes the first item in the bag and shifts remaining items.
     */
    void delete_first() {
        // shift all one to left
        for (int i = 0; i < max-1; i++) {
            items[i] = items[i+1];
        }
        number_items--; // resize bag
    }

    /**
     * Checks if the bag contains an item with a specific name.
     *
     * @param name_to_find The name to search for.
     * @return true if found, false otherwise.
     */
    bool contains(string name_to_find) {
        for (int i = 0; i < number_items; i++) {
            if (name_to_find == items[i].get_name())
                return true;
        }

        return false;
    }

    /**
     * Sorts the items in the bag by cost in ascending order.
     */
    void sort_by_cost_ascending() {
        for (int i = 0; i < number_items-1; i++) {
            for (int j = 0; j < number_items-1; i++) {
                if (items[j].get_cost() > items[j+1].get_cost())
                    swap(j,j+1);
            }
        }
    }

    /**
     * Swaps two items in the bag given their indices.
     *
     * @param index1 Index of the first item.
     * @param index2 Index of the second item.
     */
    void swap(int index1, int index2) {
        Item temp = items[index1];
        items[index1] = items[index2];
        items[index2] = temp;
    }

    /// requirements
    /**
     * Finds and displays the most expensive item in the bag.
     */
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

    /**
     * Displays items in reverse order.
     */
    void show_reverse() {
        for (int i = number_items-1; i>0; i++) {
            items[i].show();
        }
    }

    /**
     * Counts and displays the frequency of a specific item in the bag.
     *
     * @param item The item to count.
     */
    void get_frequency(Item item) {
        int count = 0;
        for (int i = 0; i < number_items; i++) {
            if (items[i].get_name() == item.get_name() )
                count++;
        }

        cout << "\nThere are " << count << " ";
        cout << item.get_name() << "'s";
    }

    /**
     * Deletes a specific item from the bag.
     *
     * @param item The item to delete (matched by name).
     * @return true if deleted successfully, false if not found.
     */
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

    /**
     * Gets the index of a specific item.
     *
     * @param item The item to find.
     * @return The index of the item, or the loop limit if not found (needs improvement).
     */
    int get_index_of(Item item) {
        for (int i = 0; i < number_items; i++) {
            if (items[i].get_name() == item.get_name() )
                return i;
        }
    }

    /**
     * Calculates the total cost of all items in the bag.
     * @return The sum of all item costs.
     */
    double sum_of_all() {
        double sum=0;
        for (int i = 0; i < number_items; i++)
            sum += items[i].get_cost();
        return sum; // that was easy
    }
};


/**
 * Main function to test Item and Bag classes.
 */
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
