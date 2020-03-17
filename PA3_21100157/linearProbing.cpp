#ifndef LINEARPROBING_CPP
#define LINEARPROBING_CPP

#include "linearProbing.h"
#include "hashfunctions.cpp"


HashL::HashL()
{
    tableSize = 1000 ; // you cant change this  (OK!)
    count = 0 ;
    
    hashTable = new block *[tableSize] ; 
          
    for(int i = 0 ; i < tableSize ; i++) 
    	hashTable[i] = NULL ; 
}

HashL::~HashL()
{
    
}

unsigned long HashL :: hash(string value)
{
	unsigned long index = bitHash(value) ;
	unsigned long final_index = madCompression(index , tableSize) ;
	return final_index ;
}

void HashL::resizeTable()
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

			while(temp[index] != NULL)
			{
				index = (index + 1) % tableSize ;
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

void HashL::insert(string value)
{
	if((count*1.0)/tableSize > 0.5)
	{
		resizeTable() ;
	}

	unsigned long index = hash(value) ;
	while(hashTable[index] != NULL)
	{
		index = (index + 1) % tableSize ;
	}

	hashTable[index] = new block(index , value) ;
	count++ ;
}

void HashL::deleteWord(string value)
{
	unsigned long index = hash(value) ;

	while(hashTable[index] != NULL)
	{
		if(hashTable[index] -> value == value) 
        { 
            hashTable[index] = NULL ; 
            count-- ; 
            return ;
        } 

        index = (index + 1) % tableSize ;
    }
}

block* HashL::lookup(string value)
{
	unsigned long index = hash(value) ; 
    int counter = 0 ; 
          
    while(hashTable[index] != NULL) 
    {    
        if(counter++ > count)  
            return NULL ;         
           
        if(hashTable[index] -> value == value) 
            return hashTable[index] ; 

        index = (index + 1) % tableSize ;
    } 
        
    return NULL; 
}

#endif
