//
//  HashTable.hpp
//  CMSC 341 Proj5
//
//  Created by Pearl Pongsuppat on 5/6/18.
//  Copyright © 2018 Pearl Pongsuppat. All rights reserved.
//

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <iostream>
#include "HashTable.h"

template <typename T>
HashTable<T>::~HashTable(){

}


template <typename T>
bool HashTable<T>::insert(const T &data){

}

bool HashTable<T>::find(const T &data) = 0{

}

template <typename T>
T HashTable<T>::remove(const T &data, bool &found){

}
    
    // Functions for debugging and grading:
template <typename T>
void HashTable<T>::dump(){
    
    
}

template <typename T>
int HashTable<T>::at(int index, std::vector<T> &contents){
    
}
    

#endif
