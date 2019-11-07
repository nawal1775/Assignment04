//Implementation of the double linked list data structure
#ifndef _DOUBLE_LINKED_LIST_H
#define _DOUBLE_LINKED_LIST_H

#include "LinkedListADT.h" //include the abstract linked list class
#include <iostream>
using namespace std;
//this node struct will be used in the linked list class
template<typename T>
struct Node{ //the node of the list contains the data and pointers to nodes before and after it
    T data;
    Node* next;
    Node* previous;
    Node(const T& r_data) //constructor to set the data and init next and previous to null
    {
        data = r_data;
        next = 0;
        previous = 0;
    }
};

template<typename T>
class DoubleLinkedList //: public LinkedListADT<T>
{
protected:
    Node<T>* head; //pointer to the head node
    Node<T>* tail; // pointer the tail node
    int size; //size or number of nodes in the list
public:
    DoubleLinkedList();
    void InsertFirst(const T& data);
    void InsertEnd(const T& data);
    bool GetItem(T& item, int index) const;
    bool DeleteItem(int index);
    bool SetItem(const T& data, int index);
    int GetSize() const;
    bool DeleteFirst();
    bool DeleteLast();
    ~DoubleLinkedList();
};

/*
Default Constructor
Init head and tail to null
Init size to minus one => empty list*/
template<typename T>
DoubleLinkedList<T>::DoubleLinkedList()
{
    head = 0;
    tail = 0;
    size = -1;
}


/*InsertFirst
takes the data to be inserted in the first item
returns nothing*/
template<typename T>
void DoubleLinkedList<T>::InsertFirst(const T& data)
{
    //create new node and init it with the data passed to the function
    Node<T>* newNode = new Node<T>(data);
    size++; //increment the size as we add a new node
    if (!head) //Special case if there was no nodes in the list
    {
        //set next and previous ptr to null as this is the only node
        newNode->next = 0;
        newNode->previous = 0;
        //head and tail points to the same node as this is the only node
        head = newNode;
        tail = newNode;
        return;
    }

    newNode->next = head; //new head points the old head
    newNode->previous = 0; //new head points to nothing before it
    head->previous = newNode;
    head = newNode; //head equal new head
}

/*InsertEnd
takes the data to be inserted in the last item
returns nothing*/
template<typename T>
void DoubleLinkedList<T>::InsertEnd(const T& data)
{
    //create new node and init it with the data passed to the function
    if (!tail) //Special case if there was no nodes in the list
    {
        InsertFirst(data);
        return;
    }

    Node<T>* newNode = new Node<T>(data);
    size++; //increment the size as we add a new node
    newNode->previous = tail; //new tail points the old tail
    newNode->next = 0; //new tail points to nothing after it
    tail->next = newNode;
    tail = newNode; //tail equal new tail
}

/*GetItem
takes the item to store the data returned from the specified index passed to the function
returns true if index is correct and false if index is beyond range*/
template<typename T>
bool DoubleLinkedList<T>::GetItem(T& data, int index) const
{
    //if index is negative or greater than the size of list return false
    if (index < 0 || index > size)
    {
        return false;
    }

    Node<T>* p; //pointer to traverse the list
    //now decide the most effecient traversal either forward or backward
    if (index <= size / 2) //if index lies in the first half of the list do forward traversing
    {
        p = head; //start traversing from head
        for (int i = 0; i < index; i++) //loop until p points to the node with the desired index
        {
            p = p ->next;
        }
    }
    else //index lies in the second half of the list so do backward traversing
    {
        p = tail; //start traversing from tail
        for (int i = size; i > index; i--) //loop from the end of the list until p points to the node with desired index
        {
            p = p ->previous;
        }
    }
    data = p->data; //store the data inside of our node with the index needed in the data passed parameter passed to the function
    return true; //successful operation so return true
}


