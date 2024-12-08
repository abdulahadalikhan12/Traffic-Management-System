#ifndef QUEUE_H
#define QUEUE_H

struct queueNode
{
    queueNode *next;
    Intersection *intersection;

    queueNode();
};

class Queue
{
    queueNode *front;
    queueNode *rear;

public:
    Queue();
    void enqueue(Intersection *temp);
    Intersection *dequeue();
    queueNode *getPointers(int indicator);
};

#endif