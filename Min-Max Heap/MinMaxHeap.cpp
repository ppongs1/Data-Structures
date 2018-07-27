//
//  CMSC_341_Proj4.
//  CMSC 341 Proj4
//
//  Created by Pearl Pongsuppat on 4/20/18.
//  Copyright © 2018 Pearl Pongsuppat. All rights reserved.
//

#include <iostream>

#include "MinMaxHeap.h"
#include <cstdlib>
#ifndef MINMAXHEAP_CPP
#define MINMAXHEAP_CPP

//Constructor
template <typename T>
MinMaxHeap<T>::MinMaxHeap(int capacity){
    
    m_size = 0;
    m_capacity = capacity;
    minHeap = new Heaps(m_capacity+1);
    maxHeap = new Heaps(m_capacity+1);
    minHeap->m_comparison = &minProperty;
    maxHeap->m_comparison = &maxProperty;
}

//Copy Constructor
template <typename T>
MinMaxHeap<T>::MinMaxHeap(const MinMaxHeap<T>& other){
    
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    
    minHeap = new Heaps(other.m_capacity+1);
    maxHeap = new Heaps(other.m_capacity+1);
    
    minHeap->m_comparison = &minProperty;
    maxHeap->m_comparison = &maxProperty;
    
    minHeap->size = other.minHeap->size;
    minHeap->m_capacity= other.minHeap->m_capacity;
    maxHeap->size = other.maxHeap->size;
    maxHeap->m_capacity= other.maxHeap->m_capacity;
    
    for(int i = 0; i < m_capacity; i++){
        maxHeap->heapArray[i] = other.maxHeap->heapArray[i];
        minHeap->heapArray[i] = other.minHeap->heapArray[i];
    }
}

//Destructor
template <typename T>
MinMaxHeap<T>::~MinMaxHeap(){
    delete minHeap;
    delete maxHeap;
    
}

//Overloaded assignment operator
template <typename T>
const MinMaxHeap<T>& MinMaxHeap<T>::operator=(const MinMaxHeap<T>& rhs){

    if(this != &rhs){
        
        delete minHeap;
        delete maxHeap;
        
        m_capacity = rhs.m_capacity;
        m_size = rhs.m_size;
        
        minHeap = new Heaps(rhs.m_capacity);
        maxHeap = new Heaps(rhs.m_capacity);
        
        minHeap->m_comparison = &minProperty;
        maxHeap->m_comparison = &maxProperty;
        
        minHeap->size = rhs.minHeap->size;
        minHeap->m_capacity= rhs.minHeap->m_capacity;
        maxHeap->size = rhs.maxHeap->size;
        maxHeap->m_capacity= rhs.maxHeap->m_capacity;
        
        for(int i = 0; i < m_capacity; i++){
            maxHeap->heapArray[i] = rhs.maxHeap->heapArray[i];
            minHeap->heapArray[i] = rhs.minHeap->heapArray[i];
        }
    }
    return *this;
}

template <typename T>
int MinMaxHeap<T>::size(){
    
    return m_size;
}

template <typename T>
void MinMaxHeap<T>::insert(const T& data){
    
    //Create a keyVal array to store the pairs that will be swapped after
    //insertion and another indexArray for the index they move into.
    //Each heap will have one of each array
    keyVal minPairArray[m_capacity];
    keyVal maxPairArray[m_capacity];
    int minIndexArray[m_capacity];
    int maxIndexArray[m_capacity];
    int minArrSize = 0;
    int maxArrSize = 0;

    //num1 and num2 will return the index value the data belongs to in that heap
    int num1, num2;
    num1 = minHeap->insert(data, minPairArray, minIndexArray, minArrSize);
    num2 = maxHeap->insert(data, maxPairArray, maxIndexArray, maxArrSize);
    
    //Sets the corresponding indices for each heap
    minHeap->heapArray[num1].index = num2;
    maxHeap->heapArray[num2].index = num1;
    
    //If any values percolated up during insertion, then the index values
    //will need to be updated in the other heaps.
    minHeap->swapVals(maxHeap, minPairArray, minIndexArray,minArrSize);
    maxHeap->swapVals(minHeap, maxPairArray, maxIndexArray,maxArrSize);
    m_size++;
}

