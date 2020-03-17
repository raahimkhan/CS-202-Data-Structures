#ifndef __DICTIONARY_CPP
#define __DICTIONARY_CPP
#include "dictionary.h"
#include "bst.h"
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std ;

int how_many ;

void menu()
{
	cout << "Press 1 to search word" <<endl ;
	cout << "Press 2 to delete word" <<endl ;
	cout << "Press 3 to insert word" <<endl ;
	cout << "Press 4 to edit word" <<endl ;
	cout << "Press 0 to exit" <<endl ;
	cout <<endl ;
}

Dictionary::Dictionary() 
{
	wordsTree = NULL ;
}

Dictionary::~Dictionary()
{
	if (wordsTree != NULL)
    {
       delete wordsTree;
    }

    wordsTree = NULL ;
}

void Dictionary::initialize(string wordsFile) 
{
	ifstream file_read ;
	file_read.open((wordsFile + ".txt").c_str()) ;
	string line ;
	string inserted ;
	int counter = 0 ;
	wordsTree = new BST<string> ;

	if (file_read)
	{
	    while(getline(file_read , line))
	    {
	    	inserted = line ;
		    cout << inserted << "  inserted from file" <<endl ;
		    wordsTree -> insert(line ,line) ;
		    counter++ ;
		    if (counter == how_many)
		    	break ;
	    }

	    file_read.close() ;

	    cout << counter << "   " << "words inserted in tree" <<endl ;
    }

    else
    {
    	cout << "File not found!" <<endl ;
    	return ;
    }
}

bool Dictionary::deleteWord(string word)
{
	if (wordsTree == NULL)
		return false ;

	else
	{
		// first search word
		if (wordsTree -> search(word) != NULL)
		{
			wordsTree -> delete_node(word) ;
            return true;
		}

		else // if word not found
			return false ;
	}
}

bool Dictionary::editWord(string oldWord, string newWord) 
{
	
    if (wordsTree != NULL)
    {
    	node<string>* temp = wordsTree -> search(oldWord) ;

        if (temp == NULL)
        	return false ;
        
        else
        {
            string temp_value = temp -> value ;

            if (!deleteWord(oldWord))
            	return false ;
            
            else
            {
            	wordsTree -> insert(temp_value , newWord) ;
                return true ;
            }
        }
    }

    else
    	return false ;
}

bool Dictionary::insertWord(string word) 
{
	if (wordsTree != NULL)
	{
		wordsTree -> insert(word , word) ;

        if (wordsTree -> search(word) != NULL)
        	return true ;

        else
        	return false ;

	}

	else
		return false ;
}   
    

node<string>* Dictionary::findWord(string word) 
{
	if (wordsTree != NULL)
    {
        clock_t t;
        t = clock();
        node<string>* temp = wordsTree -> search(word) ;
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds

        if (temp != NULL)
        {
           cout << "findWord() took " << time_taken << "sec to search for " << word << endl;
           return temp ;
        } 

        else
        	return temp ;
    }

    else
    	return NULL ;
}

#endif

int main() 
{
	int choice ;
	Dictionary dict ;

	cout << "How many words to insert in wordsTree :   " ;
	cin >> how_many ;
	cout <<endl ;

    string name ;
	cout << "Enter filename :   " ;
	cin >> name ;

	cout << "Initializing wordsTree!" <<endl ;
	cout <<endl ;
	dict.initialize(name);
	cout <<endl ;

    while(1)
    {

    menu() ;

	loop : cout << "Enter your choice  :  " ;
	cin >> choice ;
	cout <<endl ;

    if (cin.fail())
    {
    	cout << "Strings not allowed!" <<endl ;
    	cin.clear() ;
    	cin.ignore() ;
    	goto loop ;
    }

	if (choice == 1)
	{
		string find ;
		cout << "Enter word to find  :   " ;
		cin >> find ;
		cout <<endl ;
		node<string>* temp = dict.findWord(find) ;
		if (temp != NULL)
        {
            cout << "temp -> val = " << temp -> value <<endl ;
            cout << "Word found!" <<endl ;
        }

        else
        	cout << "Word not found!" <<endl ;
    }

    else if (choice == 2)
    {
    	string del ;
    	cout << "Enter word to delete :   " ;
    	cin >> del ;
    	cout <<endl ;
    	bool status = dict.deleteWord(del) ;
    	if (status == true)
    		cout << "Deleted" <<endl ;

    	else
    		cout << "Word not found or tree is empty" <<endl ;
    }

    else if (choice == 3)
    {
    	string to_insert ;
    	cout << "Enter word to insert  :  " ;
    	cin >> to_insert ;
    	cout <<endl ;
    	bool status = dict.insertWord(to_insert) ; 
    	if (status == true)
    		cout << "Word inserted!" <<endl ;

    	else
    		cout << "Word not inserted!" <<endl ;
    }

    else if (choice == 4)
    {
    	string old ;
    	string new_word ;
    	cout << "Enter old word  :   " ;
    	cin >> old ;
    	cout <<endl ;
    	cout << "Enter new word  :  " ;
    	cin >> new_word ;
    	cout <<endl ;
    	bool status = dict.editWord(old , new_word) ; 
    	if (status == true)
    		cout << "Word edited!" <<endl ;

    	else
    		cout << "Old word not found or the tree is empty!" <<endl ;
    }

    else if (choice == 0)
    {
    	cout << "Program exiting!" <<endl ;
    	return 0 ;
    }

    else
    {
    	cout << "Invalid choice! Please input again" <<endl ;
    	cin.clear() ;
    	cin.ignore() ;
    	goto loop ; 
    }

    cout <<endl <<endl ;

    }

return 0 ;
}
