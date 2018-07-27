//
//  QTree.h
//  Project3
//
//  Created by Pearl Pongsuppat on 3/29/18.
//  Copyright © 2018 Pearl Pongsuppat. All rights reserved.
//

#ifndef QTREE_H
#define QTREE_H

#include "Point.h"
#include "BBox.h"
#include "QTNode.h"

class QTree {
public:
    QTree();
    ~QTree();
    void helpDestruct(QTNode*);
    bool add(const Point &pt, int data);  // actually, add/replace
    bool addChild(QTNode*,QTNode*);
    bool remove(const Point pt);
    bool removeChild(QTNode*, const Point pt);
    void fixRoot(QTNode*&);
    bool checkRoot(QTNode*);
    bool find(const Point pt, int &data);
    bool findChild(QTNode*, const Point pt, int &data);
    int findPoints(const BBox &region, std::vector<Point> &found);
    void findHelp(QTNode*, const BBox &region,std::vector<Point> &found,  int &data);
    void quadPoints(QTNode*,const BBox &region, std::vector<Point> &found, int &data);
    void dump();
    void reDump(QTNode*);
    
    QTNode *m_root;
    
private:
    
    
};

#endif
