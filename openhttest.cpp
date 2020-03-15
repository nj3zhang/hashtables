#include <iostream>
#include <fstream>
#include <string.h>
#include "openhttest.h"
#include <math.h>
using namespace std;
void parseEntryValues(string values, string &key, string &id);
int hash1 (unsigned long long int key, int size);
int hash2 (unsigned long long int key, int size);

//Destructor
openAddr::~openAddr(){
    for (int i = 0; i < size; i++){
        if(HashTable[i] != nullptr){
            HashTable[i] -> key = 0;
            HashTable[i] -> value = "";
            delete (HashTable[i]);
        }
    }
    delete[] HashTable;
}

//Initialize
string openAddr::initSize (double m) {
    size = m;
    if (currentSize != 0){
	for (int i = 0; i < size; i++){
        if(HashTable[i] != nullptr){
            HashTable[i] -> key = 0;
            HashTable[i] -> value = "";
            delete HashTable[i];
        }
    }
		delete[] HashTable;
    }
    HashTable = new HashNode* [size]{};
    for (int i = 0; i < size; i++){
        HashTable [i] = nullptr;
    }
    return string("success");
};

string openAddr::insertEntry(unsigned long long int key, string value) {
    int index = hashFunc (key);
    // return failure when inserting a duplicate or when the table is full
    if(index == -1 || currentSize == size) {
        return string("failure");
    }
    HashNode *entry = new HashNode;
    entry->key = key;
    entry->value = value;
    HashTable[index] = entry;
    currentSize += 1;
    return string("success");
};
int openAddr::searchTable(unsigned long long int key){
    int index = -1;
    index = hash1(key, size);
    //num of collisions
    int i = 0;
    // The iteration to find new index ends after checking all positions
    while (i < size){
        if (HashTable [index] && HashTable[index]->key == key){
            return index;
            }
            index = (hash1(key, size) + i * hash2(key, size)) % size;
        i++;
    }
    return -1;
};

string openAddr::deleteEntry(unsigned long long int key){
    int index = searchTable(key);
    if (index == -1){
        return string("not found");
    }
    HashTable[index]->key = 0;
    HashTable[index]->value ="";
    delete(HashTable[index]);
    HashTable[index] = nullptr;
    currentSize -= 1;
    return string("success");
}
/*
 Performs double hashing and returns the index in the table to insert to
 */
int openAddr::hashFunc (unsigned long long int key) {
    int index = -1;
    index =  hash1(key, size);
    //num of collisions
    int i = 0;
    // make sure to end iteration to find new index ends after checking all positions
    while (i < size){
        if (HashTable[index] == nullptr){
            return index;
        }
        // Duplicate
        if (HashTable[index]->key == key){
            index = -1;
            break;
        }
        index = (hash1(key, size) + i * hash2(key, size)) % size;
        i++;
    }
    return index;
}
int hash1 (unsigned long long int key, int size) {
    return key % size;
}
int hash2 (unsigned long long int key, int size) {
    int x = floor(key/size);
    int y = x % size;
    // If its even, add one to make it odd
    if (y % 2 == 0){
        y += 1;
    }
    return y;
}

int main() {
    string line {};
    openAddr HashTableO;
    while (getline(cin, line) && !cin.eof()){
        string command {line[0]};
        string values {""};
        string message {""};
        string key {};
        string id {};
        unsigned long long int valid_key {0};
        int lineLength = line.length();
        int i = 1;
        // ignore whitespace after command
        while (line[i] == ' '){
            i += 1;
        }
        while (i < lineLength) {
            values += line[i];
            i++;
        }
        // Parse values into key and id if its not null
        if (values != ""){
            parseEntryValues(values, key, id);
        }

        try {
            if (key != ""){
                valid_key = stol(key);
            }
            if (command == "n") {
                //define size
                int size = stoi(values);
                message = HashTableO.initSize(size);
            } else if (command == "i") {
                //insert
                if(key.length() != 10){
                    throw "error";
                }
                try {
                    if(id == ""){
                        throw "error";
                    }
                    message = HashTableO.insertEntry(valid_key, id);
                } catch (...) {
                    message = "";
                }
            } else if (command == "s") {
                if(key.length() != 10 || id != ""){
                    throw "error";
                }
                //search
                try {
                    int searchIndex = HashTableO.searchTable(valid_key);
                    if (searchIndex == -1) {
                        message = "not found";
                    } else {
                        message = "found " + HashTableO.HashTable[searchIndex]->value + " in " + to_string(searchIndex);
                    }
                } catch (...) {
                    message = "";
                }
            } else if (command == "d") {
                //delete
                message = HashTableO.deleteEntry(valid_key);
            }
        } catch(const char *msg) {
            message = "";
            cout << "error" << endl;
        }
        if(message != ""){
            cout << message << endl;
        }
    }
    return 0;
}
/*
 Parse the value to be added to the table
 Seperate the key and value
 Verify the validity of the value
 */
void parseEntryValues(string values, string &key, string &id) {
    int valuesLength = values.length();
    int i = 0;
    while(i < valuesLength && values[i]!=';' && values[i] != ' ') {
        key += values[i];
        i++;
    }
    i += 1;
    while (i < valuesLength) {
        id += values[i];
        i++;
    }
}

