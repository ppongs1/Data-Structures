//  file: SqList.cpp
//  CMSC 341 Proj2
//
//  Created by Pearl Pongsuppat on 2/27/18.
//  Copyright © 2018 Pearl Pongsuppat. All rights reserved.
//

#include <iostream>
#include "SqList.h"
#include "INode.h"
#include "DNode.h"
#include "Int341.h"
#include <list>
#include <cmath>

using namespace std;

SqList::SqList(){

    list <INode> m_iList;
    m_num = 0;
    m_innerSD = 0;
    m_outerSize= 0;
}
SqList::~SqList(){
    
    list<INode>::iterator it;
    for(it = m_iList.begin(); it != m_iList.end(); it++){
        DNode *temp = it->m_dNode;
        while(it->m_dNode != NULL){
            temp = it->m_dNode;
            it->m_dNode = it->m_dNode->getNext();
            delete temp;
        }
        delete it->m_dNode;
        it->m_dNode = NULL;
        temp = NULL;
        
    }
}

//Copy Constructor. The runnings time must be O(n)
SqList::SqList(const SqList &other){
    int newSize,count;
    m_num = other.m_num;
    /*
    list<INode>::iterator it, it2;
    for(it = other.m_iList.begin(); it != other.m_iList.end(); it++){
        INode *temp = new INode;
        newSize = it->getSize();
        m_iList.push_back(*temp);
        it2 = m_iList.end();
        it2--;
        
        for(DNode *curr = it->m_dNode; count < newSize; curr = curr->getNext()){
            it2->addData(curr->getData());
            count++;
        }
        count = 0;
    }*/

}
    
//OverLoaded Assignment Operator. The running time of the assignment
//operator must be O(n)
const SqList& SqList::operator=(const SqList& rhs){

    return *this;
}
    
//Consolidate checks for merging and splitting inner lists
void SqList::consolidate(){
    
    int mid;
    list<INode>::iterator it;
    for(it= m_iList.begin(); it != m_iList.end(); it++){
        //cout << "consolidate " << endl;
        //check the size of the inner list and if it doesn't meet
        //condition 1 then split.
        if(float(it->getSize()) > calcSize()){
           
            INode *temp = new INode;
            mid = floor(it->getSize()/2);
            DNode *curr = it->m_dNode;
            DNode *prev,*temptail;
            
            //Find the node you want to split by iterating through the INode to the midpoint.
            //When the midpoint is reached, check the size of the entire list to see if it is
            //even or odd and split accordingly.
            for(int i = 0; i < mid+1; i++){

                if(i == mid){
                    
                    temp->m_dNode = curr;
                    if(it->getSize()%2 != 0){
                        it->setSize(mid);
                        temptail = it->m_tail;
                        it->m_tail = prev;
                        temp->m_tail = temptail;
                        temp->setSize(mid+1);
                        m_outerSize++;
                    }
                    else{
                       
                        it->setSize(mid);
                        temptail = it->m_tail;
                        it->m_tail = prev;
                        temp->m_tail = temptail;
                        temp->setSize(mid);
                        m_outerSize++;
                        
                    }
                    
                    it++;
                    m_iList.insert(it, *temp);
                    break;
                }
             
                //Moves to the next node until the midpoint is reached.
                else{
                    prev = curr;
                    curr = curr->getNext();
                   
                }
                
            }

        }
        //Checks for adjacent short lists.
        else if (float(it->getSize()) <= float(sqrt(m_num)/2)){
           
            if(it == m_iList.end()){
           
               break;
            }
           
            else{
                   it++;
                    if(float(it->getSize()) < float(sqrt(m_num)/2)){
                      //  cout << "inside if statement " << endl;
                        DNode *curr = it->m_tail;
                        int tempSize = it->getSize();
                        it--;
                        it->m_tail = curr;
                        it->setSize(it->getSize()+ tempSize);
                        it++;
                        it = m_iList.erase(it);
                        
                     //   break;
                    }
                it--;
            }
        
        }
        //Checks for an empty INode
        else if(it->getSize() == 0){
            
            m_iList.erase(it);
            m_outerSize--;
            break;
        }
     }
}

    
//Inspector
//void SqList::inspector(){

//}
    