/*DeleteItem
takes the index of the node to delete
returns true if index is correct and false if index is beyond range*/
template<typename T>
bool DoubleLinkedList<T>::DeleteItem(int index)
{
    //if index is negative or greater than the size of list return false
    if (index < 0 || index > size)
    {
        return false;
    }
    else if (index == 0) //if it's the first node
    {
        return DeleteFirst();
    }
    else if (index == size) //if it's the last node
    {
        return DeleteLast();
    }

    Node<T>* p; //pointer to traverse the list
    //now decide the most effecient traversal either forward or backward
    if (index <= size / 2) //if index lies in the first half of the list do forward traversing
    {
        p = head; //start traversing from head
        for (int i = 0; i < index; i++) //loop until p points to the node with the desired index
        {
            p = p ->next;
        }
    }
    else //index lies in the second half of the list so do backward traversing
    {
        p = tail; //start traversing from tail
        for (int i = size; i > index; i--) //loop from the end of the list until p points to the node with desired index
        {
            p = p ->previous;
        }
    }
    //get the node before the node we want to delete
    Node<T>* beforeDeleted = p->previous;
    //get the node after the node we want to delete
    Node<T>* afterDeleted = p->next;

    //link beforeDeleted to after deleted and bypass the node we want to delete to remove it from list
    beforeDeleted->next = afterDeleted;
    afterDeleted->previous = beforeDeleted;

    //delete the node with the desired index
    delete p;

    size--; //decrease the size by one as we deleted a node
    return true; //successful operation so return true
}

/*SetItem
takes the new data to store in the node with the passed index
returns true if index is correct and false if index is beyond range*/
template<typename T>
bool DoubleLinkedList<T>::SetItem(const T& data, int index)
{
    //if index is negative or greater than the size of list return false
    if (index < 0 || index > size)
    {
        return false;
    }

    Node<T>* p; //pointer to traverse the list
    //now decide the most effecient traversal either forward or backward
    if (index <= size / 2) //if index lies in the first half of the list do forward traversing
    {
        p = head; //start traversing from head
        for (int i = 0; i < index; i++) //loop until p points to the node with the desired index
        {
            p = p ->next;
        }
    }
    else //index lies in the second half of the list so do backward traversing
    {
        p = tail; //start traversing from tail
        for (int i = size; i > index; i--) //loop from the end of the list until p points to the node with desired index
        {
            p = p ->previous;
        }
    }
    p->data = data; //overwrite the existing data in the node with the passed data
    return true; //successful operation so return true
}


/*GetSize
returns the size of the linked list=> returns the number of nodes in the linked list*/
template<typename T>
int DoubleLinkedList<T>::GetSize() const
{
    return size;
}

/*DeleteFirst
Deletes the first node on the list
returns false if list is empty*/
template<typename T>
bool DoubleLinkedList<T>::DeleteFirst()
{
    if (!head) //if list is empty
    {
        return false;
    }

    //set the previous pointer of the node after head to null
    Node<T>* afterHead = head->next;
    if (afterHead) //if after head in not null set its previous to null
    {
        afterHead->previous = 0;
    }

    //delete head
    delete head;
    head = afterHead;
    size--;
    return true;
}


/*DeleteLast
Deletes the last node on the list
returns false if list is empty*/
template<typename T>
bool DoubleLinkedList<T>::DeleteLast()
{
    if (!tail) //if list is empty
    {
        return false;
    }

    //set the previous pointer of the node after head to null
    Node<T>* beforeTail = tail->previous;
    if(beforeTail) //if beafore tail in not null set its next to null
    {
        beforeTail->next = 0;
    }

    //delete head
    delete tail;
    tail = beforeTail;
    size--;
    return true;
}


/*Destructor
free all the memory used by the list by deleting all nodes*/
template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
    //p will be used to treaverse the list, it is intialized to head
	Node<T>* p = head;
	while (head) //while the head pointer still points to a node
	{
		p = head->next; //Let p points to the node after the head
		delete head; //delete the head
		head = p; //Now the new head points to P
	}
	size = 0; //after all nodes are deleted the count of the list is zero
}

#endif
