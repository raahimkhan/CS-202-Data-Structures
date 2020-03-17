#ifndef __TREE_CPP
#define __TREE_CPP
#include "tree.h"
#include <sstream>

// try to make get_node() and get_file() after tree initialization

//Friendly function to convert from int to string
string int_to_string(int number)
{
	ostringstream strng ;
	strng << number ;
	string converted = strng.str() ;
	return converted ;
}

//Friendly function to convert from string to int
int string_to_int(string a)
{
	stringstream to_convert(a) ;
	int converted = 0 ;
	to_convert >> converted ;
	return converted ;
}

Tree::Tree(string data)
{
	TreeItem* new_node = new TreeItem() ;
	new_node -> id = 1 ;
	new_node -> latest_data = data ;
	root = new_node ;
	VCS_node temp(data , 0) ;
	new_node -> container.push_back(temp) ;
}

Tree::~Tree()
{
	if (root != NULL)
	{
		int total = (root -> child).size() ;

		for (int x = 0 ; x < total ; x++)
		{
			int total2 = ((root->child[x])->child).size() ;

			for (int y = 0 ; y < total2 ; y++)
				delete (root -> child[x] -> child[y]) ;
		}

		int total3 = (root -> child).size() ;

		for (int x = 0 ; x < total3 ; x++)
			delete (root -> child[x]) ;

		delete root ;
	}

	else  //if only root node present
		delete root ;
}

void Tree::branch(int id)
{
	string p_id = int_to_string(id) ; //Parent id
	TreeItem* p_node = get_node(id) ; //Parent node

	if (p_node != NULL)
	{
		if ((p_node -> child).size() < 9)
		{
			//increment is kind of a pointer which goes 8 bytes ahead and points to the next vector element

			string increment = int_to_string((p_node -> child).size() + 1) ; // (p_node -> child).size() are number of children
			int id_of_child = string_to_int(p_id + increment) ;

			TreeItem *BRANCH = new TreeItem ; //New child
			BRANCH -> id = id_of_child ;
			BRANCH -> latest_data = p_node -> latest_data ; 

			//Now push new child
			VCS_node temp(p_node -> latest_data , 0) ;
			(BRANCH -> container).push_back(temp) ;
			(p_node -> child).push_back(BRANCH) ;
		}
	}
}

void Tree::merge(int src_id,int dst_id)
{
	TreeItem *s_n = get_node(src_id) ; //source node
	TreeItem *d_n = get_node(dst_id) ; //destination node

	if(s_n != NULL && d_n != NULL)
	{
		d_n -> latest_data = d_n -> latest_data + s_n -> latest_data ;
		int decrement = (d_n -> container).size() - 1 ;
		(d_n -> container[decrement]).data = d_n -> latest_data ;
		merge_state merger ; //merge state
		merger.src_id = src_id ; 
		merger.dst_id = dst_id ;
		history.push_back(merger) ;
	}
}

void Tree::commit(int src_id,string new_data)
{ 
	TreeItem *old = get_node(src_id) ; //current
	if(old != NULL)
	{
		string newdata = old -> latest_data + new_data ;  //new data
		string newLATESTDATA = newdata ; 
		VCS_node temp(newLATESTDATA , (old -> container).size()) ;
		(old -> container).push_back(temp) ;
		old -> latest_data = newLATESTDATA ;
	}
}

string Tree::get_file(int id, int t_stamp)
{
	TreeItem *fileget = get_node(id) ;
	
	if (fileget != NULL)
	{
		for(int x = 0 ; x < (fileget -> container).size() ; x++) //(temp->container).size() is container size
		{
			int compare = (fileget -> container[x]).time_stamp ;

			if(compare == t_stamp)
				return (fileget -> container[x]).data;
		}

		return "" ;
	}

	else //if fileget is NULL
	{
		return "" ;
	}
} 

TreeItem* Tree::get_node(int id)
{
	if(id == 1)  //since root has an id of 1
		return root ;

	if(id >= 11 && id <= 19)
	{
		if(root -> child.empty()) //if root has no child
			return NULL;

		else
		{
			vector<TreeItem*>::iterator iter ;
			for(iter = root -> child.begin() ; iter != root -> child.end() ; iter++)
			{
				if( (*iter) -> id == id)
					return (*iter) ;
			}
		}

		return NULL;
	}

	else if(id >= 111 && id <= 199)
	{
		if(root -> child.empty()) //if root has no child
		{
			return NULL;
		}

		else
		{
			int scan_id = id / 10 ; //sc_id

			vector<TreeItem*>::iterator iter ;

			for(iter = root -> child.begin() ; iter != root -> child.end() ; iter++)
			{
				if( (*iter) -> id == scan_id)
				{
					TreeItem* scan = (*iter) ; //sc

					if( (scan -> child).empty() ) // if no child for branch
					{
						return NULL;
					}

					for(iter = (scan -> child).begin() ; iter != (scan -> child).end() ; iter++)
					{
						if( (*iter) -> id == id)
							return (*iter) ;
					}
				}
			}
		}

		return NULL ;
	}

	return NULL ;
} 

vector<merge_state> Tree::merge_history()
{
	return history ;
}

void Tree::level_traversal() 
{ 
	if(root == NULL)
		return ;
	
	else
		cout << "Node id: " << root -> id <<endl ;
		cout << "Latest data: " << root -> latest_data <<endl ;

	if( !(root -> child).empty() )
	{
		int child_size = (root -> child).size() ;
		for(int i = 0 ; i < child_size ; i++)
		{
			cout << "Node id: " << (root -> child[i]) -> id <<endl ;
			cout << "Latest data: " << (root -> child[i]) -> latest_data <<endl ;
		}
	}

	else
		return ;
    
    int child_size2 = (root -> child).size() ;

	for(int i = 0 ; i < child_size2 ; i++)
	{
		int child_size3 = ( (root->child[i]) -> child).size() ;
		for(int j = 0 ; j < child_size3 ; j++)
		{
			cout << "Node id: " << ((root -> child[i]) -> child[j]) -> id <<endl ;
			cout << "Latest data: " << ((root -> child[i]) -> child[j]) -> latest_data <<endl ;
		}
	}
} 

#endif