//Member function to insert an item into the appropriate sorted position
void SqList::add(const Int341& data){
   
    //If the list is empty add it to the first element of the list
    if(m_num == 0){
        INode *index = new INode;
        index->addData(data);
        m_iList.push_front(*index);
        m_outerSize++;
        m_num++;
        
    }
    
    //Checks if the data is greater than the last number in the square list. If it is the data
    //will be added to that INode.
    else if((data > m_iList.back().findAt(-1))){
       
        m_iList.back().addData(data);
        m_num++;
        
    }
    
    else{
       
        list<INode>::iterator it;
        for(it= m_iList.begin(); it != m_iList.end(); it++){
            
            //if the data you want to insert is less than or equal to the first element
            //of that INode
            if(data <= it->findAt(-1)){
                it->addData(data);
                m_num++;
                break;
            }
        }
    }

   consolidate();
}

    

//Remove a value from the square list and return its value
//If data is not valid throw out of range exception.
//This function should call consolidate() after removal
//The remove function should take O(sqrt(n)) not counting the time for consolidate
Int341 SqList::remove(const Int341& data){
    
    int innerSize = 0;
    DNode *temptail;
    list<INode>::iterator it;
    for(it= m_iList.begin(); it != m_iList.end(); it++){
        innerSize += it->getSize();
      
        if(data > it->findAt(0) && data < it->findAt(-1)){
      
            it->remove(data);
            temptail = it->m_tail;
            it->m_tail = temptail;
            it->setSize(it->getSize()-1);
            m_num--;
            break;
        }
        else if(data == it->m_dNode->getData()){
            it->removeAt(0);
            it->setSize(it->getSize()-1);
            m_num--;
            break;
        }
        else if(data == it->m_tail->getData()){
            it->remove(data);
            it->setSize(it->getSize()-1);
            m_num--;
            break;
        }
     }
    consolidate();

    return data;

}
    
//Remove an item from the given position of the Sqlist and return its value
//If pos is not valid throw out of range exception.
//This function should call consolidate() after removal
//The remove function should take O(sqrt(n)) not counting the time for consolidate
Int341 SqList::removeAt(int pos){
    
    Int341 dataVal;
    int innerSize = 0;
    int prevSize = 0;
   
    if(pos >= m_num || pos < -1){
        throw ("Out of Range ." );
        
    }
    list<INode>::iterator it;
    for(it= m_iList.begin(); it != m_iList.end(); it++){
        
        innerSize += it->getSize();
        
        if(pos <= innerSize-1){
           
            dataVal = it->findAt(pos - prevSize);
            it->remove(dataVal);
            it->setSize(it->getSize()-1);
            m_num--;
            break;
        }
       
        //Keeps track of the previous size
        else{
            prevSize += innerSize;
            
        }
    }
    consolidate();
    return dataVal;
}
    
//Returns the position of the first occurrence of a value in a SqList
//If data does not appear in the list, then return -1
int SqList::indexOf(const Int341& data){
   
    int numIndex;
    int innerSize = 0;
    
    
    list<INode>::iterator it;
    for(it= m_iList.begin(); it != m_iList.end(); it++){
        
        if(data > it->findAt(0) && data < it->findAt(-1)){
            
            numIndex = it->find(data) + innerSize;
            return numIndex;
            
        }
        else if(data == it->m_dNode->getData().m_data){
            numIndex = innerSize;
            return numIndex;
            
        }
        else if(data == it->m_tail->getData().m_data){
            
            numIndex = (it->getSize()-1) + innerSize;
            return numIndex;
        }
        else{
            
            innerSize += it->getSize();
           
        }
    }
    
    return -1;
    
}


//Overloaded operator. If pos is not valid throw out of range exception
//This is my overloaded operator. During compilation it threw a warning

Int341& SqList::operator[](int pos){

    
    Int341 dataVal;
    int prevSize = 0;
    int innerSize = 0;
    if(pos >= m_num){
        throw ("Out of Range .");
    }
    list<INode>::iterator it;
    for(it= m_iList.begin(); it != m_iList.end(); it++){
        innerSize += it->getSize();
        if(pos < innerSize-1){
            dataVal = it->findAt(pos - prevSize);
            break;
        }
        else{
            prevSize = innerSize;
        }
    }
    return dataVal;
}

float SqList::calcSize(){
    
  
    m_innerSD= 2*(sqrt(m_num));
  
    return m_innerSD;
}

//Returns the number of items in a SqList
int SqList::numItems(){

    return m_num;

}
    
//Debugging
void SqList::dump(){
    cout << "m_num " << m_num << endl;
    int i = 0;
    list<INode>::iterator it;
    for(it= m_iList.begin(); it != m_iList.end(); it++){
        cout << i;
        it->print();
        cout << endl;
        i++;
    }
    
}

 

