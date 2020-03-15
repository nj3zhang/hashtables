#include <string.h>
#include <math.h>
#include <fstream>
#include "chaining.cpp"

using namespace std;
void parseEntryValues(string values, string &key, string &id);

int main (){
    ifstream file;
    string line {};
    file.open("test1.in");
    
    chaining HashTableC;
    while (getline(file, line)){
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
            message = HashTableC.initSize(size);
        } else if (command == "i"){
           if(key.length() != 10){
                throw "error";
            }
            try {
                if(id == ""){
                    throw "error";
                }
                message = HashTableC.insertEntry(valid_key, id);
            } catch (...) {
                message = "";
            }
        } else if (command == "s") {
            message = HashTableC.searchTable(valid_key);
        } else if (command == "d"){
            message = HashTableC.deleteEntry(valid_key);
        } else if (command == "p"){
            int index = stoi (key);
            message = HashTableC.printList(index);
        }
        } catch(const char *msg) {
            message = "";
            //cout << "error" << endl;
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

