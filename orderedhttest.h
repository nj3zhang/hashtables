#ifndef orderedhttest_h
#define orderedhttest_h

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
class Node {
    public:
    Node *next {nullptr};
    Node *prev {nullptr};
    unsigned long long int key;
    string value;
};

class linkedlist {
    public:
    Node *list_head {nullptr};
    Node *list_tail {nullptr};
    int list_size {0};
    void enqueue_back (unsigned long long int key, string value);
    void enqueue_front (unsigned long long int key, string value);
    void dequeue_front();
    void dequeue_back();
    void searchInsert (unsigned long long int key, string value);
    bool isDuplicate (unsigned long long int key);
    Node* searchKey (unsigned long long int key);
   ~linkedlist();
};

class chaining {
public:
    int size {0};
    int currentSize{0};
    vector <linkedlist*> HashTable;

//    chaining();
    ~chaining();
    string initSize (double m);
    string insertEntry (unsigned long long int key, string value);
    string deleteEntry (unsigned long long key);
    string searchTable (unsigned long long key);
    string printList (int index);
};

#endif /* orderedhttest_h */

