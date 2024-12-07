#ifndef MINHEAP_H
#define MINHEAP_H

#include <climits>

class MinHeap
{
public:
    struct Node
    {
        int dist;
        char node;
    };

    Node *heap;
    int size;
    int capacity;

    // swap two nodes
    void swap(Node &a, Node &b);
    // get the parent index of a node
    void heapifyUp(int index);
    // get the left child index of a node
    void heapifyDown(int index);

    // constructor
    MinHeap(int cap);
    //insert a node
    void insert(Node node);
    // extract the minimum node
    Node extractMin();
    // check if the heap is empty
    bool isEmpty();
};

#endif // MINHEAP_H
