//
//  ChainHashTable.hpp
//  CMSC 341 Proj5
//
//  Created by Pearl Pongsuppat on 5/6/18.
//  Copyright © 2018 Pearl Pongsuppat. All rights reserved.
//

#ifndef ChainHashTable_CPP
#define ChainHashTable_CPP
#include <iostream>
#include <list>
#include <iterator>
#include "ChainHashTable.h"
#include <stdexcept>



//These are the default constructors for your two hash table classes. The parameter
//hashFunc is a pointer to the function that should be used to generate hash codes for the
//data type T. The parameter n is the requested size of the hash table. We chose 101 as
//the default value because it is a nice prime number.

template <typename T>
ChainHashTable<T>::ChainHashTable(unsigned int (*hashFunc)(const T&), int n){
    
    this->hashFunc = hashFunc;
    m_size = n;
    m_table = new list<T>[n];
    totalItems = 0;

}
//Destructor
template <typename T> 
ChainHashTable<T>::~ChainHashTable(){
    delete [] m_table;
    m_table = NULL;
    
}
    
//Copy Constructor
template <typename T>
ChainHashTable<T>::ChainHashTable (ChainHashTable& other){
    m_size = other.m_size;
    totalItems = other.totalItems;
    
    this->hashFunc = other.hashFunc;
    m_table = new list<T>[other.m_size];
    for(int i = 0; i < m_size; i++){
        typename  list<T>::iterator it;
        for(it = other.m_table[i].begin(); it != other.m_table[i].end(); it++){
            
            m_table[i].push_back(*it);
        }
    }
    
}
    
//Overloaded Assignment Operator
template <typename T>
const ChainHashTable<T>& ChainHashTable<T>::operator= (ChainHashTable<T>& rhs){
  
    if( this != &rhs){
    m_size = rhs.m_size;
    totalItems = rhs.totalItems;
    
    this->hashFunc = rhs.hashFunc;
    m_table = new list<T>[rhs.m_size];
    for(int i = 0; i < m_size; i++){
        typename  list<T>::iterator it;
        for(it = rhs.m_table[i].begin(); it != rhs.m_table[i].end(); it++){
            
            m_table[i].push_back(*it);
            }
        }
    }
    return *this;
}
    
//This function inserts data into the hash table. It returns true if data was new and
//inserted. if data is already in the hash table, it is left as-is, and the function
//returns false
template <typename T>
bool  ChainHashTable<T>::insert(const T &data){
   
    if(find(data)){
        return 0;
    }
    int hashNum = this->hashFunc(data) % m_size;
    m_table[hashNum].push_front(data);
    totalItems++;
    return 1;
}
    
//The find() function looks for data in the hash table. The function returns true if
//found, false otherwise.
template <typename T>
bool ChainHashTable<T>::find(const T &data){
    
    int hashNum = this->hashFunc(data) % m_size;
  
    typename  list<T>::iterator it;
    for(it = m_table[hashNum].begin(); it != m_table[hashNum].end(); it++){
    
        if(*it == data){
            return 1;
        }
    }
    return 0;
}
    
//The remove() function removes data from the hash table if it is found, and returns it,
//setting found to true. If data is not in the hash table, remove() returns with found set
//to false
template <typename T>
T ChainHashTable<T>::remove(const T &data, bool &found){

     int hashNum = this->hashFunc(data) % m_size;
    
    typename  list<T>::iterator it;
    for(it = m_table[hashNum].begin(); it != m_table[hashNum].end(); it++){
        
        if(*it == data){
            m_table[hashNum].erase(it);
            found = true;
            return data;
        }
    }
    found = false;
    return data;
}
    
 //dump() function does the usual: print some vital statistics and the contents of the
//hash table(s) to stdout.
template <typename T>
void ChainHashTable<T>::dump(){
    
    for (int index = 0; index < m_size; index++){
        typename  list<T>::iterator it;
        cout << "[" << index << "] :";
        for(it = m_table[index].begin(); it != m_table[index].end(); it++){

            cout << *it << " , ";
        }
        cout << endl;
    }
    cout << "Total Items : " << totalItems << endl;
}
    
//The at() function returns the number of items stored at the index slot of the hash
//table.
template <typename T>
int ChainHashTable<T>::at(int index, std::vector<T> &contents){

    if( index < 0 || index >= m_size){
        throw out_of_range ("Out_of_range");
    }
    int count = 0;
    typename  list<T>::iterator it;
    for(it = m_table[index].begin(); it != m_table[index].end(); it++){
        contents.push_back(*it);
        count++;
    }
    return count;
}
#endif
