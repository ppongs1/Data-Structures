//
//  QTree.hpp
//  Project3
//
//  Created by Pearl Pongsuppat on 3/29/18.
//  Copyright © 2018 Pearl Pongsuppat. All rights reserved.
//

#include "Point.h"
#include "BBox.h"
#include "QTNode.h"
#include "QTree.h"
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

//Default constructor
QTree::QTree(){
    m_root = NULL;
}

//Destructor
QTree::~QTree(){

    //Calls a helper destructor function
    helpDestruct(m_root);
    delete m_root;
    m_root = NULL;

}

//Helper destructor function, recursively deletes nodes from the quadtree
void QTree::helpDestruct(QTNode *curr){
    
    //Traverses through the tree recursively until
    //First goes through each child node, checking if it is NOT equal
    //to NULL. Then checks if the node is a leaf node
    if(curr->pt1 != NULL){
        if(curr->pt1->checkLeaf() == 1){
            delete curr->pt1;
            curr->pt1 = NULL;
        }
        else{
            helpDestruct(curr->pt1);
            delete curr->pt1;
            curr->pt1 = NULL;
        }
    }
    if(curr->pt2 != NULL){
        if(curr->pt2->checkLeaf() == 1){
            delete curr->pt2;
            curr->pt2 = NULL;
        }
        else{
            helpDestruct(curr->pt2);
            delete curr->pt2;
            curr->pt2 = NULL;
        }
    }
    if(curr->pt3 != NULL){
        if(curr->pt3->checkLeaf() == 1){
            delete curr->pt3;
            curr->pt3 = NULL;
        }
        else{
            helpDestruct(curr->pt3);
            delete curr->pt3;
            curr->pt3 = NULL;
        }
    }
    if(curr->pt4 != NULL){
        if(curr->pt4->checkLeaf() ==1){
            delete curr->pt4;
            curr->pt4 = NULL;
        }
        else{
            helpDestruct(curr->pt4);
            delete curr->pt4;
            curr->pt4 = NULL;
        }
    }
 
    return;
    
}
bool QTree::add(const Point &pt, int data){
    
    QTNode *temp = new QTNode();
    bool checkAdd = 0;
    
    //Adds the very first item in our tree.
    if(m_root == NULL){
        m_root = temp;
        temp->add(pt, data);
        BBox box1(pt,1);
        temp->m_bounds = box1;
    }

    else{
        //Checks when the root is a leaf but the point you want to insert is
        //out of bounds of the root.
        if(m_root->checkLeaf() == 1 && m_root->m_bounds.inBounds(pt) == 0 ){
            QTNode *curr = new QTNode();

            //Resize your root and add the new pt and data into curr.
            //Temp acts as m_root, and addChild is called to place temp
            //and curr in the correct child nodes of m_root according to
            //its newly resized bounds.

            m_root->m_bounds.resize(m_root->m_point, pt);
            curr->add(pt,data);
            temp->add(m_root->m_point, m_root->m_data);
            checkAdd = addChild(m_root, temp);
            checkAdd = addChild(m_root, curr);
            
           }
        
        //Checks when the root is NOT a leaf and the point you want to insert is
        //out of bounds of the root
        else if(m_root->checkLeaf() == 0 && m_root->m_bounds.inBounds(pt) == 0){
            QTNode *curr2;
            temp->add(pt,data);
            
            //While the point is not within the bounds of m_root
            //Create a new QTNode that will act as the root. Call the grow
            //function and set m_root to the new QTNode. curr2 will keep track
            //of the old root.
            while(m_root->m_bounds.inBounds(pt) == 0){
                QTNode *curr = new QTNode;
                curr->m_bounds = m_root->m_bounds;
                curr->m_bounds.grow();
                curr2 = m_root;
                m_root = curr;
                addChild(m_root, curr2);
            }
            checkAdd = addChild(m_root, temp);
        }
        else{
            //Adds the new node
            temp->add(pt, data);
            checkAdd = addChild(m_root,temp);
        }
     }
    return 0;
}
    
