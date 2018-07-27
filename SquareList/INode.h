//
//  INode.h
//  CMSC 341 Proj2
//
//  Created by Pearl Pongsuppat on 2/27/18.
//  Copyright © 2018 Pearl Pongsuppat. All rights reserved.
//

#ifndef INODE_H
#define INODE_H
#include "DNode.h"
#include "Int341.h"

//Each element in the index-level list will be an object of the INode class
//(for "Index-list Node")

class INode {
    
public:
    
    INode(); //Default constructor
    ~INode(); //Destructor
    INode* getNext(); //Retrieves the m_next pointer
    void addData(Int341); //Adds the value of the data to the singly linked list
    int find(Int341); //Retrieves the index of the data in the list
    Int341 findAt(int); //Retrieves the value at the given index
    Int341 removeAt(int); //Removes item and returns the data value
    
    Int341 remove(const Int341& data);
    DNode* getTail();
    void setSize(int);
    int getSize(); //returns size of the INode
    void print(); //Prints out the contents of my linked list
    DNode* m_dNode; //pointer to the data level node it is indexing into
    DNode *m_tail; //Pointer to the end of the linked list
    int m_size; //Keeps track of the size of each INode
};

#endif /* INode_h */
