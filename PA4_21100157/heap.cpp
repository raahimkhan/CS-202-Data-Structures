#ifndef __HEAP_CPP
#define __HEAP_CPP
#include "heap.h"

MinHeap::MinHeap(int cap)
{
    heap_size = 0 ;
    capacity = cap ;
    harr = new int [cap] ;
}

void MinHeap::MinHeapify(int i)
{
    int min = i ;

    if (left(i) < heap_size && harr[left(i)] < harr[min])
        min = left(i) ;

    if (right(i) < heap_size && harr[right(i)] < harr[min])
        min = right(i) ;

    if (min != i)
    {
        int temp = harr[i] ;
        harr[i] = harr[min] ;
        harr[min] = temp ;
        MinHeapify(min) ;
    }
}

int MinHeap::parent(int i)
{
    return (i - 1)/2 ;
}

int MinHeap::left(int i)
{
    return (2 * i + 1) ;
}

int MinHeap::right(int i)
{
    return (2 * i + 2) ;
}

int MinHeap::extractMin()
{
    if (heap_size <= 0)
        return -1 ;

    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }

    // Store the minimum value, and remove it from heap
    int root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    MinHeapify(0);

    return root;
}

void MinHeap::decreaseKey(int i, int new_val)
{
    harr[i] = new_val ;
    while (i != 0 && harr[parent(i)] > harr[i])
    {
       int temp = harr[i] ;
       harr[i] = harr[parent(i)] ;
       harr[parent(i)] = temp ;

       i = parent(i) ;
    }
}

int MinHeap::getMin()
{
    return harr[0] ;
}

void MinHeap::deleteKey(int i)
{
    if (i >= heap_size)
        return ;

    decreaseKey(i, -1);
    extractMin();
}

void MinHeap::insertKey(int k)
{
    if (heap_size == capacity)
        return ;

    //First increase the heap size
    heap_size = heap_size + 1 ;

    //Now insert the new element after the last inserted element
    harr[heap_size - 1] = k ;

    //Now upheap if heap property is violated
    int last_inserted = heap_size - 1 ;

    while (last_inserted != 0 && harr[parent(last_inserted)] > harr[last_inserted])
    {
       int temp = harr[last_inserted] ;
       harr[last_inserted] = harr[parent(last_inserted)] ;
       harr[parent(last_inserted)] = temp ;

       last_inserted = parent(last_inserted) ;
    }
}

int* MinHeap::getHeap()
{
	return harr ;
}

#endif
