//
// linkedlist.c
//
// Created by Anthony Sainez on 3 February 2020
// Copyright © 2020 Anthony Sainez. All rights reserved.
//

struct node {
    char *value;
    struct node *next;
};

// typedef means define a new type, like 'alias'
typedef struct node NodeStruct;

/*
 alternatively, you could do...
 
 struct Node {
     char *value;
     struct Node *next;
 } NodeStruct;
 
 then...
 
 typedef NodeStruct *List;
 typedef char *String;
 */

/*
List cons(String s, List List) {
    List node = (List) malloc(sizeof(NodeStruct)); // List is a NodeStruct pointer type
    
    node->value = (String) malloc (strlen(s) + 1); // String is a char pointer type
    strcpy(node->value, s);
    node->next = list;
    return node;
}
 */

int main() {
    /*
    String s1 = "abc", s2 = "cde";
    List theList = NULL;
    theList = cons(s2, theList);
    theList = cons(s1, theList);
     */
}
