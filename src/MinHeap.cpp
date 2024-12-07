#include "../src/MinHeap.h"

MinHeap::MinHeap(int cap) : size(0), capacity(cap)
{
    heap = new Node[cap];
}

void MinHeap::swap(Node &a, Node &b)
{
    Node temp = a;
    a = b;
    b = temp;
}

void MinHeap::heapifyUp(int index)
{
    while (index > 0 && heap[(index - 1) / 2].dist > heap[index].dist)
    {
        swap(heap[(index - 1) / 2], heap[index]);
        index = (index - 1) / 2;
    }
}

void MinHeap::heapifyDown(int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heap[left].dist < heap[smallest].dist)
    {
        smallest = left;
    }

    if (right < size && heap[right].dist < heap[smallest].dist)
    {
        smallest = right;
    }

    if (smallest != index)
    {
        swap(heap[smallest], heap[index]);
        heapifyDown(smallest);
    }
}

void MinHeap::insert(Node node)
{
    if (size == capacity)
        return; // If heap is full
    heap[size] = node;
    heapifyUp(size);
    size++;
}

MinHeap::Node MinHeap::extractMin()
{
    if (size == 0)
        return {INT_MAX, '\0'};

    Node root = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0);
    return root;
}

bool MinHeap::isEmpty()
{
    return size == 0;
}
