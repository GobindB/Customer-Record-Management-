#ifndef LinkedList_h
#define LinkedList_h

#include "LinkNode.h"
#include <iostream>
#include <string>
//=====================================================================================
// Linked List
//=====================================================================================

template <typename U>
class LinkedList;

template <typename T>
class LinkedList
{
private:
    LinkNode<T> *head;
    LinkNode<T> *tail;
    int count;
    int sort; //0:unsorted 1:ascending 2:descending

public:
    LinkedList(int = 0);
    virtual ~LinkedList();

    int getSort() const;//getter for a sorting type of a list
    int getCount() const;//getter for a count
    void emptyList();//clear out all nodes in a list

    void print(std::ostream &) const;// prints out list

    void addData(T); // create new node and add it to a list
    int addData(T, int);// create new node and add it to a list to a given location

    bool deleteData(T);//deletes one node of delData value

    int findData(T);//find a node that has given data
    bool isEmpty();//check if its empty

    void setTail(); //already efficiently incorporated in the add and delete functions so this function exists only for potential future use
    T& getTail();
    


};



/*Constructor for the LinkedList. Sets count to 0. Creates the head and makes it point to nullptr.
Pre: sortType - integer which determines if the data will be sorted or unsorted
Post: modifies the head next
Return:
*/
template <typename T>
LinkedList<T>::LinkedList(int sortType)
    : count(0) //initialize count to 0
{
    head = new LinkNode<T>;
    head->setNext(nullptr);
    tail = nullptr;

    if (sortType < 0 || sortType > 2) //if sortType is neither 0, 1, or  2, set it to 0: unsorted
        sortType = 0;
    sort = sortType;
}


/* Destructor deletes all the nodes and the head. Frees memory
Pre:
Post: deltes everything.
Return:
*/
template <typename T>
LinkedList<T>::~LinkedList()
{
    LinkNode<T> *currPtr;
    LinkNode<T> *nextPtr;
    currPtr = head->getNext();

    while (currPtr != nullptr)
    {
        nextPtr = currPtr->getNext();
        delete currPtr;
        currPtr = nextPtr;
    }

    delete head;
}


/* prints the output of the array.
Pre:
Post:
Return:
*/
template <typename T>
void LinkedList<T>::print(std::ostream &os) const
{
    LinkNode<T> *currPtr;
    currPtr = head->getNext();

    while (currPtr != nullptr)
    {
        os << currPtr->getData() << std::endl;
        currPtr = currPtr->getNext();
    }
}


/* Adds data to the link list. Creates a new node.
Pre: newData - type T. template type
Post:
Return:
*/
template <typename T>
void LinkedList<T>::addData(T newData)
{
    LinkNode<T> *newNode = new LinkNode<T>;
    newNode->setData(newData);
    LinkNode<T> *currPtr;
    LinkNode<T> *prePtr;

    prePtr = head;
    currPtr = head->getNext();


    switch (sort)
    {
    case 0: //if unsorted
    {
        while (currPtr != nullptr) //goes to end of the list
        {
            prePtr = currPtr;
            currPtr = currPtr->getNext();
        }
        break;
    }
    case 1: //ascending order
    {
        while (currPtr != nullptr && newNode->getData() > currPtr->getData()) //newNode will be between smaller and larger value
        {
            prePtr = currPtr;
            currPtr = currPtr->getNext();
        }
        break;
    }
    case 2: //descending order
    {
        while (currPtr != nullptr && newNode->getData() < currPtr->getData()) //newNode will be between larger and smaller value
        {
            prePtr = currPtr;
            currPtr = currPtr->getNext();
        }
        break;
    }
    default:
        break;
    }

    prePtr->setNext(newNode);
    newNode->setNext(currPtr);
    ++count; //increment the count


    if (newNode->getNext() == nullptr)
        tail = newNode;
    //setTail(); not needed but may be useful later
}



