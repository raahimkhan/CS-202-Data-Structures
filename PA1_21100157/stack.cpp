#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"

template <class T>
Stack<T>::Stack()
{
	/**Remains empty**/
}
    
template <class T>
Stack<T>::Stack(const Stack<T>& otherStack) : list(otherStack.list)
{
	/**Remains empty**/
}

template <class T>
Stack<T>::~Stack()
{
	/**Remains empty**/
}

template <class T>
void Stack<T>::push(T item)
{
	list.insertAtHead(item) ;
}

template <class T>
T Stack<T>::top()
{
	return list.getHead() -> value ;
}

template <class T>
T Stack<T>::pop()
{
	T temp = list.getHead()->value;
	list.deleteHead();
    return temp;
}

template <class T>
int Stack<T>::length()
{
	return list.length();
}

template <class T>
bool Stack<T>::isEmpty()
{
	int stack_length = list.length() ;
	if (stack_length == 0)
	{
		return true ;
	}
	return false ;
}

#endif