bool QTree::addChild(QTNode *temp, QTNode *curr){
    
    bool checkAdd = 1;
    
    //Creates a box that will check for the regions of each child node.
    BBox box1(temp->m_bounds.m_bL, (temp->m_bounds.m_dim/2));
    
    //If curr has children then set the points of curr to be the most bottom
    //left point of its BBox.
    if(curr->checkLeaf() == 0){
        curr->m_point = curr->m_bounds.m_bL;
    }
    
    //First checks if curr is in bounds with the BBox for the
    //bottom left child node. If it is then set that child node
    //to equal curr and set the bounds of curr to box1. If curr
    //is not inBounds with box1 then change x & y coordinates to
    //check for the quadrant. Repeats for each child node until it is
    //inBounds.
    if(box1.inBounds(curr->m_point)){
        if(temp->pt1 == NULL){
            temp->pt1 = curr;
            curr->m_bounds = box1;
            return checkAdd;
        }
        else{
            checkAdd = addChild(temp->pt1, curr);
       }
    }
    else{
        //Changes x-coordinate so we can look at the second quadrant
        box1.m_bL.m_x = box1.m_bL.m_x + box1.m_dim;
    }
    
    if(box1.inBounds(curr->m_point)){
     
        if(temp->pt2 == NULL){
            temp->pt2 = curr;
            curr->m_bounds = box1;
            return checkAdd;
            
        }
        else{
            checkAdd = addChild(temp->pt2,curr);
        }
    }
    else{
        //Changes x and y coordinates to look at the third quadrant
        box1.m_bL.m_x = box1.m_bL.m_x - box1.m_dim;
        box1.m_bL.m_y = box1.m_bL.m_y + box1.m_dim;
    }
    
    if(box1.inBounds(curr->m_point)){
       
     if(temp->pt3 == NULL){
         
            temp->pt3 = curr;
            curr->m_bounds = box1;
            return checkAdd;
        }
        else{
            checkAdd = addChild(temp->pt3, curr);
        }
    }
    
    else{
        //Changes x coordinate to look at the fourth quadrant.
         box1.m_bL.m_x = box1.m_bL.m_x + box1.m_dim;
    }
    
    if(box1.inBounds(curr->m_point)){
        if(temp->pt4 == NULL){
            temp->pt4 = curr;
            curr->m_bounds = box1;
            return checkAdd;
        }
        else{
            checkAdd = addChild(temp->pt4, curr);
        }
    }
    return checkAdd;
}


