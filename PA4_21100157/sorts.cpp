#ifndef __SORTS_CPP
#define __SORTS_CPP
#include "sorts.h"
#include "heap.cpp"
#include "list.cpp"

//=====================================================================================

vector<long> InsertionSort(vector<long> nums)
{
	int size = nums.size() ;
	long numbers[size] ;

	for (int i = 0 ; i < nums.size() ; i++)
	{
		numbers[i] = nums[i];
	}

    int x , y ;

	for (int i = 0 ; i < size ; i++)
	{
		x = numbers[i] ;
		y = i - 1 ;

		while (y >= 0 && numbers[y] > x)
		{
			numbers[y + 1] = numbers[y] ;
			y-- ;
		}

		numbers[y + 1] = x ;
	}

	for (int i = 0; i < size; i++)
	{
		nums[i] = numbers[i] ;
	}

    return nums ;
}

//=====================================================================================

ListItem<long>* breaker(ListItem<long> *head_reference)
{
    ListItem<long> *fast = head_reference ;
    ListItem<long> *slow = head_reference ;

    while (fast -> next != NULL && fast -> next -> next != NULL)
    {
        fast = fast -> next -> next ;
        slow = slow -> next ;
    }

    ListItem <long> *final = slow -> next ;

    slow -> next = NULL ;

    return final ;
}

ListItem<long> *merger(ListItem<long> *first_list , ListItem<long> *second_list)
{
    ListItem <long> *firstlist_ref = first_list ;

    ListItem <long> *secondlist_ref = second_list ;

    if (firstlist_ref == NULL)
    {
        return secondlist_ref ;
    }

    if (secondlist_ref == NULL)
    {
        return firstlist_ref ;
    }

    if (firstlist_ref -> value < secondlist_ref -> value)
    {
        firstlist_ref -> next = merger(firstlist_ref -> next , secondlist_ref) ;
        ListItem <long> *temp = firstlist_ref -> next ;
        temp -> prev = firstlist_ref ;
        firstlist_ref -> prev = NULL ;
        return firstlist_ref ;
    }

    else
    {
        secondlist_ref -> next = merger(firstlist_ref , secondlist_ref -> next) ;
        secondlist_ref -> next -> prev = secondlist_ref ;
        secondlist_ref -> prev = NULL ;
        return secondlist_ref ;
    }
}

ListItem<long> *sorter(ListItem<long> *HEAD)
{
    ListItem <long> *head_reference = HEAD ;

    if (head_reference == NULL || head_reference -> next == NULL)
    	return head_reference ;

    else
    {
        ListItem<long> *other_list_ref = breaker(head_reference) ;

        head_reference = sorter(head_reference) ;

        other_list_ref = sorter(other_list_ref) ;

        return merger(head_reference , other_list_ref) ;
    }
}

vector<long> MergeSort(vector<long> nums)
{
	List <long> linked_list ;

    int size = nums.size() ;

    for (int i = 0 ; i < size ; i++)
    {
        linked_list.insertAtHead(nums[i]) ;
    }

    ListItem <long> *sorted_ptr = linked_list.getHead() ;

    sorted_ptr = sorter(sorted_ptr) ;

    int move = 0 ;

    while (sorted_ptr != NULL)
    {
        nums[move] = sorted_ptr -> value ;
        sorted_ptr = sorted_ptr -> next ;
        move++ ;
    }

    return nums ;
}

//=====================================================================================

void QuickSortArray_swap(long* x, long* y)
{
    long temp = *x ;
    *x = *y ;
    *y = temp ;
}

long parts (long sorted[] , long first_index , long last_index)
{
    long f = first_index ;

    long l = last_index ;

	long smaller_element = (f - 1) ;  // Index of smaller element

    long pivot = sorted[l] ;  // Taking pivot to be the last index

    for (int y = f ; y <= l - 1 ; y++)
    {
        //If element at yth index smaller than or equal to our pivot

        if (sorted[y] <= pivot)
        {
            smaller_element += 1 ;

            QuickSortArray_swap(&sorted[smaller_element] , &sorted[y]) ;
        }
    }

    QuickSortArray_swap(&sorted[smaller_element + 1] , &sorted[l]) ;

    long final = smaller_element + 1 ;

    return final ;
}

void QuickSortArray_helper(long sorted[] , long first_index , long last_index)
{
    long f = first_index ;

    long l = last_index ;

    if (f < l)
    {
        long partion_index = parts(sorted , f , l) ; // sorted[partion] is now at right place

        // Sort the elements 2 times. First before partition and second after partition

        long partion_index_inc = partion_index + 1 ;

        long partion_index_dec = partion_index - 1 ;

        QuickSortArray_helper(sorted , f , partion_index_dec) ;
        QuickSortArray_helper(sorted , partion_index_inc , l) ;
    }
}

vector<long> QuickSortArray(vector <long> nums)
{
	int size = nums.size() ;

	long sorted[size] ;

	for(int i = 0 ; i < size ; i++) // copy keys from vector to array
	{
		sorted[i] = nums[i] ;
	}

	QuickSortArray_helper(sorted , 0 , size - 1) ; // pass array , index 0 and last index to helper function for sorting

	for(int i = 0 ; i < size ; i++) //copy back keys from array to vector
	{
		nums[i] = sorted[i] ;
	}

	return nums ;
}

