#ifndef chaining_cpp
#define chaining_cpp
#include <stdio.h>
#include "orderedhttest.h"

int hash1 (unsigned long long int key, int size);
int hash1 (unsigned long long int key, int size) {
    return key % size;
}
linkedlist::~linkedlist(){
     Node *temp {nullptr};
        
        if (list_size == 1){
            delete list_head;
            list_head = nullptr;
            list_tail = nullptr;
        } else {
            while (list_head != nullptr) {
                temp = list_head -> next;
                delete list_head;
                list_head = temp;
            }
            list_tail = nullptr;
        }
        temp = nullptr;
        list_size = 0;
}

Node* linkedlist::searchKey (unsigned long long int key) {
    Node *temp = list_head;
        while (temp != nullptr) {
        if (temp -> key == key){
            return temp;
        } else {
            temp = temp -> next;
        }
    }
    return nullptr;
}
bool linkedlist::isDuplicate(unsigned long long int key) {
    Node *temp = list_head;
    while (temp){
        if(temp->key == key) {
            return true;
        }
        temp = temp->next;
    }
    delete temp;
    return false;
}

void linkedlist::searchInsert(unsigned long long key, string value) {
    // Search
    Node *temp = list_head;
    Node *current = new Node;
    current -> key = key;
    current -> value = value;
    if (temp -> key < key && temp -> next -> key > key){
        current -> next = temp -> next;
        current -> prev = temp;
        if (temp -> next != nullptr) {
            temp->next->prev = current;
        }
        temp -> next = current;
        list_size += 1;
    } else {
        temp = temp -> next;
    }
}
void linkedlist::enqueue_front(unsigned long long key, string value) {
    Node *current = new Node;
    current -> key = key;
    current -> value = value;
    if (list_head == nullptr) {
        current -> next = list_head;
        list_head = current;
        list_tail = current;
    } else {
        current -> next = list_head;
        list_head -> prev = current;
        list_head = current;
    }
    list_size += 1;
};
void linkedlist::enqueue_back(unsigned long long key, string value){
    Node *current = new Node;
    current -> key = key;
    current -> value = value;
    if (list_tail == nullptr) {
        list_tail = current;
        list_head = current;
    } else{
        current -> prev = list_tail;
        list_tail -> next = current;
        list_tail = current;
    }
    list_size += 1;
}
void linkedlist::dequeue_front() {
    if (list_size == 1 || list_head == list_tail) {
        delete list_head;
        list_head = nullptr;
        list_tail = nullptr;
    } else {
        Node *temp {nullptr};
        temp = list_head->next;
        delete list_head;
        list_head = temp;
        list_head -> prev = nullptr;
    }
    list_size -= 1;
}
void linkedlist::dequeue_back() {
    // if its the last entry, set both pointers to null
    if (list_tail == list_head) {
        delete list_head;
        list_head = nullptr;
        list_tail = nullptr;
    } else {
        Node *temp = list_tail -> prev;
        delete list_tail;
        list_tail = temp;
        list_tail -> next = nullptr;
    }
    list_size -= 1;
}

chaining::~chaining(){
    for (int i = 0; i < size; i++){
           if(HashTable[i] != nullptr){
               delete (HashTable[i]);
               HashTable[i] = nullptr;
           }
       }
    HashTable.clear();
}
/*
 Initialize size of the table, sets all entries to null
 */
string chaining::initSize(double m){
    size = m;
    HashTable.resize(size);
    if(currentSize != 0){
        for (int i = 0; i < size; i++){
            if(HashTable[i] != nullptr){
                delete (HashTable[i]);
                HashTable[i] = nullptr;
            }
        }
        HashTable.clear();
    }
    for (int i = 0; i < size; i++){
        linkedlist *empty = new linkedlist;
        HashTable[i]=empty;
    }
    return string("success");
}

/*
 Insert entry into the hash table
 Hash the key to find the index
 Insert to the linked list (ordered)
 */
string chaining::insertEntry(unsigned long long key, string value){
    int index = hash1(key, size);
    if(size == 0){
        return string("failure");
    }
    if (HashTable[index] != nullptr && HashTable[index]->isDuplicate(key)){
        return string("failure");
    }
    // Insert at the back if list is empty or if the last entry is smaller than the key to be inserted
    if (HashTable[index]->list_size == 0 || HashTable[index]->list_tail->key < key){
        HashTable[index]->enqueue_back(key, value);
    } else if (HashTable[index]->list_head->key > key) {
        //enqueue front
        HashTable[index]->enqueue_front(key, value);
    } else {
        // The entry must be inserted in the middle
        HashTable[index]->searchInsert(key, value);
    }
    currentSize+=1;
    return string("success");
}
/*
 Searches throught the table for the key
 Hash the key to find index in the table
 Linearly search through linked list to locate entry
 */
string chaining::searchTable(unsigned long long key) {
    if (size == 0){
        return string("not found");
    }
    int index = hash1(key, size);
    Node* result = HashTable[index]->searchKey(key);
    string message {""};
    if (result != nullptr){
        message = "found " + result->value + " in " + to_string(index);
    } else {
        message = "not found";
    }
    return message;
}

string chaining::deleteEntry(unsigned long long key){
    int index = hash1(key, size);
    Node* result = HashTable[index]->searchKey(key);
    if (result == nullptr){
        return string ("failure");
    } else if (result -> next == nullptr) {
        //either deleting the back node or the last node left in the list
        HashTable[index]->dequeue_back();
    } else if (result -> prev == nullptr) {
        HashTable[index]->dequeue_front();
    } else {
       // delete in the middle
        result -> next -> prev = result -> prev;
        result -> prev -> next = result -> next;
        delete result;
        result = nullptr;
    }
    currentSize -= 1;
    return string("success");
}
string chaining::printList(int index){
    string message{""};
    if (HashTable[index] != nullptr && HashTable[index]->list_head != nullptr) {
       Node *result = HashTable[index]->list_head;
        while (result != nullptr) {
            string p_key = to_string(result -> key);
            // If the number had 0s in front, concat them back and print
            while (p_key.length() < 10) {
                p_key = "0" + p_key;
            }
            message += to_string(result -> key);
            if (result -> next != nullptr){
                message += " ";
            }
            result = result ->next;
        }
    }
    return message;
}
#endif

