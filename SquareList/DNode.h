//
//  DNode.h
//  CMSC 341 Proj2
//
//  Created by Pearl Pongsuppat on 2/27/18.
//  Copyright © 2018 Pearl Pongsuppat. All rights reserved.
//

#ifndef DNODE_H
#define DNODE_H
#include "Int341.h"

class DNode {
    
public:
    DNode(); //Default Constructor
    ~DNode();
    void setData(Int341); //Sets the value for the data
    Int341 getData(); //Retrieves the value of the data
    DNode *getNext(); //Returns the pointer of the node
    void setNext(DNode*);
    void addData(int);
    Int341 m_data; //stores the value of the data
    DNode *m_next;
    
    
};

#endif /* DNode_h */