bool QTree::remove(const Point pt){
    bool checkRemove = 0;
    
    //Checks when m_root is a leaf and the point is inside that node.
    if(m_root->checkLeaf() == 1 && m_root->m_bounds.inBounds(pt) ==1){
        delete m_root;
        m_root = NULL;
        return 1;
    }
    else{
        if(m_root->checkLeaf() == 0){
            checkRemove = removeChild(m_root, pt);
        }
    }
    fixRoot(m_root);
    return checkRemove;
}
bool QTree::removeChild(QTNode* temp, const Point pt){
    bool checkRemove = 0;
    
    //Checks if the child node is NULL, if it is NOT NULL then
    //check if its a leaf, if it is a leaf then call QTNode remove
    //to check if the point you want to remove is in that child node.
    //If checkRemove returns true then the node is deleted and set to NULL
    //ELSE: If the child node is NOT NULL and if it is NOT a leaf then
    //call removeChild on that node to traverse through that subtree.
    //Continues to do this for all children.
    if(temp->pt1 != NULL){
        
        if(temp->pt1->checkLeaf() == 1){
            checkRemove = temp->pt1->remove(pt);
            if(checkRemove == 1){
                delete temp->pt1;
                temp->pt1 = NULL;
                return checkRemove;
            }
        }
        else{
           removeChild(temp->pt1, pt);
        }
      }
    
    if(temp->pt2 != NULL){
        
        if(temp->pt2->checkLeaf() == 1){
            checkRemove = temp->pt2->remove(pt);
            if(checkRemove == 1){
                delete temp->pt2;
                temp->pt2 = NULL;
                return checkRemove;
            }
        }
        else{
           removeChild(temp->pt2, pt);
        }
    }
    if(temp->pt3 != NULL){
        if(temp->pt3->checkLeaf() == 1){
            checkRemove = temp->pt3->remove(pt);
            if(checkRemove == 1){
                delete temp->pt3;
                temp->pt3 = NULL;
                return checkRemove;
            }
        }
        else{
            removeChild(temp->pt3, pt);
        }
    }
    
    if(temp->pt4 != NULL){
        if(temp->pt4->checkLeaf() == 1){
            checkRemove = temp->pt4->remove(pt);
            if(checkRemove == 1){
                delete temp->pt4;
                temp->pt4 = NULL;
                return checkRemove;
            }
        }
        else{
            removeChild(temp->pt4, pt);
        }
    }

    return checkRemove;
}
void QTree::fixRoot(QTNode *&temp){
   
    //Checks when m_root has only one child node. Fixes the root until
    //the condition is satisfied.
    while(checkRoot(temp) == 1){
        QTNode *curr, *curr2;
        if(temp->pt1 != NULL){
          
            curr = temp->pt1;
        }
        if(temp->pt2 != NULL){
          
            curr = temp->pt2;
        }
        if(temp->pt3 != NULL){
          
            curr = temp->pt3;
        }
        if(temp->pt4 != NULL){
        
            curr = temp->pt4;
        }
        curr2 = temp;
        temp = curr;
        delete curr2;
        curr2 = NULL;
    }
}
bool QTree::checkRoot(QTNode *temp){
    
    //Starting from the root check if it has any children
    //If it does have children increment numChild. Returns
    //true if the root node has only one child, otherwise false.
    int numChild =0;
    if(temp->pt1 != NULL){numChild++;}
    if(temp->pt2 != NULL){numChild++;}
    if(temp->pt3 != NULL){numChild++;}
    if(temp->pt4 != NULL){numChild++;}
    
    if(numChild == 1){
        return 1;
    }
    else{ return 0; }
}
bool QTree::find(const Point pt, int &data){
    
    bool checkPoint = 0;
    
    //If the root is a leaf and the point/data you are looking for
    //is in the root then return true.
    if(m_root->checkLeaf() == 1 && m_root->find(pt, data) ==1){
        return 1;
    }
    else{
        //If the root has children then call the helper function
        //to recursively traverse through the tree to find the correct
        //point and data.
        if(m_root->checkLeaf() ==0){
            checkPoint = findChild(m_root,pt,data);
        }
    }
  return checkPoint;
}
bool QTree::findChild(QTNode *temp, const Point pt, int &data){ 

    bool checkPoint = 0;
   //Checks if the child node is NOT NULL, if it isn't then check
   //if it is a leaf. If it is a leaf call QTNode find(). If checkPoint
   //returns true then the pt and data were found in that node, return
   //checkPoint. Continues to do this for every child node.
    
    if(temp->pt1 != NULL){
        if(temp->pt1->checkLeaf() == 1){
            checkPoint = temp->pt1->find(pt, data);
            if(checkPoint == 1){
                return checkPoint;
            }
        }
        else{
            findChild(temp->pt1, pt,data);
        }
    }
    
    if(temp->pt2 != NULL){
        if(temp->pt2->checkLeaf() == 1){
            checkPoint = temp->pt2->find(pt,data);
            if(checkPoint == 1){
                return checkPoint;
            }
        }
        else{ findChild(temp->pt2, pt, data); }
    }
    if(temp->pt3 != NULL){
        if(temp->pt3->checkLeaf() == 1){
            checkPoint = temp->pt3->find(pt,data);
            if(checkPoint == 1){
                return checkPoint;
            }
        }
        else{ findChild(temp->pt3, pt, data); }
    }
    if(temp->pt4 != NULL){
        if(temp->pt4->checkLeaf() == 1){
            checkPoint = temp->pt4->find(pt,data);
            if(checkPoint == 1){
                return checkPoint;
            }
        }
        else{ findChild(temp->pt4, pt, data); }
    }
    
    return checkPoint;
}
int QTree::findPoints(const BBox &region, std::vector<Point> &found){
  
    int data = 0;
   //If m_root is a leaf and the region overlaps it then adds the point to
   //the vector and returns the size.
    if(m_root->checkLeaf() == 1 && m_root->m_bounds.overlaps(region)){
        found.push_back(m_root->m_point);
        return int(found.size());
    }
    else {
        //Calls recursive function to find the correct subquad tree.
        findHelp(m_root,region,found, data);

    }
  return data;

}
void QTree::findHelp(QTNode *curr,const BBox &region, std::vector<Point> &found, int &data){
    
    //If the region given does not overlap the bounds of the current
    //child node we are at then we have found the correct subquad tree.
    //When the correct subtree is found the helper function quadPoints
    //is called to find the points within that subtree.
    //Otherwise keep recursing through until the region does not overlap
    //Continues to do this for each child.
    if(curr->pt1 != NULL){
        if(curr->pt1->m_bounds.overlaps(region) == 0){
            quadPoints(curr,region,found,data);
        }
        else{
            findHelp(curr->pt1 ,region, found, data);
        }
    }
    if(curr->pt2 != NULL){
        if(curr->pt2->m_bounds.overlaps(region) == 0){
             quadPoints(curr, region,found,data);
        }
        else{
            findHelp(curr->pt2 ,region, found,data);
        }
    }
    if(curr->pt3 != NULL){
        if(curr->pt3->m_bounds.overlaps(region) == 0){
            quadPoints(curr, region, found,data);
        }
        else{
            findHelp(curr->pt3 ,region, found, data);
        }
    }
    if(curr->pt4 != NULL){
        if(curr->pt4->m_bounds.overlaps(region) == 0){
            quadPoints(curr, region, found,data);
        }
        else{
            findHelp(curr->pt4 ,region, found, data);
        }
    }
}