template <typename T>
T MinMaxHeap<T>::deleteMin(){
   
    keyVal minValArray[m_capacity];
    int indexArray[m_capacity];
    int arrSize = 0;
    int numIndex;
    
    //Grabs the corresponding index in the max heap
    int hole = minHeap->heapArray[1].index;
    
    //Stores the original min value to return at the end of function
    T temp = minHeap->heapArray[1].m_data;
    
    //Replaces the minimum value with the value in the deepest leaf to the right,
    //and numIndex will store the index value of the data after percolating down.
    //swapVals() will update the index value for the data that were previously
    //swapped.
    minHeap->heapArray[1] = minHeap->heapArray[m_size];
    numIndex = minHeap->fixDelete(minValArray,indexArray, arrSize);
    minHeap->swapVals(maxHeap, minValArray, indexArray, arrSize);
    
    //Change the index in the max heap to match the index in the min heap
    //after percolating down
    maxHeap->heapArray[minHeap->heapArray[numIndex].index].index = numIndex;
    maxHeap->fixHeap(minHeap, hole);
    m_size--;
    return temp; 
}

//deleteMax() - Removes the largest item in the min-max heap and returns
//the key value of the deleted item
template <typename T>
T MinMaxHeap<T>::deleteMax(){
    
    keyVal maxValArray[m_capacity];
    int indexArray[m_capacity];
    int arrSize = 0;
    int numIndex;
    
    //Grabs the corresponding index in the max heap
    int hole = maxHeap->heapArray[1].index;
    
    //Stores the original max value to return at the end of function
    T temp = maxHeap->heapArray[1].m_data;
    
    //Replaces the maximum value with the value in the deepest leaf to the right,
    //and numIndex will store the index value of the data after percolating down.
    //swapVals() will update the index value for the data that were previously
    //swapped.
    maxHeap->heapArray[1] = maxHeap->heapArray[m_size];
    numIndex = maxHeap->fixDelete(maxValArray,indexArray, arrSize);
    maxHeap->swapVals(minHeap, maxValArray, indexArray, arrSize);
    minHeap->heapArray[maxHeap->heapArray[numIndex].index].index = numIndex;
    minHeap->fixHeap(maxHeap, hole);
    m_size--;

    return temp;
}

//locateMin(): The data parameter should hold the value of the item in position
//'pos' of the min-heap. The index parameter should hold the location of the item's
//"twin" in the other heap.
template <typename T>
void MinMaxHeap<T>::locateMin(int pos, T& data,int& index){
    data = minHeap->heapArray[pos].m_data;
    index = minHeap->heapArray[pos].index;
}

//locateMax(): Analagous to locateMin()
template <typename T>
void MinMaxHeap<T>::locateMax(int pos, T& data, int& index){
    data = maxHeap->heapArray[pos].m_data;
    index = maxHeap->heapArray[pos].index;
}


//Dump()
template <typename T>
void MinMaxHeap<T>::dump(){
    
    cout << ". . . MinMaxHeap::dump() ..." << endl;
    cout << endl;
    cout << "------------Min Heap------------" << endl;
    minHeap->dump();
    cout << endl;
    cout << "------------Max Heap------------" << endl;
    maxHeap->dump();
    cout << "--------------------------------" << endl;
    cout << endl;
}

//Heaps Constructor
template <typename T>
MinMaxHeap<T>::Heaps::Heaps(int capacity){
    m_capacity = capacity;
    heapArray = new keyVal[capacity+1];
    size = 0;
}

//Destructor
template <typename T>
MinMaxHeap<T>::Heaps::~Heaps(){
    delete [] heapArray;
    heapArray = NULL;
}

