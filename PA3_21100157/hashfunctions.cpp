#ifndef HASHFUNCTIONS_CPP
#define HASHFUNCTIONS_CPP
#include <string>
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;
// this takes in a string and returns a 64bit hash.
unsigned long polyHash(std::string value,int a = 9)
{
	/**Working: for example we have  H e l l o and its corresponding ASCII codes are 72 101 108 108 111
       then polyHash("Hello") = 72a^4 + 101a^3 + 108a^2 + 108a^1 + 111a^0**/

    unsigned long hasher = 0 ;
    for (int i = 0 ; i < value.length() ; i++)
    {
        char character = value[i] ;
        hasher = int(character) + a*hasher ;
    }
    return hasher ;

}

//does some bitwise operation and generates a 64bit hash.
unsigned long bitHash(std::string value)
{
	unsigned long bitwise_hash = 0 ;
    for (int i = 0 ; i < value.length() ; i++)
    {
        bitwise_hash ^= (bitwise_hash << 5) + (bitwise_hash >> 2) + int(value[i]) ;
    }
    return bitwise_hash ;
}

// Size is the size of array maintained by the hashtable.
unsigned long divCompression(unsigned long hash,long size)
{
	unsigned long final_index = hash % size ;
    return final_index ;
}

// multiplication addition and division compression. 
unsigned long madCompression(unsigned long hash,long size,int m = 1993,int a = 1637)
{
	unsigned long final_index =  (a*hash + m) % size ;
    return final_index ;
}

#endif

// you may write your own program to test these functions.