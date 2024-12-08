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
    queueNode *getPointers(int indicator)
    { // 1 = front ,  2 = rear
        if (indicator == 1)
            return front;
        else if (indicator == 2)
            return rear;
        else
        {
            std::cout << "Incorrect input.\n";
            return nullptr;
        }
    }
};

#endif