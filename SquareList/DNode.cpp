//
//  DNode.cpp
//  CMSC 341 Proj2
//
//  Created by Pearl Pongsuppat on 2/27/18.
//  Copyright © 2018 Pearl Pongsuppat. All rights reserved.
//

#include "DNode.h"
#include <iostream>
#include "Int341.h"

using namespace std;

DNode::DNode(){
    
    m_next = NULL;
    m_data = 0;
    
}

DNode::~DNode(){
    
    
}

void DNode::setNext(DNode *next){

  m_next = next;
}
DNode* DNode::getNext(){

  return m_next;

}
Int341 DNode::getData(){
    
  return m_data;
    
}

void DNode::setData(Int341 data){
 
  m_data = data;
 
}




