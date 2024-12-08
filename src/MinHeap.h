#ifndef MINHEAP_H
#define MINHEAP_H

#include <iostream>
#include <climits>

template <typename T>
class MinHeap
{
public:
    struct Node
    {
        int priority; // key to determine order (e.g., distance, vehicle density, etc.)
        T data;       // generic data type (e.g., int, Road, etc.)
    };

private:
    Node *heap;   // array of nodes
    int size;     // current size of the heap
    int capacity; // maximum capacity of the heap

    void swap(Node &a, Node &b);
    int parent(int index);
    int left(int index);
    int right(int index);
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    MinHeap(int cap);
    ~MinHeap();
    void insert(Node node);
    Node extractMin();
    bool isEmpty();
};

#include "MinHeap.tpp"

#endif // MINHEAP_H
