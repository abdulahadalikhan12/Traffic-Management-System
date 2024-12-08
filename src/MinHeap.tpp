#include "MinHeap.h"

template <typename T>
MinHeap<T>::MinHeap(int cap) : size(0), capacity(cap)
{
    heap = new Node[capacity];
}

template <typename T>
MinHeap<T>::~MinHeap()
{
    delete[] heap;
}

template <typename T>
void MinHeap<T>::swap(Node &a, Node &b)
{
    Node temp = a;
    a = b;
    b = temp;
}

template <typename T>
int MinHeap<T>::parent(int index)
{
    return (index - 1) / 2;
}

template <typename T>
int MinHeap<T>::left(int index)
{
    return (2 * index) + 1;
}

template <typename T>
int MinHeap<T>::right(int index)
{
    return (2 * index) + 2;
}

template <typename T>
void MinHeap<T>::heapifyUp(int index)
{
    while (index != 0 && heap[parent(index)].priority > heap[index].priority)
    {
        swap(heap[index], heap[parent(index)]);
        index = parent(index);
    }
}

template <typename T>
void MinHeap<T>::heapifyDown(int index)
{
    int smallest = index;
    int l = left(index);
    int r = right(index);

    if (l < size && heap[l].priority < heap[smallest].priority)
        smallest = l;
    if (r < size && heap[r].priority < heap[smallest].priority)
        smallest = r;

    if (smallest != index)
    {
        swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}

template <typename T>
void MinHeap<T>::insert(Node node)
{
    if (size == capacity)
    {
        std::cerr << "Heap overflow: cannot insert more elements\n";
        return;
    }

    heap[size] = node;
    size++;
    heapifyUp(size - 1);
}

template <typename T>
typename MinHeap<T>::Node MinHeap<T>::extractMin()
{
    if (isEmpty())
    {
        std::cerr << "Heap underflow: no elements to extract\n";
        return Node{INT_MAX, T()};
    }

    Node root = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0);
    return root;
}

template <typename T>
bool MinHeap<T>::isEmpty()
{
    return size == 0;
}
