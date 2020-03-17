#include <iostream>
#include "newlinearProbing.cpp"
#include "hashfunctions.cpp"
#include <time.h>
#include <stdio.h>
#include <fstream>
using namespace std ;

string dict_search(unsigned long secret_code)
{
  ifstream d("dictionary.txt") ; // Open Dictionary
  string l = "" ;
  unsigned long x = -1 ;
  string word = "" ;
  for(int i = 0 ; i <= secret_code ; i++)
    getline(d , l) ;
  stringstream lineStream(l) ;
  lineStream >> x ;
  lineStream >> word ;
  d.close() ;
  return word ;
}

int main()
{

cout <<endl ;

string which_secret ;
ifstream read_file ; //secret
ifstream read_file2 ; //dictionary

string choice ; //for with cache or without cache

cout << "Press 1 to test without cache" <<endl ;
cout << "Press 2 to test with cache" <<endl ;
cout <<endl ;
loop : cout << "Enter your choice :  " ;
loop2 : cin >> choice ;
cout <<endl ;

if (cin.fail())
{
	cin.clear() ;
	cin.ignore() ;
	cout << "Invalid choice! Please enter again :   " ;
    goto loop2 ;
}

if (choice == "1")
{
cout << "Testing without cache" <<endl ;
cout << "Press 1 for secret1" <<endl ;
cout << "Press 2 for secret2" <<endl ;
cout << "Press 3 for secret3" <<endl ;
cout << "Press 4 to test secrets given in manual file" <<endl ;
cout <<endl ;
again : cout << "Enter your choice :  " ;
cin >> which_secret ;
cout <<endl ;

if (cin.fail())
{
	cout << "Invalid input!" <<endl ;
	cout <<endl ;
	cin.clear() ;
	cin.ignore() ;
    goto again ;
}

if (which_secret == "1")
{
	read_file.open("secret1.txt") ;

    int x ;
    string comma ;
    int looper = 0 ;
    int x_from_dict ;
    string word_from_dict ;

    clock_t t ;
    t = clock() ;

    while (read_file >> x)
    {
      looper++ ;

      if (looper > 10000)
        goto z ;

	  word_from_dict = dict_search(x) ;
    cout << word_from_dict <<endl ;
          
  /*read_file2.open("dictionary.txt") ;

    while (read_file2 >> x_from_dict >> word_from_dict)
    {
    	if (x_from_dict == x)
    	{
    		cout << word_from_dict <<endl ;
    		read_file2.close() ;
    		break ;
    	}
    }*/

    read_file >> comma ;
}
    z : t = clock() - t ;
    read_file.close() ;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    cout << "Total time for without cache implementation  :   " << time_taken << endl ;
    return 0 ;
}

else if (which_secret == "2")
{
  read_file.open("secret2.txt") ;

    int x ;
    string comma ;
    int looper = 0 ;
    int x_from_dict ;
    string word_from_dict ;

    clock_t t ;
    t = clock() ;

    while (read_file >> x)
    {
      looper++ ;

      if (looper > 10000)
        goto z2 ;

    word_from_dict = dict_search(x) ;
    cout << word_from_dict <<endl ;

  /*read_file2.open("dictionary.txt") ;

    while (read_file2 >> x_from_dict >> word_from_dict)
    {
      if (x_from_dict == x)
      {
        cout << word_from_dict <<endl ;
        read_file2.close() ;
        break ;
      }
    }*/

    read_file >> comma ;
}
    z2 : t = clock() - t ;
    read_file.close() ;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    cout << "Total time for without cache implementation  :   " << time_taken << endl ;
    return 0 ;
}

if (which_secret == "3")
{
  read_file.open("secret3.txt") ;

    int x ;
    string comma ;
    int looper = 0 ;
    int x_from_dict ;
    string word_from_dict ;

    clock_t t ;
    t = clock() ;

    while (read_file >> x)
    {
      looper++ ;

      if (looper > 10000)
        goto z3 ;

    word_from_dict = dict_search(x) ;
    cout << word_from_dict <<endl ;

  /*read_file2.open("dictionary.txt") ;

    while (read_file2 >> x_from_dict >> word_from_dict)
    {
      if (x_from_dict == x)
      {
        cout << word_from_dict <<endl ;
        read_file2.close() ;
        break ;
      }
    }*/

    read_file >> comma ;
}
    z3 : t = clock() - t ;
    read_file.close() ;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    cout << "Total time for without cache implementation  :   " << time_taken << endl ;
    return 0 ;
}

if (which_secret == "4")
{
  read_file.open("manualcode.txt") ;

    int x ;
    string comma ;
    int looper = 0 ;
    int x_from_dict ;
    string word_from_dict ;

    clock_t t ;
    t = clock() ;

    while (read_file >> x)
    {
      looper++ ;

      if (looper > 10000)
        goto z4 ;

    word_from_dict = dict_search(x) ;
    cout << word_from_dict <<endl ;

  /*read_file2.open("dictionary.txt") ;

    while (read_file2 >> x_from_dict >> word_from_dict)
    {
      if (x_from_dict == x)
      {
        cout << word_from_dict <<endl ;
        read_file2.close() ;
        break ;
      }
    }*/

    read_file >> comma ;
}
    z4 : t = clock() - t ;
    read_file.close() ;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    cout << "Total time for without cache implementation  :   " << time_taken << endl ;
    return 0 ;
}

else
{
	cout << "Invalid choice! Please enter again" <<endl  ;
	cout <<endl ;
	cin.clear() ;
	cin.ignore() ;
	goto again ;
}
}

else if (choice == "2")
{
	  cout << "Testing with cache" <<endl ;
    cout << "Press 1 for secret1" <<endl ;
    cout << "Press 2 for secret2" <<endl ;
    cout << "Press 3 for secret3" <<endl ;
    cout << "Press 4 to test secrets given in manual file" <<endl ;
    cout <<endl ;
    repeat : cout << "Enter your choice :  " ;
    cin >> which_secret ;
    cout <<endl ;
    newHashL* map = new newHashL();

    if (cin.fail())
    {
	    cout << "Invalid input!" <<endl ;
	    cout <<endl ;
	    cin.clear() ;
	    cin.ignore() ;
        goto repeat ;
    }

    if (which_secret == "1")
    {
        read_file.open("secret1.txt") ;

        int x ;
        int looper = 0 ;
        string comma ;
        int x_from_dict ;
        string word_from_dict ;
        clock_t t ;
        t = clock() ;
        while (read_file >> x)
        {
          looper++ ;
          if (looper > 10000)
            goto s ;
          block *store = map -> lookup(x) ;
          if (store != NULL)
          {
             cout << store -> value << "  found from cache" <<endl ;
             //goto jump ;
          }

	        else
          {
            word_from_dict = dict_search(x) ;
            cout << word_from_dict << "  found from dictionary" <<endl ;
            map -> insert(x , word_from_dict) ;
          } 
        /*read_file2.open("dictionary.txt") ;

          while (read_file2 >> x_from_dict >> word_from_dict)
          {
    	     if (x_from_dict == x)
    	     {
    		    cout << word_from_dict << "  found from dictionary" <<endl ;
    		    map -> insert(x , word_from_dict) ;
    		    read_file2.close() ;
    		    break ;
    	     }
          }*/

          read_file >> comma ;
        }
        s : t = clock() - t ;
        read_file.close() ;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        cout << "Total time for cache implementation  :   " << time_taken << endl ;
      }
    
    else if (which_secret == "2")
    {
        read_file.open("secret2.txt") ;

        int x ;
        int looper = 0 ;
        string comma ;
        int x_from_dict ;
        string word_from_dict ;
        clock_t t ;
        t = clock() ;
        while (read_file >> x)
        {
          looper++ ;
          if (looper > 10000)
            goto s2 ;
          block *store = map -> lookup(x) ;
          if (store != NULL)
          {
             cout << store -> value << "  found from cache" <<endl ;
             //goto jump2 ;
          }

          else
          {
            word_from_dict = dict_search(x) ;
            cout << word_from_dict << "  found from dictionary" <<endl ;
            map -> insert(x , word_from_dict) ;
          } 

        /*read_file2.open("dictionary.txt") ;

          while (read_file2 >> x_from_dict >> word_from_dict)
          {
           if (x_from_dict == x)
           {
            cout << word_from_dict << "  found from dictionary" <<endl ;
            map -> insert(x , word_from_dict) ;
            read_file2.close() ;
            break ;
           }
          }*/

          read_file >> comma ;
        }
        s2 : t = clock() - t ;
        read_file.close() ;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        cout << "Total time for cache implementation  :   " << time_taken << endl ;
      }

    else if (which_secret == "3")
    {
        read_file.open("secret3.txt") ;

        int x ;
        int looper = 0 ;
        string comma ;
        int x_from_dict ;
        string word_from_dict ;
        clock_t t ;
        t = clock() ;
        while (read_file >> x)
        {
          looper++ ;
          if (looper > 10000)
            goto s3 ;
          block *store = map -> lookup(x) ;
          if (store != NULL)
          {
             cout << store -> value << "  found from cache" <<endl ;
             //goto jump3 ;
          }

          else
          {
            word_from_dict = dict_search(x) ;
            cout << word_from_dict << "  found from dictionary" <<endl ;
            map -> insert(x , word_from_dict) ;
          } 

        /*read_file2.open("dictionary.txt") ;

          while (read_file2 >> x_from_dict >> word_from_dict)
          {
           if (x_from_dict == x)
           {
            cout << word_from_dict << "  found from dictionary" <<endl ;
            map -> insert(x , word_from_dict) ;
            read_file2.close() ;
            break ;
           }
          }*/

          read_file >> comma ;
        }
        s3 : t = clock() - t ;
        read_file.close() ;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        cout << "Total time for cache implementation  :   " << time_taken << endl ;
      }

    else if (which_secret == "4")
    {
        read_file.open("manualcode.txt") ;

        int x ;
        int looper = 0 ;
        string comma ;
        int x_from_dict ;
        string word_from_dict ;
        clock_t t ;
        t = clock() ;
        while (read_file >> x)
        {
          looper++ ;
          if (looper > 10000)
            goto s4 ;
          block *store = map -> lookup(x) ;
          if (store != NULL)
          {
             cout << store -> value << "  found from cache" <<endl ;
             //goto jump4 ;
          }

          else
          {
            word_from_dict = dict_search(x) ;
            cout << word_from_dict << "  found from dictionary" <<endl ;
            map -> insert(x , word_from_dict) ;
          } 

        /*read_file2.open("dictionary.txt") ;

          while (read_file2 >> x_from_dict >> word_from_dict)
          {
           if (x_from_dict == x)
           {
            cout << word_from_dict << "  found from dictionary" <<endl ;
            map -> insert(x , word_from_dict) ;
            read_file2.close() ;
            break ;
           }
          }*/

          read_file >> comma ;
        }
        s4 : t = clock() - t ;
        read_file.close() ;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        cout << "Total time for cache implementation  :   " << time_taken << endl ;
      }
    
    else
    {
	    cout << "Invalid choice! Please enter again" <<endl  ;
	    cout <<endl ;
	    cin.clear() ;
	    cin.ignore() ;
	    goto repeat ;
   }
}

else
{
	cin.clear() ;
	cin.ignore() ;
	cout << "Invalid choice! Please enter again  :   "   ;
	goto loop2 ;
}

return 0 ;
}
