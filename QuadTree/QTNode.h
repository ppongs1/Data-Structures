//
//  QTNode.h
//  Project3
//
//  Created by Pearl Pongsuppat on 3/30/18.
//  Copyright © 2018 Pearl Pongsuppat. All rights reserved.
//

#ifndef QTNODE_H
#define QTNODE_H

#include <vector>
#include "Point.h"
#include "BBox.h"

#define QT_NUM_KIDS 4

class QTNode {
public:
    class iterator {
    public:
        iterator();
        bool operator==(const QTNode::iterator &other);
        bool operator!=(const QTNode::iterator &other);
        iterator &operator++();          // Prefix: e.g. "++it"
        iterator operator++(int dummy);  // Postfix: "it++"
        QTNode *&operator*();
        iterator begin();
        iterator end();
    
        // Add data members here to record state of current iterator position
        std::vector <QTNode*>::iterator it;
        QTNode *parent, *curr;
        
        
    };
    
    QTNode();
    ~QTNode();
    bool add(const Point &pt, int data);  // actually, add/replace
    bool remove(const Point &pt);
    bool find(const Point &pt, int &data);
    int findPoints(const BBox &region, std::vector<Point> &found);
    bool checkLeaf();
    void dump();
    
    iterator begin();
    iterator end();
    
    BBox m_bounds;  // The bounding box for this node
    Point m_point;  // If leaf node (i.e., no kids), m_point, m_data hold the
    int m_data;     // actual point and data value the user inserted.
      
    // YOu must add data member(s) to store pointers to child QTNode's
    QTNode *pt1, *pt2, *pt3, *pt4;
    std::vector<QTNode*> myVector;
    int m_size;
    
    
};
#endif