template <typename T>
int MinMaxHeap<T>::Heaps::insert(const T& data, keyVal pairArray[], int indexArray[], int &arrSize){

    keyVal pairVal;
    pairVal.m_data = data;
    
    //Set index = 'size + 1' to insert the data into the next available position in
    //the array. Index will then store the new index of the data after
    int index = size+1;
    index = percolateUp(index, data, pairArray,indexArray, arrSize);
    pairVal.index = index;
    heapArray[index] = pairVal;
    size++;
    
 return index;
}
template <typename T>
int MinMaxHeap<T>::Heaps::percolateUp(int hole, const T& data, keyVal pairArray[], int indexArray[], int &arrSize){
   
    //This function swaps the parent and child for the given heap, depending on
    //the condition, to maintain the heap shape.
    for( ; hole > 1 && m_comparison(data,heapArray[hole/2].m_data); hole /= 2){
        heapArray[hole] = heapArray[hole/2];
        pairArray[arrSize] = heapArray[hole/2];
        indexArray[arrSize] = hole;
        arrSize++;
    }
  
    return hole;
}

template <typename T>
int MinMaxHeap<T>::Heaps::percolateDown(int hole, const T& data, keyVal pairArray[], int indexArray[], int &arrSize){

    //Depending on the heap condition, the parent and it's child
    //will be swapped to maintain the shape. If the child is greater
    //than it's parent then they will need to be swapped to meet the Max
    //Heap condition. If the child is smaller then they will swap with their
    //parent to maintain the Min Heap shape.
    int child;
    for(;hole * 2 <= size; hole = child){
        child = hole * 2;
        if(child != size && m_comparison(heapArray[child+1].m_data, heapArray[child].m_data)){
            child++;
        }
        if(m_comparison(heapArray[child].m_data, data)){
            pairArray[arrSize] = heapArray[child];
            indexArray[arrSize] = hole;
            heapArray[hole] = heapArray[child];
            arrSize++;
        }
        else{ break;}
    }
    return hole;
}

//swapVals(): Updates the corresponding twin heap so that the data has
//the correct index value associated with it.
template <typename T>
void  MinMaxHeap<T>::Heaps::swapVals(Heaps *nextHeap, keyVal pairArray[],int indexArray[] , int &arrSize){
    
    if(arrSize != 0){
        for(int i = 0; i < arrSize; i++){
            nextHeap->heapArray[pairArray[i].index].index = indexArray[i];
        }
    }
}

template <typename T>
int MinMaxHeap<T>::Heaps::fixDelete(keyVal maxValArray[], int indexArray[], int &arrSize){
   
    T temp = heapArray[1].m_data;
    keyVal temp2 = heapArray[1]; 
    int hole = 1;
    hole = percolateDown(hole, temp, maxValArray, indexArray, arrSize);
    heapArray[hole] = temp2;
    size--;
    return hole;
}

template <typename T>
void MinMaxHeap<T>::Heaps::fixHeap(Heaps* nextHeap, int hole){
  
    //After deleting in the min/max heap, if the hole in the
    //twin heap is equal to the size then decrement size
    if(hole == size){
        size--;
    }
    else{
        
        keyVal pairArray[m_capacity];
        int indexArray[m_capacity];
        int arrSize = 0;
        keyVal pairVal;
        
        //Replace the empty hole in the heap with the values
        //in the deepest leaf to the right
        heapArray[hole] = heapArray[size];
        T data = heapArray[hole].m_data;
        pairVal = heapArray[hole];
        
        //PercolateUp to ensure that the shape of the heap is maintained.
        //'hole' will store the index after 'data' has been swapped into
        //it's correct location. Change the index in the other heap to match
        //the replacement.
        hole = percolateUp(hole, data, pairArray,indexArray,arrSize);
        heapArray[hole] = pairVal;
        nextHeap->heapArray[heapArray[hole].index].index = hole;
        
        //Swap the values so that the heap has the updated
        //index values to match it's twin.
        swapVals(nextHeap, pairArray, indexArray, arrSize);
        size--;
    }
}

template <typename T>
void MinMaxHeap<T>::Heaps::dump(){
    cout << "size = " << size << ", capacity = " << m_capacity << endl;
    for(int i = 1; i <= size; i++){
        cout << "Heap[" << i<<"]" << " = (" << heapArray[i].m_data << "," <<  heapArray[i].index << ")"<< endl;
    }
    
}
//maxProperty() returns true if the data you want to insert is greater than its parent
template <typename T>
bool maxProperty( const T& data, const T& data2){
    return data > data2;
}

//minProperty() returns true if the data you want to insert is less than its parent
template <typename T>
bool minProperty(const T& data, const T& data2){
    return data < data2;
}
#endif




