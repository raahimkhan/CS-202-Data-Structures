#ifndef __BST_CPP
#define __BST_CPP
#include "bst.h"
#include <iostream>
#include <queue>
#include <cmath>

// HELPER FUNCTIONS HERE...

template <class T>
void destroy_bst(node<T> *temp) /**Just a helper function for the destructor part**/
{
	if (temp != NULL)
	{
		destroy_bst(temp -> left) ;
		destroy_bst(temp -> right) ;
		delete temp ;
	}
}

template <class T>
BST<T>::BST()
{
	root = NULL ;
}


template <class T>
BST<T>:: ~BST()
{
	destroy_bst(root) ;
}

template <class T>
int BST<T> :: height (node<T>* p)
{
	if (p == NULL)  /**If it's a leaf node or only root node**/
		return 0 ;

	else
	{
		/**FIrst get heights of both left and right subtrees recursively**/
		int height_left_subtree  = height(p -> left) ;
        int height_right_subtree = height(p -> right) ;

        /**Then compare those both heights**/

        /**1 is added for the existing node from where we calculate height**/

        if (height_left_subtree > height_right_subtree)
        	return 1 + height_left_subtree ;

        else
        	return 1 + height_right_subtree ;
    }
}

//template <class T>
//int BST<T> :: balanceFactor(node<T>* p) /**you can use this to find balance factor.**/
//{
//	node <T> *temp = p ;

//	if (temp == NULL)
//		return 0 ;

//	int height_left_subtree  = height(temp -> left) ;
//    int height_right_subtree = height(temp -> right) ;


    //int balance_fac = new_left - new_right ;
//    int balance_fac = height_left_subtree - height_right_subtree ;

//    return balance_fac ;
//}

//template <class T>
//void BST<T> :: fixHeight(node<T>* p) /**use this function to fix height of a node after insertion or deletion.**/
//{
//	p -> height = height(p) ;
//}

// ROTATING HELPERS 
//template <class T>
//node<T>* BST<T> :: rotateleft(node<T>* p) /**RR case**/
//{
//	node<T> *newroot = p -> right ; //newroot points to the root that will become the new root node after rotation
//    p -> right = newroot -> left ;

//    newroot -> left = p ; // sets old root node as the left child of the new root node

//    p -> height = max(height(p->left), height(p->right)) + 1 ;
//    newroot -> height = max(height(newroot->right), p->height) + 1 ;

//    p = newroot ;

//    fixHeight(p);
//    fixHeight(newroot);
//}

//template <class T>
//node<T>* BST<T> :: rotateright(node<T>* p)  /**LL case**/
//{
//	node<T> *newroot = p -> left ; //newroot points to the root that will become the new root node after rotation
//    p -> left = newroot -> right ; // the right child of the to be new root node is now the left child of the old root node

//    newroot -> right = p ; // sets old root node as the right child of the new root node

//    p -> height = 1 + max(height(p->left), height(p->right)) ;
//    newroot -> height = 1 + max(height(newroot->left), p->height) ;

//    p = newroot ;

//    fixHeight(p);
//    fixHeight(newroot);
//}

/*template <class T>
node<T>* BST<T> :: balance(node<T>* p) /** Balancing code goes here. You might need to find balance factor and call appropriate rotations.**/
//{
    //fixHeight(p) ;

    // ROTATION CASES FOR INSERTION

    //int balfactor = balanceFactor(p);
    //int balfactor1 = height(p->right) - height(p->left);

    // LEFT LEFT CASE
    //if (balfactor > 1 && height(p->left->left) >= height(p->left->right))
    //{
      //  return rotateright(p);
    //}

    // RIGHT RIGHT CASE
    //else if (balfactor < -1 && height( p->right->right ) >= height( p->right->left ))
    //{
     //   return rotateleft(p);
   // }

    //LEFT RIGHT CASE
    //else if (balfactor > 1 && height(p->left->left) < height(p->left->right))
    //{
        //p->left = rotateleft(p->left);
      //  return rotateright(p);
    //}

    // RIGHT LEFT CASE
    //else if (balfactor < -1 && height(p->right->right) < height(p->right->left))
    //{
  //      p->right = rotateright(p->right);
//        return rotateleft(p);
//    }

//    p->height = max(height(p->left), height(p->right)) + 1;


