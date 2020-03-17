#include <string>
#include <iostream>
#include <cmath>
#include "hashfunctions.cpp"
#include <cstdlib>

using namespace std;

void menu()
{
    cout << "Press 1 for 'polyHash'" <<endl ;
    cout << "Press 2 for 'bitHash'" <<endl ;
    cout << "Press 0 to exit" <<endl ;
    cout <<endl ;
}

void menu2()
{
    cout << "Press 1 for 'Division Method'" <<endl ;
    cout << "Press 2 for 'MAD Method'" <<endl ;
    cout <<endl ;
}

int main()
{
cout <<endl ;
while(1)
{
menu() ;
char choice ;
loop : cout << "Enter your choice :   " ;
cin >> choice ;
cout <<endl ;
if (choice == '1')
{
string str ;
int a  ;
cout << "Enter a string :   " ;
cin >> str ;
cout <<endl ;
unsigned long result = polyHash(str) ;
cout << "Converted polyHash =   " << result <<endl ;
cout <<endl ;

int table_size ;
cout << "Enter table size :  " ;
cin >> table_size ;
cout <<endl ;
unsigned long index = divCompression(result , table_size) ;
cout << "After polyHash and divCompression final index for  " << str << " is  " << index <<endl ;

cout <<endl ;

unsigned long index2 = madCompression(result , table_size) ;
cout << "After polyHash and madCompression final index for  " << str << " is  " << index2 <<endl ;

cout <<endl ;
system("read -p 'Press Enter to continue...' var") ;
cout <<endl ;
}

else if (choice == '2')
{
string str ;
cout << "Enter a string :   " ;
cin >> str ;
cout <<endl ;
unsigned long result = bitHash(str) ;
cout << "Converted bitHash =   " << result <<endl ;
cout <<endl ;

int table_size ;
cout << "Enter table size :  " ;
cin >> table_size ;
cout <<endl ;
unsigned long index = divCompression(result , table_size) ;
cout << "After bitHash and divCompression final index for  " << str << " is  " << index <<endl ;

cout <<endl ;

unsigned long index2 = madCompression(result , table_size) ;
cout << "After bitHash and madCompression final index for  " << str << " is  " << index2 <<endl ;

cout <<endl ;
system("read -p 'Press Enter to continue...' var") ;
cout <<endl ;
}

else if (choice == '0')
{
    cout << "Program closing!" <<endl ;
    return 0 ;
}

else
{
    cout << "Invalid choice! Enter again" <<endl ;
    cout <<endl ;
    cin.clear() ;
    cin.ignore() ;
    goto loop ;
}
}

return 0 ;
}
