#ifndef CHAINING_CPP
#define CHAINING_CPP
#include "Chaining.h"
#include "hashfunctions.cpp"

HashC::HashC(int size)
{
    tableSize = size ;
    hashTable = new LinkedList <string> [tableSize] ;

}

HashC::~HashC()
{

}

unsigned long HashC :: hash(string input)
{
	unsigned long result = bitHash(input) ;
    unsigned long final_index = madCompression(result , tableSize) ;
    return final_index ;
}

void HashC::insert(string word)
{
	unsigned long index = hash(word) ;
    hashTable[index].insertAtHead(word);
} 

ListItem<string>* HashC :: lookup(string word)
{
	unsigned long index = hash(word) ;
	return hashTable[index].searchFor(word) ;
}

void HashC :: deleteWord(string word)
{
	unsigned long index = hash(word) ;
    hashTable[index].deleteElement(word) ;
}


#endif