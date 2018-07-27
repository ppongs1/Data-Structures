//  QTNode.h
//  Project3
//
//  Created by Pearl Pongsuppat on 3/30/18.
//  Copyright © 2018 Pearl Pongsuppat. All rights reserved.
//

#include "QTNode.h"
#include <iostream>
using namespace std;

#define QT_NUM_KIDS 4

QTNode::iterator::iterator(){
    curr = NULL;
    parent = NULL;
}
bool QTNode::iterator::operator==(const QTNode::iterator &other){
    return curr == other.curr;
}

bool QTNode::iterator::operator!=(const QTNode::iterator &other){
    
    return curr != other.curr;

}
//prefix
QTNode::iterator &QTNode::iterator::operator++(){
    
    if(curr == parent->pt1){
        curr = parent->pt2;
    }
    if(curr == parent->pt2){
        curr = parent->pt3;
    }
    if(curr == parent->pt3){
        curr = parent->pt4;
    }
    if(curr == parent->pt4){
        curr = NULL;
    }
    return *this;
}

//postfix
QTNode::iterator QTNode::iterator::operator++(int dummy){
 
    QTNode::iterator temp;
    temp = *this;
    if(curr == parent->pt1){
        curr = parent->pt2;
    }
    if(curr == parent->pt2){
        curr = parent->pt3;
    }
    if(curr == parent->pt3){
        curr = parent->pt4;
    }
    if(curr == parent->pt4){
        curr = NULL;
    }

    return temp;
}
QTNode *&QTNode::iterator::operator*(){
    
    return curr;
}

QTNode::iterator QTNode::begin(){
    
    QTNode::iterator temp;
    temp.parent = this;
    temp.curr = temp.parent->pt1;
    return temp;
    
}
QTNode::iterator QTNode::end(){
    
    QTNode::iterator temp;
    temp.parent = this;
    temp.curr = temp.parent->pt4;
    return temp;
}

QTNode::QTNode(){
    
    m_data = 0;
    pt1 = NULL;
    pt2 = NULL;
    pt3 = NULL;
    pt4 = NULL;
    myVector.push_back(pt1);
    myVector.push_back(pt2);
    myVector.push_back(pt3);
    myVector.push_back(pt4);
}
QTNode::~QTNode(){

}

//Sets the point and data to the node.
bool QTNode::add(const Point &pt, int data){
  
    m_point = pt;
    m_data = data;
    
    return 0;
}

//Checks if m_point = pt, returns true if it is.
bool QTNode::remove(const Point &pt){
    if(m_point == pt){
        return 1;
    }
    else{ return 0; }
}

//Checks if m_point = pt, sets data equal to m_data and returns true
bool QTNode::find(const Point &pt, int &data){

    if(m_point == pt){
        data = m_data;
        return 1;
    }
    
    else { return 0; }
    
}

//Pushes the point to the back of the vector and returns the size of the vector
int QTNode::findPoints(const BBox &region, std::vector<Point> &found){

  found.push_back(m_point);
    
  return int(found.size());
}

//Checks if the children nodes of the parent point to NULL
//If they all point to NULL then the node is a leaf.
bool QTNode::checkLeaf(){

    if(pt1 == NULL && pt2 == NULL && pt3 == NULL && pt4 == NULL){
        return 1;
    }
    return 0;
}
//Prints the BBox, Point, and data of the node.
void QTNode::dump(){

    cout << " [QTNODE BOUNDS = " << m_bounds << " } " << endl;
    
    if(checkLeaf() == 1 ){
        
        cout << " is LEAF: pt= " <<  m_point << ", data=" << m_data << "]" << endl;
        
    }
    else{
        
        cout << " is INTERNAL:  " << endl;
    }
}
    
 
