//Abstract data type for a linked list
#ifndef _LINKED_LIST_ADT_H
#define _LINKED_LIST_ADT_H


template<typename T>
class LinkedListADT
{
    public:
    //insert an item at the beginning of the list
    void InsertFirst(const T& data) = 0;
    
    //insert an item at the end of the list
    void InsertLast(const T& data) = 0;

    /*assign the item with the specified index to the item parameter passed by refrence 
     return true if the index was in the range of the linked list and item was found
    return false if index was beyond the range of the linked list*/
    bool GetItem(T& item, int index) = 0;

    /*edit the content of an already exisiting node with the specified index to the passed data 
     return true if the index was in the range of the linked list and item was found
    return false if index was beyond the range of the linked list*/
    bool SetItem(const T& item, int index) = 0;


    /*delete the item with the specified index
    return true if the index was in the range of the linked list and item was deleted
    return false if index was beyond the range of the linked list*/
    bool DeleteItem(int index) = 0;
};

#endif