//    fixHeight(p) ;
//    return p;
//}

// CLASS FUNCTIONS HERE

template <class T>
void BST<T> :: insert(string value,T k)
{
    root = insertHelper(value , k , root) ;
}

// insertion helper
template <class T>
node<T>* BST<T> :: insertHelper(string value,T k, node<T> *p) 
{ 
    if (p == NULL)
    {
        node <T> *temp = new node <T> (k , value) ;
        return temp ;
    }

    if (k < p -> key)
    {
        p -> left = insertHelper(value, k , p -> left) ;
    }

    else if (k > p -> key)
    {
        p -> right = insertHelper(value , k , p -> right) ;
    }

    //return balance(p) ;
    return p ;
}

template<class T>
node<T>* BST<T> :: search(T key)
{
    node<T> *temp = root ;
	
	while (temp != NULL)  /**Iterative search**/
	{
		if (key > temp -> key)
		{
			temp = temp -> right ;  /**Search in right subtree**/
		}
		else if (key < temp -> key)
		{
			temp = temp -> left ;  /**Search in left subtree**/
		}
		else
		{
			return temp ;  /**If key found**/
		}
	}
    return NULL ; /**If key not found**/
}

// DELETE HELPER FUNCTIONS
template<class T>
node<T>* BST<T> :: findmin(node<T> *p) // This function finds the min node of the tree.
{
	node <T> *temp = p ;
	while (temp -> left != NULL)
	{
		temp = temp -> left ;
	}
	return temp ;
}

template<class T>
node<T>* BST<T>::removemin(node<T>* p)  // This function recursively finds the min node and deletes it.
{
	node<T> *temp = findmin(p) ;
	node<T> *temp2 = root ;
	while (temp2 -> left != temp)
	{
		temp2 = temp2 -> left ;
	}
	delete temp ;
	temp2 -> left = NULL ;
	
    //return balance(p);
    return p ;
}

template<class T>
void BST<T>::delete_node(T k)
{
    root = remove(root, k) ;
}

template<class T>
node<T>*  BST<T>::remove(node<T>* p, T k) // k key deletion from p tree. This function uses findmin and deletemin to delete arbitrary node in the tree.
{
	if (p == NULL)  /**If root NULL**/
		return p ;

	if (k < p -> key) /**If k smaller than root key then go to left subtree**/
		p -> left = remove(p -> left , k) ;

	else if (k > p -> key)  /**If k greater than root key then go to left subtree**/
		p -> right = remove(p -> right , k) ;

	else /**If key found!**/
	{   /**If and Else cases for node with one child and leaf node**/
		if (p -> left == NULL)
		{
			node <T> *temp = p -> right ;
			delete p ;
			return temp ;
		}

		else if (p -> right == NULL)
		{
			node <T> *temp = p -> left ;
			delete p ;
			return temp ;
		}

		/**Case if node to be deleted has 2 children**/

		node <T> *temp2 = findmin(p -> right) ;  /**Find smallest key in the right subtree of node to be deleted**/

		p -> key = temp2 -> key ;  /**Copy inorder successor's key to this node**/

		p -> right = remove(p -> right , temp2 -> key) ;  /**Delete inorder successor**/
	}
    return p;

    // ROTATION CASES FOR DELETION
   // int balfactor = balanceFactor(p);
    //int balfactor1_left = balanceFactor(p->left);
    //int balfactor1_right = balanceFactor(p->right);

    //LEFT LEFT CASE
    //if (balfactor > 1 && balfactor1_left >= 0)
    //{
    //    return rotateright(p);
    //}

    //RIGHT RIGHT CASE
    //else if (balfactor < -1 && balfactor1_right <= 0)
    //{
      //  return rotateleft(p);
    //}

    //LEFT RIGHT CASE
    //else if (balfactor > 1 && balfactor1_left < 0)
    //{
      //  p->left = rotateleft(p->left);
        //return rotateright(p);
    //}

    //RIGHT LEFT CASE
    //else if (balfactor < 1 && balfactor1_right > 0)
    //{
      //  p->right = rotateright(p->right);
        //return rotateleft(p);
    //}

    
    //return balance(p);
}	

template<class T>
node<T>* BST<T>::getRoot()
{
    return root ;
}

#endif
