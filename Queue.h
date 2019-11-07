/*
This is a program that implements the queue abstract data type using a linked list.
The queue is implemented as a chain of linked nodes that has two pointers,
a frontPtr pointer for the front of the queue and a backPtr pointer for the back of the queue.
*/

/*

				The Node: item of type T and a "next" pointer
					-------------
					| item| next | --->
					-------------
General Queue case:

				 frontPtr																backPtr
					\											   						/
					 \											  					   /
					------------- 	  ------------- 	  ------------- 	  -------------
					| item| next |--->| item| next |--->  | item| next |--->  | item| next |---> NULL
					------------- 	  ------------- 	  ------------- 	  -------------

Empty Case:

				 frontptr	 backptr
						\	 /
						 \	/
					---- NULL ------


Single Node Case:
				 frontPtr	 backPtr
					\		/
					 \	   /
					-----------
					|item| next| -->NULL
					-----------

*/
#ifndef _QUEUE_H
#define _QUEUE_H
#include "DoubleLinkedList.h"

template<typename T>
class Queue : protected DoubleLinkedList<T>
{
public:
    Queue();
    Queue(const Queue<T>& q);
    void Enqueue(const T& data);
    bool IsEmpty() const;
    bool Dqueue(T& data);
    bool Peek(T& data);
    ~Queue();
};

/*Default Constructor
will automatically call the default construcotr of the double linked list class to init head tail and size*/
template<typename T>
Queue<T>::Queue() : DoubleLinkedList<T>() {}


/*Copy Constructor
will do deep copy from a queue to another*/
template<typename T>
Queue<T>::Queue(const Queue<T>& q)
{
    Node<T>* p = q.head;
    while(p)
    {
        this->InsertEnd(p->data);
        p = p->next;
    }
}


/*Enqueue
takes the item to be enqueued at the end of the queue*/
template<typename T>
void Queue<T>::Enqueue(const T& data)
{
    this->InsertEnd(data); //invoke the insert end function in the linked list class passing the data to it
}

/*IsEmpty
return true if queue is empty and false if queue is not empty*/
template<typename T>
bool Queue<T>::IsEmpty() const
{
    //head == 0 returns true if head is null => list empty and returns false otherwise
    return (this->head == 0);
}


/*Dequeue
takes a data parameter passed by reference to store the front of the queue and remove it from the queue
return true if operation successful and false if queue is empty*/
template<typename T>
bool Queue<T>::Dqueue(T& data)
{
    if(IsEmpty()) //if queue is empty return false
    {
        return false;
    }

    //invoke the linked list function to get the item at index zero => front of queue and store it in data
    this->GetItem(data, 0);

    //invoke the linked list function to delete the item at index zero => front of queue
    this->DeleteItem(0);
    return true;
}


/*Dequeue
takes a data parameter passed by reference to store the front of the queue
return true if operation successful and false if queue is empty*/
template<typename T>
bool Queue<T>::Peek(T& data)
{
    if(IsEmpty()) //if queue is empty return false
    {
        return false;
    }

    //invoke the linked list function to get the item at index zero => front of queue and store it in data
    this->GetItem(data, 0);
    return true;
}


/*Destructor
will automatically call the destructor of the double linked list class to delete all nodes and free*/
template<typename T>
Queue<T>::~Queue() {this->~DoubleLinkedList<T>();}



#endif
