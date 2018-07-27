//
//  ChainHashTable.hpp
//  CMSC 341 Proj5
//
//  Created by Pearl Pongsuppat on 5/6/18.
//  Copyright © 2018 Pearl Pongsuppat. All rights reserved.
//

#ifndef ChainHashTable_hpp
#define ChainHashTable_hpp

#include <iostream>
#include <list>
#include "HashTable.h"
using namespace std;

template <typename T>
class ChainHashTable : public HashTable<T> {

public:
    
    //These are the default constructors for your two hash table classes. The parameter
    //hashFunc is a pointer to the function that should be used to generate hash codes for the
    //data type T. The parameter n is the requested size of the hash table. We chose 101 as
    //the default value because it is a nice prime number.
     ChainHashTable(unsigned int (*hashFunc)(const T&), int n=101);
    
    //Default Constructors
     virtual ~ChainHashTable();
    
    //Copy Constructor
     ChainHashTable (ChainHashTable& other);
    
    //Overloaded Assignment Operator
    const ChainHashTable& operator= (ChainHashTable& rhs);
    
    //This function inserts data into the hash table. It returns true if data was new and
    //inserted. if data is already in the hash table, it is left as-is, and the function
    //returns false
     virtual bool insert(const T &data);
    
    //The find() function looks for data in the hash table. The function returns true if
    //found, false otherwise.
     virtual bool find(const T &data);
    
    //The remove() function removes data from the hash table if it is found, and returns it,
    //setting found to true. If data is not in the hash table, remove() returns with found set
    //to false
    virtual T remove(const T &data, bool &found);
    
     //dump() function does the usual: print some vital statistics and the contents of the
    //hash table(s) to stdout.
     virtual void dump();
    
    //The at() function returns the number of items stored at the index slot of the hash
    //table. For ProbeHashTables, that would obviously be either 0 or 1
    virtual int at(int index, std::vector<T> &contents);

    
private:
   list <T> *m_table;
    int m_size;
    int totalItems;
};
#include "ChainHashTable.cpp"
#endif /* ChainHashTable_h */
