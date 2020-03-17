#ifndef DOUBLEHASH_CPP
#define DOUBLEHASH_CPP
#include "doubleHash.h"
#include "hashfunctions.cpp"
HashD::HashD()
{
    tableSize = 10000 ; // you cant change this
    hashTable = new block*[tableSize] ;

    for (int i =0 ; i < tableSize; i++)
	{
        hashTable[i] = NULL;
    }

    count = 0 ;
}

HashD::~HashD()
{

}

unsigned long HashD::hash1(string value)
{
    unsigned long index = bitHash(value) ;
    index = madCompression(index , tableSize) ;
    return index ;
}

unsigned long HashD::hash2(string value)
{
    unsigned long index = 7 - ((bitHash(value)) % 7) ;
    return index ;
}

void HashD::resizeTable()
{
    int original = tableSize ;
    tableSize = tableSize * 2 ;
    block** temp = new block*[tableSize] ;
    
	for (int i = 0 ; i < tableSize ; i++)
	{
        temp[i] = NULL ;
    }

    for (int i = 0 ; i < original ; i++)
    {
        if (hashTable[i] != NULL)
		{
            unsigned long index = (hash1(hashTable[i] -> value)) ;
            int x = 1 ;
            
            while (temp[index] != NULL)
            {
                index = (hash1(hashTable[i] -> value) + (x * (hash2(hashTable[i] -> value)))) % tableSize ;
                x++ ;
            }

            temp[index] = new block(index , hashTable[i] -> value) ;  
        }
        
    }

    for(int i = 0 ; i < original ; i++)
    {
        delete hashTable[i] ;
    }

    delete hashTable ; 
    hashTable = temp ;
    temp = NULL ;
}


void HashD::insert(string value)
{
    if ((count*1.0)/tableSize > 0.3)
	{
        resizeTable() ;
    }

	unsigned long index = hash1(value) ; 
	
    if (hashTable[index] != NULL)  
    { 
        unsigned long index2 = hash2(value) ;  
        int i = 1 ; 
        while (true) 
        { 
            unsigned long newIndex = (index + (i * index2)) % tableSize ;  
            
            if (hashTable[newIndex] == NULL)  
            { 
                hashTable[newIndex] = new block(newIndex , value) ;
                break ; 
            } 

            i++ ; 
        } 
    } 

    else
    {
    	hashTable[index] = new block(index , value) ;
    }
    	
    count++ ; 
}

void HashD::deleteWord(string value)
{
    unsigned long index = hash1(value) ;
    int counter = 0 ;
    int x = 1 ;

    while((hashTable[index] != NULL) && (hashTable[index] -> value != value))
    {
        index = (hash1(value) + (x * hash2(value))) % tableSize ; 
        x++ ;
    }

    if (hashTable[index] != NULL)
    {
        hashTable[index] = NULL ;
        count-- ;
    }
}

block* HashD::lookup(string value)
{
    unsigned long index = hash1(value) ;
    int x = 1 ;

    while((hashTable[index] != NULL) && (hashTable[index] -> value != value) )
    {
        index = (hash1(value) + (x * hash2(value))) % tableSize ;
        x++ ;
    }

    if (hashTable[index] == NULL)
        return NULL ;
    
    else
        return hashTable[index] ;
}

#endif