//=====================================================================================

void QuickSortListSWAP(long *x , long *y)
{
	long temp = *x ;
	*x = *y ;
	*y = temp ;
}

ListItem <long> *partition(ListItem <long> *head_reference , ListItem <long> *tail_reference)
{
    long pivot = tail_reference -> value ;  // The pivot is the tail pointer

    ListItem <long> *temp = head_reference -> prev ;  // i = last_index - 1 (in array quicksort)

    for (ListItem <long> *temp2 = head_reference ; temp2 != tail_reference ; temp2 = temp2 -> next)
    {
        if (temp2 -> value <= pivot)
        {
            if (temp == NULL)
            {
            	temp = head_reference ;
            }

            else
            {
            	temp = temp -> next ;
            }

            QuickSortListSWAP(&(temp -> value) , &(temp2 -> value)) ;
        }
    }

    if (temp == NULL)
    	temp = head_reference ;

    else
    	temp = temp -> next ;

    QuickSortListSWAP(&(temp -> value) , &(tail_reference -> value)) ;

    return temp ;
}

void QuickSortListHelper(ListItem <long> *head_reference , ListItem <long> *tail_reference)
{
    ListItem <long> *temp = tail_reference ;

	if (temp != NULL && head_reference != temp && head_reference != temp -> next)
    {
        ListItem <long> *partition_ptr = partition(head_reference , temp) ;

        QuickSortListHelper(head_reference , partition_ptr -> prev) ;

        QuickSortListHelper(partition_ptr -> next , temp) ;
    }
}

vector<long> QuickSortList(vector<long> nums)
{
	List<long> linked_list ;

	int size = nums.size() ;

	for (int i = 0 ; i < size ; i++)
	{
		linked_list.insertAtHead(nums[i]) ;
	}

	ListItem <long> *sorted_ptr_head = linked_list.getHead() ;

	ListItem <long> *sorted_ptr_tail = linked_list.getTail() ;

	QuickSortListHelper(sorted_ptr_head , sorted_ptr_tail) ;

	ListItem <long> *sorted_ptr = linked_list.getHead() ;

    int move = 0 ;

    while (sorted_ptr != NULL)
    {
        nums[move] = sorted_ptr -> value ;
        sorted_ptr = sorted_ptr -> next ;
        move++ ;
    }

    return nums ;
}

//=====================================================================================

vector<long> HeapSort(vector<long> nums)
{
	int size = nums.size();
	MinHeap* heap = new MinHeap(size) ;
	int counter = 0 ;

	for (int i = 0 ; i < nums.size() ; i++)
	{
		heap -> insertKey(nums[i]) ;
		counter++ ;
	}

	for (int i = 0 ; i < counter ; i++)
	{
		int output = heap -> extractMin() ;
		nums[i] = output ;
	}

	return nums ;
}

//=====================================================================================

/**Instead of creating arr of random large size just check the size of input list/vector/array and make arr of double that size.
   This way the need for creating new arrays every time would be greatly minimized. I modified he algorithm such that I made an array
   of linked lists. Hence every index of array is an individual list. For handling duplicates suppose if two values go to same index so they will become
   list type. Meaning 1
                      2 2
                      3
    and so on and this way I handled duplicates. To handle negative numbers I traversed the entire input vector and found the max negative number
    and then added that max negative number to all values of input vector. This way all negative numbers and positive numbers would be converted
    to some new value and we would have list of all positive unsorted numbers. After inserting all numbers at index[i] to index[number] subtract
    back all numbers from max negative which will convert them back to their original form. Finally we now have a sorted list containing duplicates
    as well as negative values handled properly and efficiently.**/

vector<long> QueenOfAllSorts(vector<long> nums)
{
	int size = nums.size() ;
	int new_size = size + size ;
	int max_neg = nums[0] ;
	long index ; // Insert ith element of vector 'nums' at ith index of array

	// Find the max negative number in unsorted vector
    for (int i = 0 ; i < size ; i++)
    {
        if (nums[i] >= 0 || nums[i] == max_neg)
            continue ;

        if (nums[i] < max_neg)
            max_neg = nums[i] ;
    }

    // Convert all numbers so that positive numbers could be indexed (negatives will be converted to positive)
    for (int i = 0 ; i < size ; i++)
    {
        nums[i] = nums[i] - max_neg ;
    }

    List <long> *queen = new List <long> [new_size] ; // array of linked lists

    for (int i = 0 ; i < size ; i++)
    {
    	index = nums[i] ;
    	queen[index].insertAtHead(index) ; // This will cater for duplicates in vector
    }

    vector <long> queen_sort ; // Sorted vector

    for (int i = 0 ; i < new_size ; i++)
    {
    	ListItem <long> *temp = queen[i].getHead() ;

    	if (temp == NULL) // if ith index of array is empty
    		continue ;

    	while(temp != NULL) // cout the element at ith index along with duplicates if any at that index
        {
    		queen_sort.push_back((temp -> value) + max_neg) ; // + max_neg converts back all numbers to their original values
            temp = temp -> next ;
        }
    }

    return queen_sort ;
}

#endif
