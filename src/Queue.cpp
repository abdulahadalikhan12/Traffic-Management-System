#include "../src/Graph.h"
#include "../src/Queue.h"

queueNode::queueNode()
    : next(NULL), intersection(NULL) {}

Queue::Queue()
{
    this->front = NULL;
    this->rear = NULL;
}

void Queue::enqueue(Intersection *temp)
{
    queueNode *newNode = new queueNode;
    newNode->intersection = temp;

    if (front == NULL)
    {
        front = rear = newNode;
    }

    else
    {
        rear->next = newNode;
        rear = newNode;
    }
}

Intersection *Queue::dequeue()
{
    if (front == NULL)
    {
        return NULL;
    }

    else
    {
        Intersection *temp1 = front->intersection;
        queueNode *temp2 = front;
        front = front->next;

        if (front == NULL)
            rear = NULL;

        delete temp2;

        return temp1;
    }
}

queueNode *Queue::getPointers(int indicator)
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

bool Queue::isEmpty()
{
    return front == NULL;
}