//
//  INode.cpp
//  CMSC 341 Proj2
//
//  Created by Pearl Pongsuppat on 2/27/18.
//  Copyright © 2018 Pearl Pongsuppat. All rights reserved.
//

#include "INode.h"
#include "DNode.h"
#include "Int341.h"

#include <iostream>
using namespace std;

//Default Constructor
INode::INode(){
    m_dNode = NULL;
    m_tail = NULL;
    m_size = 0;
}

INode::~INode(){

}

//Builds my single linked list of DNode objects
void INode::addData(Int341 data){
   
  DNode *curr;
  DNode *temp = new DNode;
  temp->setData(data);
  temp->setNext(NULL);
        
  //If my linked list is empty, set head to point to the first node
  if(m_dNode == NULL){
 
    m_dNode = temp;
    m_tail = temp;
    m_size = 1;
 
  }
  
  //Checks if the node to be inserted is less than the first node
  //of the linked list
  else if(data <= m_dNode->getData()){
      temp->setNext(m_dNode);
      m_dNode = temp;
      m_size++;
  }
    
   //If the data is greater than (or equal to) the data at the tail node it will go
  //at the end of the linked list
  else if(data >= m_tail->getData()){
    m_tail->setNext(temp); 
    m_tail = temp;
    m_size++;
  }
  
  else{
      for(curr = m_dNode; curr != NULL; curr = curr->getNext()){
          if(data > curr->getData() && data <= curr->getNext()->getData()){
              DNode *now = curr->getNext();
              curr->setNext(temp);
              temp->setNext(now);
              m_size++;
              break;
          }
      }
  }

}


int INode::find(Int341 data){
   
    DNode *curr = m_dNode;
    int pos;
    if(data == m_dNode->getData()){
  
        return 0;
    }
    
    //Returns index if the data is at the end of the list
    else if(data == m_tail->getData()){
       
        return (m_size-1);
    }
    
    else{
      
        for(int i = 0; i < m_size; i++){
           
            //If the current data in your node is less than the one you want to find
            //move to the next node
            if(curr->getData() > data){
                
                pos = i;
                break;
            }
            else{
                curr = curr->getNext();
                
            }
        }

        return (pos-1);
    }
}

//Retrieves the value at the given index.
Int341 INode::findAt(int pos){

  DNode *curr = m_dNode;
  Int341 numVal;
  if(pos == 0){
      
    numVal = m_dNode->getData().m_data;
    return numVal;

  }

  //Returns the last item in the list                                                                                                                                                                         
  else if(pos == -1 && m_tail != NULL){
    numVal = m_tail->getData().m_data;
   
    return numVal;
  }

    
  else{
    for(int i = 0; i < pos; i++){
      curr = curr->getNext();
    }
    numVal = curr->getData().m_data;
    return numVal;
  }

  return -1;
}

//Returns the value of the data at the given index in the INode
Int341 INode::removeAt(int pos){
    
    DNode *curr = m_dNode;
    DNode *temp;
    Int341 intVal;
   
    //If the position is the first node in the linked list then change
    //where m_dNode points to and delete the first node
    if(pos == 0){
        intVal = m_dNode->getData().m_data;
        m_dNode = m_dNode->getNext();
        delete curr;
        curr = NULL;
    }
   
    else{
        
        //Traverse through the list to find the previous node of the node
        //that you want to delete.
        for(int i = 0; i < pos-1; i++){
            curr = curr->getNext();
            
        }
        
        //When you want to delete the last item in the linked list
        if(pos == m_size -1){
            intVal = m_tail->getData().m_data;
            delete m_tail;
            m_tail = curr;
            m_tail->setNext(NULL);
            
        }
        else{
         
            temp = curr->getNext();
            curr->setNext(temp->getNext());
            intVal = temp->getData().m_data;
            delete temp;
            temp = NULL;
        }
    }
   // m_size--;
    return intVal;
    
}

Int341 INode::remove(const Int341& data){
    
    //Call find to get the position of the data and traverse through
    //the list until the position is reached. 
    Int341 numVal;
    int pos = find(data);
    
    DNode *curr = m_dNode;
    //Removes the data if it is the first data in the INode
    if(data == m_dNode->getData()){
        
        numVal = m_dNode->getData();
        m_dNode = m_dNode->getNext();
        delete curr;
        curr = NULL;
       
    }
    else{
        for(int i = 0; i < pos -1 ; i++){
        
        curr = curr->getNext();
      
        }
        if(data == m_tail->getData()){
            
            DNode *temp = curr->getNext();
            numVal = m_tail->getData();
            curr->setNext(temp->getNext());
            delete m_tail;
            m_tail = curr;
            
        }
        
        else{

            DNode *temp = curr->getNext();
            numVal = temp->getData();
            curr->setNext(temp->getNext());
            delete temp;
            temp = NULL;
            
                
            }
        }
  
    return numVal;
}
DNode* INode::getTail(){
    DNode *curr = m_dNode;
    while(curr->m_next != NULL){
        curr = curr -> m_next;
    }
    return curr;
    
}
void INode::setSize(int size){
    m_size = size;
    
}
int INode::getSize(){
    
    return m_size;
    
}
void INode::print(){
   

  DNode *curr = m_dNode;
  for(int i = 0; i < m_size; i++){
      
      cout << "[" << curr->getData().m_data << "]"<< "->";
      curr = curr->getNext();
      
  }

}

