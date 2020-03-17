#ifndef NEWLINEARPROBING_CPP
#define NEWLINEARPROBING_CPP

#include "newlinearProbing.h"
#include "hashfunctions.cpp"
#include <sstream>

string int_to_string(int number)
{
	ostringstream strng ;
	strng << number ;
	string converted = strng.str() ;
	return converted ;
}

newHashL::newHashL()
{
    tableSize = 1000 ; // you cant change this  (OK!)
    count = 0 ;

    hashTable = new block *[tableSize] ;

    for(int i = 0 ; i < tableSize ; i++)
    	hashTable[i] = NULL ;
}

newHashL::~newHashL()
{}

unsigned long newHashL :: hash(string value)
{
	unsigned long index = bitHash(value) ;
	unsigned long final_index = madCompression(index , tableSize) ;
	return final_index ;
}

void newHashL::insert(int secret_key , string value)
{
	if(count == tableSize)
	{
	    //least frequency used
	    
        string s_key = int_to_string(secret_key) ; //convert secret_key to string to get its hash

        unsigned long index = hash(s_key) ;

        int lfu = hashTable[index] -> counter ;

        unsigned long replace = index ;

	    for (int i = 0 ; i < tableSize ; i++)
        {
            if (hashTable[i] == NULL)
                continue ;

            if (hashTable[i] -> counter < lfu)
            {
                lfu = hashTable[i] -> counter ;
                replace = i ;
            }
        }

        hashTable[replace] = new block(secret_key , value) ;
       
        hashTable[replace] -> counter = 0 ;
        return ;
    }

    string s_key = int_to_string(secret_key) ; //convert secret_key to string to get its hash

	unsigned long index = hash(s_key) ;

	while(hashTable[index] != NULL)
	{
		index = (index + 1) % tableSize ;
	}

	hashTable[index] = new block(secret_key , value) ;
	hashTable[index] -> counter = 0 ;
	count++ ;
}

block* newHashL::lookup(int secret_key)
{
	string s_key = int_to_string(secret_key) ; //convert secret_key to string to get its hash
    unsigned long index = hash(s_key) ;
    int counter = 0 ;

    while(hashTable[index] != NULL)
    {
        if(counter++ > count)
            return NULL ;

        if(hashTable[index] -> key == secret_key)
        {
            hashTable[index] -> counter = hashTable[index] -> counter + 1 ;
            return hashTable[index] ;
        }


        index = (index + 1) % tableSize ;
    }

    return NULL;
}

#endif
