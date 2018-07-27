
//  ProbHashTable.cpp
//  CMSC 341 Proj5
//
//  Created by Pearl Pongsuppat on 5/6/18.
//  Copyright © 2018 Pearl Pongsuppat. All rights reserved.
//

#ifndef ProbeHashTable_CPP
#define ProbeHashTable_CPP
#include <iostream>
#include <stdexcept>
#include "ProbeHashTable.h"

const int EMPTY = 0;
const int OCCUPIED = 1;
const int LAZY_DEL = -1;

//These are the default constructors for your two hash table classes. The parameter
//hashFunc is a pointer to the function that should be used to generate hash codes for the
//data type T. The parameter n is the requested size of the hash table. We chose 101 as
//the default value because it is a nice prime number.
template <typename T>
ProbeHashTable<T>::ProbeHashTable(unsigned int (*hashFunc)(const T&), int n){
    this->hashFunc = hashFunc;
    m_table = new HashTableEntry[n];
    totalItems = 0;
    m_probeSize = n;
    
}
    
//Destructors
template <typename T>
ProbeHashTable<T>::~ProbeHashTable(){
    delete [] m_table;
    m_table = NULL;
}
    
//Copy Constructor
template <typename T>
ProbeHashTable<T>::ProbeHashTable (ProbeHashTable& other){
     m_probeSize = other. m_probeSize;
    totalItems = other.totalItems;
   
    this->hashFunc = other.hashFunc;
    m_table = new HashTableEntry[other. m_probeSize];
    for(int i = 0; i < other. m_probeSize; i++){
        m_table[i].m_data = other.m_table[i].m_data;
        m_table[i].m_flag = other.m_table[i].m_flag;
    }
}
    
//Overloaded Assignment Operator
template <typename T>
const ProbeHashTable<T>& ProbeHashTable<T>::operator= (ProbeHashTable<T>& rhs){

    if(this != &rhs){
        
        delete [] m_table;
         m_probeSize = rhs. m_probeSize;
        totalItems = rhs.totalItems;
        
        this->hashFunc = rhs.hashFunc;
        m_table = new HashTableEntry[rhs.m_probeSize];
        for(int i = 0; i < rhs.m_probeSize; i++){
            
            m_table[i].m_data = rhs.m_table[i].m_data;
            m_table[i].m_flag = rhs.m_table[i].m_flag;
        
        }
    }
    return *this;
}
    
//This function inserts data into the hash table. It returns true if data was new and
//inserted. if data is already in the hash table, it is left as-is, and the function
//returns false.Throw exception
template <typename T>
bool ProbeHashTable<T>::insert(const T &data){

    unsigned int hashNum = this->hashFunc(data) % m_probeSize;
    int count = 0;
  
    if(totalItems ==  m_probeSize){
        throw out_of_range ( "Out of Range ");
    }
    
    if(find(data)){
 
        return 0;
    }
    
    //If the flag is set to empty or lazy delete then insert the data into
    //appropriate position
    if(m_table[hashNum].m_flag ==  EMPTY ||m_table[hashNum].m_flag == LAZY_DEL){
        m_table[hashNum].insert(data);
    }
    else{
        //Linear probe to find the next available position to insert.
        while(m_table[hashNum].m_flag == OCCUPIED && count <  m_probeSize){
            hashNum = (hashNum+1) %  m_probeSize;
            count++;
        }
        m_table[hashNum].insert(data);
    }
    totalItems++;
    return 1;
}
    
//The find() function looks for data in the hash table. The function returns true if
//found, false otherwise.
template <typename T>
bool ProbeHashTable<T>::find(const T &data){
    
    unsigned int hashNum = this->hashFunc(data) % m_probeSize;
    int num = 0;
  
    if(m_table[hashNum].m_flag == EMPTY){
        return 0;
    }

    if(m_table[hashNum].m_flag != EMPTY &&
       m_table[hashNum].m_flag != LAZY_DEL &&
       m_table[hashNum].m_data == data ){
        return 1;
        }
    
    else{
        while(num <  m_probeSize){
            if(m_table[hashNum].m_flag == EMPTY){
                return 0;
            }
            if(m_table[hashNum].m_flag == OCCUPIED){
                if(m_table[hashNum].m_data == data){
                return 1;
                }
            }
            hashNum = (hashNum + 1)% m_probeSize;
            num++;
        }
    }
    return 0;
}
    
//The remove() function removes data from the hash table if it is found, and returns it,
//setting found to true. If data is not in the hash table, remove() returns with found set
//to false
template <typename T>
T ProbeHashTable<T>::remove(const T &data, bool &found){
    
    int hashNum = this->hashFunc(data)% m_probeSize ;
    int num = 0;
    
    //If the data we want to remove is equal to the data at hashNum
    //and the flag is not marked as empty or lazy deleted then set
    //m_flag to -1 and found returns true.
    if(m_table[hashNum].m_data == data &&
       m_table[hashNum].m_flag != EMPTY &&
       m_table[hashNum].m_flag != LAZY_DEL){
        m_table[hashNum].m_flag = LAZY_DEL;
        found = true;
        totalItems--;
        return data;
    }
    
    else{
        
        //Linear probe to find the data we want to remove
        while(m_table[hashNum].m_data != data && num <  m_probeSize){
            hashNum = (hashNum + 1)% m_probeSize;
            if(m_table[hashNum].m_flag == EMPTY){
                found = false;
                return data;
            }
            
            if(m_table[hashNum].m_flag == OCCUPIED){
                if(m_table[hashNum].m_data == data){
                    m_table[hashNum].m_flag = LAZY_DEL;
                    found = true;
                    totalItems--;
                    return data;
                }
            }
            num++;
        }
    }
    
    found = false;
    return data;
}
    
//dump() function does the usual: print some vital statistics and the contents of the
//hash table(s) to stdout.
template <typename T>
void ProbeHashTable<T>::dump(){
    for(int i = 0; i <  m_probeSize; i++){
        cout << "[" << i << "]: ";
        if(m_table[i].m_flag == EMPTY){
            cout << "EMPTY \n";
        }
        else if(m_table[i].m_flag == OCCUPIED){
            int hashNum = this->hashFunc(m_table[i].m_data) %  m_probeSize;
            cout << m_table[i].m_data << "(" << hashNum << ")"<< endl;
        }
        else{
            cout << "DELETED\n";
        }
    }
    cout << "Total Items: " << totalItems << endl;
}
    
//The at() function returns the number of items stored at the index slot of the hash
//table. For ProbeHashTables, that would obviously be either 0 or 1
template <typename T>
int ProbeHashTable<T>::at(int index, std::vector<T> &contents){
   
    if( index < 0 || index >= m_probeSize){
        throw out_of_range ("Out_of_range");
    }
    if(m_table[index].m_flag == OCCUPIED){
        contents.push_back(m_table[index].m_data);
        return 1;
    }
    else{ return 0; }
}

template <typename T>
ProbeHashTable<T>::HashTableEntry::HashTableEntry(){
    
    m_flag = EMPTY;
}

template <typename T>
void ProbeHashTable<T>::HashTableEntry::insert(const T &data){
 
    m_data = data;
    m_flag = OCCUPIED;
}

#endif
    

