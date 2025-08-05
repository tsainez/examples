// Create a struct that holds an int and a pointer to another instance of the same struct. Write a function that takes the address of one of these structs and an int indicating the length of the list you want created. This function will make a whole chain of these structs (a linked list), starting from the argument (the head of the list), with each one pointing to the next. Make the new structs using new, and put the count (which object number this is) in the int. In the last struct in the list, put a zero value in the pointer to indicate that it’s the end. Write a second function that takes the head of your list and moves through to the end, printing out both the pointer value and the int value for each one.

#include <iostream>

struct Link {
    int data;
    struct Link* next;
};

// Creating a linked list. Based partly off previous work done in CSE 030.
void linkedList(struct Link* head, int n) {
    struct Link* temp = head;

    // Iterate the length
    for (int i = 1; i <= n; i++) {
        Link* link = new Link();
        link->next = NULL;
        link->data = i;

        // Is the head empty?
        if (i == 1) {
            head->data = i;
        }
        else {
            // Go until the last node
            while (temp->next != NULL) {
                temp = temp->next;
            }

            // Copy the node at the end
            temp->next = link;
        }
    }
}

void display(struct Link* head) {
    struct Link* temp = head;

    std::cout << "Address" << "\t\t" << "Data" << std::endl;

    //iterate throught each node
    while (temp != NULL) {
        std::cout << temp << "\t" << temp->data << std::endl;
        temp = temp->next;
    }
}

int main() {
    Link* head = new Link();

    //call the function to make linked list of argument number node
    linkedList(head, 5);

    //call the function display() to display linked list
    display(head);
}