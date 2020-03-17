#ifndef GRAPH__H
#define GRAPH__H
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <set>
#include <algorithm>
#include <queue>
// You may include more libraries.

using namespace std ;
class node ;

class edge
{
	// You may add more variables and functions in this class
	public:
		node* Origin;
		node* Dest;
		float weight;

		friend bool operator < (edge a, edge b);
		friend bool operator == (edge a, edge b);
		friend bool operator > (edge a, edge b);
};
class node
{
	// You may add more variables and functions in this class
	public:
		int visit ; // flag to check if the node has been already visited
		float distance ;
		node *prev ;
		string name ;
		vector<edge> edges ; // edges connected to node
} ;


class Graph
{
	public:
		vector<node*> Mst; // minimum spanning tree
		vector<node*> people;
		vector<edge> arcs;
		Graph(char* filename, bool isUnitLength);
		void display() ; // displays the graph

		bool Reachable(string start, string dest);
		vector<node*> Prims();
		vector<node*> Kruskal(); //runs kruskal algorithm and returns the Minimum spanning tree
		vector<string> Dijkstra(string start, string dest, float &d);
};

#endif

