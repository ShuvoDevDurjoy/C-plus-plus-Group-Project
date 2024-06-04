

#include "queuelinked.h"

template <class T>
void QueueLinked<T>::Enqueue(T data)
{
    QueueNode<T> *newNode = new QueueNode<T>(data);

    if (IsEmpty())
    {
        front = newNode;
        rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
}

template <class T>
bool QueueLinked<T>::Dequeue(T &data)
{
    if (IsEmpty())
    {
        return false;
    }

    QueueNode<T> *temp = front;
    data = temp->data;
    front = front->next;

    if (front == nullptr)
    {
        rear = nullptr;
    }

    delete temp;
    return true;
}

template <class T>
bool QueueLinked<T>::IsEmpty()
{
    return front == nullptr;
}

template <class T>
void QueueLinked<T>::Print()
{
    QueueNode<T> *current = front;

    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->next;
    }

    std::cout << std::endl;
}

template <class T>
void QueueLinked<T>::Clear()
{
    QueueNode<T> *current = front;
    QueueNode<T> *next;

    while (current != nullptr)
    {
        next = current->next;
        delete current;
        current = next;
    }

    front = nullptr;
    rear = nullptr;
}

template <class T>
QueueLinked<T>::~QueueLinked()
{
    Clear();
}
