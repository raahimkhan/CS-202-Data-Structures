#include "newlinearProbing.cpp"
#ifndef NEWLINEARPROBING_H
#define NEWLINEARPROBING_H

#include <string>
#include <iostream>

using namespace std;
class block{
    public:
        unsigned long key;
        string value;
        int counter;
        block(unsigned long _key,string _value){
            this->key = _key;
            this->value = _value;
        }
};


class newHashL{
    private:
        block** hashTable;
        long tableSize;
        unsigned long hash(string value); // return the corresponding key of the value
        long count; // keeps a count of the number of entries in the table.

    public:
        newHashL();
        ~newHashL();
        void insert(int secret_key , string value);
		block* lookup(int secret_key);
};

#endif
