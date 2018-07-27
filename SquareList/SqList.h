//  file: SqList.h
//  CMSC 341 Proj2
//
//  Created by Pearl Pongsuppat on 2/27/18.
//  Copyright © 2018 Pearl Pongsuppat. All rights reserved.
//


#ifndef _SQLIST_H_
#define _SQLIST_H_

#include <list> 
#include <iostream>
#include "INode.h"
#include "DNode.h"
#include "Int341.h"
#include <stdexcept>

using namespace std;
class SqList{
    

 public:
  
  //Default Constructor, 
  SqList();
    
  //Copy Constructor. The runnings time must be O(n)
  SqList(const SqList &other);

  //Destructor
  ~SqList();
    
  //OverLoaded Assignment Operator. The running time of the assignment
  //operator must be O(n)
  const SqList& operator=(const SqList& rhs);
 
  //Consolidate
  void consolidate();
    
  //Inspector
  void inspector();
    
  //Member function to insert an item into the appropriate sorted position in list
  void add(const Int341& data);
    
  //Remove a value from the square list and return its value
  //If data is not valid throw out of range exception.
  //This function should call consolidate() after removal
  //The remove function should take O(sqrt(n)) not counting the time for consolidate
  Int341 remove(const Int341& data);
    
  //Remove an item from the given position of the Sqlist and return its value
  //If pos is not valid throw out of range exception.
  //This function should call consolidate() after removal
  //The remove function should take O(sqrt(n)) not counting the time for consolidate
  Int341 removeAt(int pos);
    
  //Returns the position of the first occurrence of a value in a SqList
  //If data does not appear in the list, then return -1
  int indexOf(const Int341& data);

    
  //Overloaded operator. If pos is not valid throw out of range exception
  Int341& operator[](int pos);
    
    
  //Returns the number of items in a SqList
  int numItems();
  
  //Checks for condition 1. Inner list must be less than or equal to sqrt(n)*2
  float calcSize();
    
  //Debugging
  void dump();

private:
    list <INode> m_iList;
    int m_num;
    int m_outerSize;
    float m_innerSD;
};
#endif
