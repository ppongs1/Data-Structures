//
//  MinMaxHeap.h
//  CMSC 341 Proj4
//  Created by Pearl Pongsuppat on 4/20/18.
//  Copyright © 2018 Pearl Pongsuppat. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#ifndef MINMAXHEAP_H
#define MINMAXHEAP_H
using namespace std;


template <typename T>
class MinMaxHeap{

    struct keyVal{
        T m_data;
        int index;
    };
    
public:
    //Default Constructor
    MinMaxHeap(int capacity);
    
    //Copy Constructor
    MinMaxHeap(const MinMaxHeap<T>& other);
    
    //Destructor
    ~MinMaxHeap();
    
    //Overloaded assignment operator
    const MinMaxHeap<T>& operator=(const MinMaxHeap<T>& rhs);

    //Size function that returns the #items in the
    //min-max heap
    int size();
    
    //Adds item to the min-max heap. Throws out of
    //range exception if the heap has reached capacity
    void insert(const T& data);
    
    
    //Removes the smallest item in the min-max heap and
    //returns the key value of the deleted item
    T deleteMin();
    
    //Removes the largest item in the min-max heap
    //and returns the key value of the deleted item
    T deleteMax();
    
    void locateMin(int pos, T& data, int& index);
    void locateMax(int pos, T& data, int& index);
    void dump();
    int m_capacity;
    int m_size;
    
    class Heaps{
    public:
        //Constructor
        Heaps(int);
        //Destructor
        ~Heaps();
        int insert(const T& data, keyVal pairArray[], int indexArray[], int &arrSize);
        
        //Updates the corresponding twin heap so that the data has
        //the correct index value associated with it.
        void swapVals(Heaps* nextHeap, keyVal pairArray[], int indexArray[], int &index);
        
        //Helper function for deleteMin()/deleteMax()
        int fixDelete(keyVal minValArray[], int indexArray[], int &arrSize);
       
        //Fixes the corresponding twin heap after deleteMin() or deleteMax()
        void fixHeap(Heaps*, int hole);
        
        //Swap parent and child
        int percolateUp(int hole, const T& data, keyVal pairArray[], int indexArray[], int &arrSize);
        int percolateDown(int hole, const T& data, keyVal pairArray[], int indexArray[], int &arrSize);
        
        void dump(); 
        
        //Member variable for a dynamically allopcated array that will contain
        //the data for the Min/Max heaps
        keyVal *heapArray;
        
        //Function pointer that returns true depending on the condition for the heap
        bool (*m_comparison)(const T&, const  T&);
        int size;
        int m_capacity;
    private:
        
    };
    
    Heaps *minHeap;
    Heaps *maxHeap;
private:
    
};
template <typename T>
bool maxProperty( const T& data,const  T& data2);

template <typename T>
bool minProperty( const T& data, const T& data2);


#include "MinMaxHeap.cpp"
#endif

