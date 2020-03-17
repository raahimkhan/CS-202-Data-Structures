#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include "LinkedList.h"

template <class T>
LinkedList<T>::LinkedList()
{
	head = NULL ;
	tail = NULL ;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{
	head = NULL ;
	tail = NULL ;
	ListItem<T> *ptr_copy = otherLinkedList.head ;
	while(ptr_copy != NULL)
	{
		insertAtTail(ptr_copy -> value) ;
		ptr_copy = ptr_copy -> next ;
	}
}

template <class T>
LinkedList<T>::~LinkedList()
{
	ListItem<T> *ptr_node = head ;
	while(ptr_node != NULL)
	{
		ptr_node = ptr_node -> next ;
		deleteHead() ;
	}
	delete head ;
}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{
	ListItem<T> *temp_node = new ListItem<T>(item) ;
	if (head == NULL)   /**If no node has been created yet**/
	{
		temp_node -> next = NULL ;
		temp_node -> prev = NULL ;
		head = temp_node ;
		tail = temp_node ;
	}
	else    /**Insert at head**/ 
	{
		temp_node -> next = head ;
		temp_node -> prev = NULL ;
		head -> prev = temp_node ;
		head = temp_node ;
	}
}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
	ListItem<T> *temp_node = new ListItem<T>(item) ;
	if (tail == NULL) /**If no node has been created yet**/
	{
		temp_node -> next = NULL ;
		temp_node -> prev = NULL ;
		head = temp_node ;
		tail = temp_node ;
	}
	else /**Insert at tail**/
	{
	    temp_node -> prev = tail ;
		temp_node -> next = NULL ;
		tail -> next = temp_node ;
		tail = temp_node ;
	}

}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
	/**We can search using our search function if afterWhat is present or not first**/
	ListItem<T> *temp_node = searchFor(afterWhat) ;
	if (temp_node != NULL) /**If afterWhat has been found in list**/
	{
		if (temp_node -> next == NULL) /**If only 1 node is present or to be inserted after last node**/
		{
			insertAtTail(toInsert) ;
		}
		else
		{
			ListItem<T> *temp_node2 = new ListItem<T>(toInsert) ;
			ListItem<T> *insert_node = new ListItem<T>(toInsert) ;
			temp_node2 = temp_node ;
			temp_node2 = temp_node2 -> next ;
			insert_node -> next = temp_node2 ;
			insert_node -> prev = temp_node ;
			temp_node -> next = insert_node ;
			temp_node2 -> prev = insert_node ;
		}
	}
}

template <class T>
ListItem<T>* LinkedList<T>::getHead()
{
	if (head != NULL)
	{
		return head ;
	}
	else
	{
		return NULL ;
	}
}

template <class T>
ListItem<T>* LinkedList<T>::getTail()
{
	if (tail != NULL)
	{
		return tail ;
	}
	else
	{
		return NULL ;
	}
}

template <class T>
ListItem<T> *LinkedList<T>::searchFor(T item)
{
	ListItem<T> *temp_node = new ListItem<T>(item) ;
    int found = 0 ;
	temp_node = head ;
	while(temp_node != NULL)
	{
		if (temp_node -> value == item)
		{
			found = 1 ;
			goto jump ;
		}

		else
			temp_node = temp_node -> next ;
	}
	jump: if (found == 1)
	{
		return temp_node ;
	}
	else
	{
		return NULL ;
	}
}

template <class T>
void LinkedList<T>::deleteElement(T item)
{
	ListItem<T> *temp_node = searchFor(item) ; /**First search whether item to be deleted present in list or not**/
	if (temp_node != NULL) /**If item found**/
	{
		if (temp_node -> next == NULL) /**If last element**/
		{
			deleteTail() ;
		}
			

		else if (temp_node -> prev == NULL) /**If first element**/
		{
			deleteHead() ;
		}
			

		else /**If in between**/
		{
			temp_node -> prev -> next = temp_node -> next ;
			temp_node-> next -> prev = temp_node -> prev ;
			delete temp_node ;
		}
	}
}

template <class T>
void LinkedList<T>::deleteHead()
{
	if (head != NULL)
	{
	   ListItem<T> *ptr_node = head ;
	   if (ptr_node != tail)
	   {
	      head = head -> next ;
	      head -> prev = NULL ;
	      delete ptr_node ;
	      ptr_node = NULL ;
	   }
	   else
	   {
	   	  delete ptr_node ;
	   	  ptr_node = NULL ;
	   	  head = NULL ;
	   	  tail = NULL ;
	   }
	}
}

template <class T>
void LinkedList<T>::deleteTail()
{
	if (tail != NULL)
	{
	   ListItem<T> *ptr_node = tail ;
	   if (ptr_node != head)
	   {
	      tail = tail -> prev ;
	      tail -> next = NULL ;
	      delete ptr_node ;
	      ptr_node = NULL ;
	   }
	   else
	   {
	   	  delete ptr_node ;
	   	  ptr_node = NULL ;
	   	  head = NULL ;
	   	  tail = NULL ;
	   }
	}
}

template <class T>
int LinkedList<T>::length()
{
	ListItem<T> *ptr_node = head ;
	int counter = 0 ;
	while (ptr_node != NULL)
	{
		counter = counter + 1 ;
		ptr_node = ptr_node -> next ;
	}
	return counter ;
}

#endif
