#ifndef QUADRATICPROBING_CPP
#define QUADRATICPROBING_CPP

#include "quadraticProbing.h"
#include "hashfunctions.cpp"


HashQ::HashQ()
{
    tableSize = 1000 ; // you cant change this  (OK!)
    count = 0 ;

    hashTable = new block *[tableSize] ;

    for(int i = 0 ; i < tableSize ; i++)
    	hashTable[i] = NULL ;
}

HashQ::~HashQ()
{

}

unsigned long HashQ :: hash(string value)
{
	unsigned long index = bitHash(value) ;
	unsigned long final_index = madCompression(index , tableSize) ;
	return final_index ;
}

void HashQ::resizeTable()
{
	int original = tableSize ;
	tableSize = tableSize * 2 ;
	block **temp = new block*[tableSize] ;

	for (int i = 0 ; i < tableSize ; i++)
		temp[i] = NULL ;

	for (int i = 0 ; i < original ; i++)
	{
		if (hashTable[i] != NULL)
		{
			unsigned long index = hash(hashTable[i] -> value) ;

			int j = 0 ;

            while (temp[index] != NULL) //Until empty space found
            {
                index = (index + (j * j)) % tableSize ;  // h(k) = (k + j^2) mod N
                j++ ;
            }

            temp[index] = new block(index , hashTable[i] -> value) ;
        }
	}

	for (int i = 0 ; i < original ; i++)
	{
		delete hashTable[i] ;
	}

	delete hashTable ;
	hashTable = temp ;
	temp = NULL ;
}

void HashQ::insert(string value)
{
	if((count*1.0)/tableSize > 0.4)
	{
		resizeTable() ;
	}

	unsigned long index = hash(value) ;

	int j = 0 ;

    while (hashTable[index] != NULL) //Until empty space found
    {
        index = (index + (j * j)) % tableSize ;  // h(k) = (k + j^2) mod N
        j++ ;
    }

    hashTable[index] = new block(index , value) ;
    
    count++ ;
}

void HashQ::deleteWord(string value)
{
	unsigned long index = hash(value) ;

	int j = 0 ;

	while(hashTable[index] != NULL)
	{
		if(hashTable[index] -> value == value)
        {
            hashTable[index] = NULL ;
            count-- ;
            return ;
        }

        index = (index + (j * j)) % tableSize ;

        j++ ;
    }
}

block* HashQ::lookup(string value)
{
	unsigned long index = hash(value) ;
    int counter = 0 ;
    int j = 0 ;

    while(hashTable[index] != NULL)
    {
        if(counter++ > count)
            return NULL ;

        if(hashTable[index] -> value == value)
            return hashTable[index] ;

        index = (index + (j * j)) % tableSize ;

        j++ ;
    }

    return NULL;
}

#endif
