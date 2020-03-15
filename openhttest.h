//
//  openhttest.h
//  Hashing
//
//  Created by Nicole Zhang on 2020-02-08.
//  Copyright © 2020 Nicole Zhang. All rights reserved.
//

#ifndef openhttest_h
#define openhttest_h
#include <string.h>
#include <iostream>
using namespace std;
class HashNode {
public:
    unsigned long long key {};
    string value {};
    HashNode(){
        key = 0;
        value = "";
    };
    
};

class openAddr{
public:
    HashNode **HashTable;
    int size {};
    int currentSize{0};
    openAddr() {
        HashNode();
        size = 0;
    };
    ~openAddr();
    string initSize (double m);
    string insertEntry (unsigned long long int key, string value);
    string deleteEntry (unsigned long long key);
    int searchTable (unsigned long long key);
    int hashFunc (unsigned long long key);
};

#endif /* openhttest_h */

