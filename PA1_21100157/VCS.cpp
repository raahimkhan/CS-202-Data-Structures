#ifndef VCS_CPP
#define VCS_CPP
#include "VCS.h"
#include "string"
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std ;


/*Reason for choosing stack as my container*/
/*Stack is a LIFO (last in first out) data structure hence we can insert different file versions inside it an orderly fashion.
For instance we are currently on V1 we call commit and then V2 would be added to stack top. Similarly its easier to implement undo and redo with stack
since undo would remove current version and it is obvious that previous version would be below it. Same for redo next version would be above the
current version and hence it is much easier with stack to manipulate all these functions*/

//Friendly function to convert from int to string
string int_to_string(int number)
{
	ostringstream strng ;
	strng << number ;
	string converted = strng.str() ;
	return converted ;
}

//base constructor, init
VCS::VCS(string fname)
{
	curr_size = 0 ;
	filename = fname ;
}

//destructor
VCS::~VCS()
{
	while(!container1.isEmpty())
	{
		VCS_node store = container1.pop() ;
	}

	while(!container2.isEmpty())
	{
		VCS_node store2 = container2.pop() ;
	}
}


//time to commit
void VCS::commit(string msg)
{
	VCS_node *version_node = new VCS_node ;
	version_node -> message = msg ;
	version_node -> time_stamp = curr_size ;

	string file = filename + int_to_string(version_node -> time_stamp) + ".txt" ; /**New file created on each commit call**/
	string content ;
	ifstream readfile ; /**For reading from original file**/
	readfile.open((filename + ".txt").c_str()) ;
	ofstream writefile ; /**For writing to file**/
	writefile.open(file.c_str()) ;

	while(getline(readfile,content))
	{
		writefile << content ;
	}

	readfile.close() ;
	writefile.close() ;

	container1.push(*version_node) ; /**Push the node into stack1 or container1**/

	curr_size++ ; /**Increment stack size**/
}

//print status of every version
void VCS::status()
{
	VCS_node temp ;
	int check = 0 ; /**Will print info of last 5 commits only**/
	int count = 0 ; /**To keep check on how many nodes pushed back to original stack**/
	while(!container1.isEmpty() && check < 5)
	{
		container2.push(container1.pop()) ;
		check++ ;
		count++ ;
	}
	while(count > 0)
	{
		temp = container2.top() ;
		cout << "Message :   "<< temp.message <<endl ;
		cout << "Time Stamp :   "<< temp.time_stamp <<endl ;
		cout <<endl ;
		container1.push(container2.pop()) ;
		count-- ;
	}
}

//goes one step back
string VCS::undo()
{
	VCS_node temp ;
	container2.push(container1.pop()) ;
	ifstream infile ;
	ofstream outfile ;
	temp = container1.top() ;


	string line ;
	string content ;
	infile.open((filename + int_to_string(temp.time_stamp) + ".txt").c_str()) ;
	outfile.open((filename + ".txt").c_str()) ;
	while(getline(infile,line))
	{
		outfile << line ;
		content = line ;
	}

	infile.close() ;
	outfile.close() ;
	return content  ;
}

//one step ahead
string VCS::redo()
{
	VCS_node temp ;
	container1.push(container2.pop()) ;
	ifstream infile ;
	ofstream outfile ;
	temp = container1.top() ;


	string line ;
	string content ;
	infile.open((filename + int_to_string(temp.time_stamp) + ".txt").c_str()) ;
	outfile.open((filename + ".txt").c_str()) ;
	while(getline(infile,line))
	{
		outfile << line ;
		content = line ;
	}

	infile.close() ;
	outfile.close() ;
	return content  ;
}

//goes t_stamp step back or ahead
string VCS::revert(int t_stamp)
{
	string content ;
	VCS_node temp ;
	temp = container1.top() ;

	if(t_stamp < temp.time_stamp)  /**If required version less then current version**/
	{
		while(temp.time_stamp != t_stamp)
		{
			content = undo() ;
			temp = container1.top() ;
		}
	}

	else if(t_stamp > temp.time_stamp) /**If required version greater then current version**/
	{
		while(temp.time_stamp != t_stamp)
		{
			content = redo() ;
			temp = container1.top() ;
		}
	}
	return content ;
}

#endif