/* adds data to unsorted list by position. Returns -1 if the list is sorted because this operation would not be allowed.
Pre: newData - T data
position - int index of newNode
Post:
Return: int - position. returns -1 if this operation fails.
*/
template <typename T>
int LinkedList<T>::addData(T newData, int position)
{
    if (sort != 0) //if sort type is not unsorted
        return -1;
    else if (position < 0 || position > count) //if position out of bounds
    {
        return -1;
    }

    LinkNode<T> *newNode;
    newNode = new LinkNode<T>;
    newNode->setData(newData);


    LinkNode<T> *currPtr;
    LinkNode<T> *prePtr;

    prePtr = head;
    currPtr = head->getNext();


    int index = 0;
    while (currPtr != nullptr && index < position) //goes to index
    {
        prePtr = currPtr;
        currPtr = currPtr->getNext();

        ++index;
    } //currPtr is now on index position
    prePtr->setNext(newNode);
    newNode->setNext(currPtr); //inserted behind index position, becomes the new index position

    ++count;

    if (newNode->getNext() == nullptr)
        tail = newNode;
    //setTail(); //not needed but may be useful later
    return position;
}



/* deletes one node of delData value
Pre: delData - T data to be deleted
Post:
Return: true or false. false if data not found in list. true otherwise
*/
template <typename T>
bool LinkedList<T>::deleteData(T delData)
{
    bool deleted = false;
    LinkNode<T> *currPtr;
    LinkNode<T> *prePtr;

    prePtr = head;
    currPtr = head->getNext();

    while (currPtr != nullptr && currPtr->getData() != delData)
    {
        prePtr = currPtr;
        currPtr = currPtr->getNext();
    }
    if (currPtr != nullptr)
    {
        deleted = true;
        prePtr->setNext(currPtr->getNext());
        delete currPtr;
        --count;
    }


    if (!isEmpty() && prePtr->getNext() == nullptr)
        tail = prePtr;

    return deleted;
}



/* empies the list out except for the head.
Pre:
Post: list is now empty. head points to null
Return:
*/
template <typename T>
void LinkedList<T>::emptyList()
{
    LinkNode<T> *currPtr = head->getNext();
    LinkNode<T> *nextPtr;

    while (currPtr != nullptr)
    {
        nextPtr = currPtr->getNext();
        delete currPtr;
        currPtr = nextPtr;
        --count;
    }
    head->setNext(nullptr);

    tail = nullptr;
}



/* looks for data in the linked list.
Pre: search - T
Post:
Return: int - returns the index of the search value node
*/
template <typename T>
int LinkedList<T>::findData(T search)
{
    int notFoundIndex = -1;
    int index = 0;

    LinkNode<T> *currPtr;
    currPtr = head->getNext();

    while (currPtr != nullptr)
    {
        if (currPtr->getData() == search)
        {
            return index;
        }
        currPtr = currPtr->getNext();
        ++index;
    }
    return notFoundIndex;
}

/*
Pre:
Post:
Return: int - number of nodes in a list
*/
template <typename T>
int LinkedList<T>::getCount() const
{
    return count;
}

/*
Pre:
Post:
Return: int - type of order
*/
template <typename T>
int LinkedList<T>::getSort() const
{
    return sort;
}

/*
Pre:
Post:
Return: bool - whether if it is empty
*/
template <typename T>
bool LinkedList<T>::isEmpty()
{
    if (count == 0)
        return true;
    else
        return false;
}


/* finds the tail of the list. not always needed (more efficient ways implemented in the program)
Pre:
Post: sets tail member to the rear of the list
Return:
*/
template <typename T>
void LinkedList<T>::setTail()
{
    LinkNode<T> *currPtr;
    currPtr = head->getNext();

    while (currPtr->getNext() != nullptr)
    {
        currPtr = currPtr->getNext();
    }
    tail = currPtr;
}


/* gets the tail
Pre:
Post:
Return: T - the rear of the list. modifiable if needed.
*/
template <typename T>
T& LinkedList<T>::getTail()
{
    if (tail != nullptr)
    {
        return tail->getData();
    }
    else
        return head->getData();
}


 

#endif
