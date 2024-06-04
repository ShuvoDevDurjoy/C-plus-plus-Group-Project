
#ifndef QUEUELINKED_H
#define QUEUELINKED_H

#include <iostream>

template <class T>
class QueueNode
{
public:
    T data;
    QueueNode<T>* next;

    QueueNode(T data) : data(data), next(nullptr) {}
};

template <class T>
class QueueLinked
{
private:
    QueueNode<T>* front;
    QueueNode<T>* rear;

public:
    QueueLinked() : front(nullptr), rear(nullptr) {}

    void Enqueue(T data);
    bool Dequeue(T& data);
    bool IsEmpty();
    void Print();
    void Clear();
    ~QueueLinked();
};

#endif // QUEUELINKED_H