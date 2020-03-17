#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

template <class T>
Queue<T>::Queue()
{
	/**Remains empty**/
}
    
template <class T>
Queue<T>::Queue(const Queue<T>& otherQueue): list(otherQueue.list)
{
	/**Remains empty**/
}

template <class T>
Queue<T>::~Queue()
{
	/**Remains empty**/
}

template <class T>
void Queue<T>::enqueue(T item)
{
	list.insertAtTail(item) ;
}

template <class T>
T Queue<T>::front()
{
	return list.getHead() -> value ;
}

template <class T>
T Queue<T>::dequeue()
{
	T temp = list.getHead()->value;
	list.deleteHead();
    return temp;
}

template <class T>
int Queue<T>::length()
{
	return list.length() ;
}

template <class T>
bool Queue<T>::isEmpty()
{
	int queue_length = list.length() ;
	if (queue_length == 0)
	{
		return true ;
	}
	return false ;
}


#endif