void QTree::quadPoints(QTNode* curr, const BBox &region,std::vector<Point> &found, int &data){

    //Checks each child node to see if it is NULL. If it is not NULL
    //and it is a leaf then call QTNode findPoints. QTNode findpoints will
    //add the point to our vector 'found'.
    //ELSE: Goes through the subquad tree and recurses down until you find a leaf.

    if(curr->pt1 != NULL){
        if(curr->pt1->checkLeaf() == 1){
            curr->pt1->findPoints(region, found);
            data++;
        }
        else{
            quadPoints(curr->pt1, region,found,data);
        }
    }
    if(curr->pt2 != NULL){
        if(curr->pt2->checkLeaf() == 1){
             curr->pt2->findPoints(region, found);
            data++;
        }
        else{
            quadPoints(curr->pt2, region,found, data);
        }
    }
    if(curr->pt3 != NULL){
        if(curr->pt3->checkLeaf() == 1){
            curr->pt3->findPoints(region, found);
            data++;
        }
        else{
            quadPoints(curr->pt3, region,found,data);
        }
    }
    if(curr->pt4 != NULL){
        if(curr->pt4->checkLeaf() == 1){
             curr->pt4->findPoints(region, found);
            data++;
        }
        else{
            quadPoints(curr->pt4, region,found,data);
        }
    }
}
void QTree::dump(){
    //Prints out all of the contents in the tree
    cout << "============================================================" << endl;
    cout << "START Dump of quadtree " << endl;
    cout << "============================================================" << endl;
    if(m_root == NULL){
        cout << "NULL " << endl;
    }

    reDump(m_root);
    cout<< "------------------------------------------------------------" << endl;
    cout << "END Dump of quadtree " << endl;
    cout << "============================================================ " << endl;
}

void QTree::reDump(QTNode *curr){
    
    //Prints the root
    curr->dump();

    //Checks if the child is NULL, if yes print NULL
    //ELSE: Check if the child node is a leaf, if it has
    //children then call reDump with that child node until
    //it reaches a leaf. Print out the contents of that leaf.
    //Continues to do this for each child node/quadrant.
    if(curr->pt1 == NULL){
        cout << "BOTTOM LEFT CHILD : " << endl;
        cout << "NULL " << endl;
    }
    else{
        //Checks if the first child node has children. If yes then
        //recursively call reDump and continue through that subtree.
        if(curr->pt1->checkLeaf() == 0){
            cout << "BOTTOM LEFT CHILD : " << endl;
            reDump(curr->pt1);
            cout << "]" << endl;
        }
        else{
            //If the first quadrant doesn't have children then display point/data
            cout << "BOTTOM LEFT CHILD : " << endl;
            curr->pt1->dump();
        }
    }
    if(curr->pt2 == NULL){
        cout << "BOTTOM RIGHT CHILD : " << endl;
        cout << "NULL " << endl;
        
    }
    else{
        if(curr->pt2->checkLeaf() == 0){
            cout << "BOTTOM RIGHT CHILD : " << endl;
            reDump(curr->pt2);
            cout << "]" << endl;
        }
        else{
            cout << "BOTTOM RIGHT CHILD : " << endl;
            curr->pt2->dump();
        }
    }
   
    if(curr->pt3 == NULL){
        cout << "TOP LEFT CHILD : " << endl;
        cout << "NULL " << endl;
    }
    else{
        if(curr->pt3->checkLeaf() == 0){
            cout << "TOP LEFT CHILD : " << endl;
            reDump(curr->pt3);
            cout << "]" << endl;
        }
        else{
            cout << "TOP LEFT CHILD : " << endl;
            curr->pt3->dump();
        }
    }
    if(curr->pt4 == NULL){
        cout << "TOP RIGHT CHILD : " << endl;
        cout << "NULL " << endl;
    }
    else{
        if(curr->pt4->checkLeaf() == 0){
            cout << "TOP RIGHT  CHILD : " << endl;
            reDump(curr->pt4);
            cout << "]" << endl;
        }
        else{
            cout << "TOP RIGHT CHILD : " << endl;
            curr->pt4->dump();
        }
    }
   return;
    
}
