#ifndef GRAPH__CPP
#define GRAPH__CPP
#include "Graph.h"
#include <fstream>
#include <list>

Graph::Graph(char* file, bool isUnitLength) // 20 nodes
{
    ifstream in_file ;
	in_file.open(file) ;

	if (in_file.fail())
	{
		cout << "File does not exist / Cannot read file" <<endl ;
		exit(1) ;
	}
    string first_line ; // Will just ignore it as it is just the heading i.e PEOPLE in friends.txt
    in_file >> first_line ;
    string temp ;
    in_file >> temp ; // names of people from friends.txt
    while (temp != "CONNECTIONS")
	{
		node *temp_node = new node ; // create vertex/node for single person
		temp_node -> name = temp ;
		temp_node -> visit = 0 ;

		people.push_back(temp_node) ; // push this single node into a vector of node named people

		in_file >> temp ; // read name of next person until temp == "CONNECTIONS"
	}

    // After above while loop ends last value of temp would be "CONNECTIONS" so we just ignore that and read further

	while (!in_file.eof()) // now read connections and index of friendship from friends.txt
	{
		string start ; // origin
		string finish ;  // dest
		float index ; // weight / index of friendship

		in_file >> start ;
		in_file >> finish ;
		in_file >> index ;

		node *get_origin ;
		for (int i = 0; i < people.size(); i++)
	    {
	        if (people[i] -> name == start)
		    {
		        get_origin = people[i] ;
		        goto jump ;
			}
	    }

		jump : node *node_origin = get_origin ;

		node *get_dest ;
		for (int i = 0; i < people.size(); i++)
	    {
	        if (people[i] -> name == finish)
		    {
		        get_dest = people[i] ;
		        goto jump2 ;
			}
	    }

		jump2 : node *node_dest = get_dest ;

		edge edge_origin ; // creates edge from starting to end point along with index of friendship
        edge_origin.Origin = node_origin ;
        edge_origin.Dest = node_dest ;
        if(isUnitLength == false)
            edge_origin.weight = index ;

        else
            edge_origin.weight = 1 ;

		node_origin -> edges.push_back(edge_origin) ;

		arcs.push_back(edge_origin) ;

		edge edge_dst ; // creates edge from end to starting point along with index of friendship since undirected
		edge_dst.Origin = node_dest ;
        edge_dst.Dest = node_origin ;
        edge_dst.weight = index ;

        if (isUnitLength == false)
            edge_dst.weight = index ;

        else
            edge_dst.weight = 1 ;

		node_dest -> edges.push_back(edge_dst) ;
	}
}

void Graph::display()
{
    int counter = 0 ;
    for (int i = 0 ; i < arcs.size() ; i++)
    {
        edge temp = arcs[i] ;
        cout << temp.Origin->name << " -> " << temp.Dest->name << " " << "Weight : " << temp.weight <<endl ;
        counter++ ;
    }
    cout <<endl ;
    cout << "Total connections :  " << counter <<endl ;

	/*
	node* temp as original parameter
	if(temp->visit)
		return ;

	cout << "Person: " << temp->name;
	temp->visit = 1;
	for(int i=0; i< temp->edges.size(); i++)
	{
		if(!temp->edges[i].Origin->visit || !temp->edges[i].Dest->visit)
		cout << " -> " << temp->edges[i].weight << " -> " <<" " <<temp->edges[i].Dest->name<< endl;
		display(temp->edges[i].Origin);
		display(temp->edges[i].Dest);
	}*/
}

bool Graph::Reachable(string start, string dest)
{
    // First find whether start word is present in our graph or not
    bool found_start = false ;
    node *start_node ;
    for (int i = 0 ; i < people.size() ; i++)
    {
        if (people[i] -> name == start)
        {
            start_node = people[i] ;
            found_start = true ;
            break ;
        }

        else
            continue ;
    }

    if (found_start == false)
    {
        return false ;
    }

    bool found_end = false ;
    node *end_node ;
    for (int i = 0 ; i < people.size() ; i++)
    {
        if (people[i] -> name == dest)
        {
            end_node = people[i] ;
            found_end = true ;
            break ;
        }

        else
            continue ;
    }

    if (found_end == false)
    {
        return false ;
    }

    if (start == dest)  // Self loop
        return true ;

    if (start_node -> visit == 1)  // if already visited (returned back to initial position)
        return false ;

    start_node -> visit = 1 ;
    int condition = 0 ;

    for (int i = 0 ; i < start_node -> edges.size() ; i++)
    {
        node *temp = start_node -> edges[i].Dest ;
        string new_start = temp -> name ;
        if (Reachable(new_start , dest))
        {
            condition = 1 ;
            break ;
        }
    }

    if (condition == 1)
        return true ;

    else
        return false ;
}

vector<node*> Graph::Prims()
{

}

int min_extractor(vector<set<node*> >cloud, node *temp)
{
	for (int i = 0 ; i < cloud.size() ; i++)
	{
		if (cloud[i].find(temp) != cloud[i].end())
		{
			return i ;
		}
	}

	return -1 ;
}

vector<node*> Graph::Kruskal()
{
    for (int i = 0 ; i < people.size() ; i++)
        people[i] -> visit = 0 ;

    priority_queue <edge, vector<edge>, greater<edge> > p_queue ;  // Min Heap

    for (int i = 0 ; i < arcs.size() ; i++)
        p_queue.push(arcs[i]) ;

    vector<set<node*> >cloud ;

    for (int i = 0 ; i < people.size() ; i++)
	{
		set<node*> temp ;
		temp.insert(people[i]) ;
		cloud.push_back(temp) ;
	}

	vector<node*> result ;

	vector <edge> spanning_edges ;

    while (p_queue.empty() == false)
    {
        edge min_edge = p_queue.top() ;  // extract edge with minimum distance
        p_queue.pop() ;

        // Find index of Origin and Dest of min_edge
        int origin_index = min_extractor(cloud, min_edge.Origin );
		int dest_index = min_extractor(cloud, min_edge.Dest) ;

		if (origin_index != dest_index)
		{
			spanning_edges.push_back(min_edge) ;

			cloud[origin_index].insert(cloud[dest_index].begin(), cloud[dest_index].end()) ;
			cloud.erase(cloud.begin() + dest_index) ;
		}
    }

    float total_cost = 0 ;

    for (int i = 0 ; i < spanning_edges.size() ; i++)
    {
        cout << spanning_edges[i].Origin -> name << " " << spanning_edges[i].Dest -> name << " " << spanning_edges[i].weight << endl ;
        total_cost = total_cost + spanning_edges[i].weight ;
    }

    cout <<endl ;
    cout << "Now converting these spanning edges to a tree" <<endl ;
    cout <<endl ;

    for (int i = 0 ; i < spanning_edges.size() ; i++)
    {
        if(spanning_edges[i].Origin -> visit == 1)
            continue ;

        node *tree = spanning_edges[i].Origin ;
        cout << tree -> name << " : " ;
        for (int j = 0 ; j < spanning_edges.size() ; j++)
        {
            if (spanning_edges[j].Origin -> name == tree -> name)
            {
                cout << spanning_edges[j].Dest -> name << " " ;
            }

            else
                continue ;
        }

        spanning_edges[i].Origin -> visit = 1 ;

        cout <<endl ;
    }

    cout <<endl ;

    cout << "Total weight of tree =  " << total_cost <<endl ;

	return result ;
}

int min_index_finder(vector <node*> temporary)
{
    int lowest = 0 ;
    float lowest_distance = temporary[0] -> distance ;

    for(int i = 1 ; i < temporary.size() ; i++)
    {
        if(lowest_distance > temporary[i] -> distance)
        {
            lowest_distance = temporary[i] -> distance ;
            lowest = i ;
        }
    }

    return lowest ;
}

float min_distance_finder(vector <node*> temporary)
{
    int lowest = 0 ;
    float lowest_distance = temporary[0] -> distance ;

    for(int i = 1 ; i < temporary.size() ; i++)
    {
        if(lowest_distance > temporary[i] -> distance)
        {
            lowest_distance = temporary[i] -> distance ;
            lowest = i ;
        }
    }

    return lowest_distance ;
}

vector<string> Graph::Dijkstra(string start, string dest , float &d)
{
    node *start_node , *end_node ;
    bool start_found = false ;
    bool end_found = false ;

    for (int i = 0 ; i < people.size() ; i++)
    {
        if (people[i] -> name == start)
        {
            start_node = people[i] ;
            start_found = true ;
            break ;
        }
    }

    for (int i = 0 ; i < people.size() ; i++)
    {
        if (people[i] -> name == dest)
        {
            end_node = people[i] ;
            end_found = true ;
            break ;
        }
    }

    if(start_found == false)
    {
        cout << start << "  not present in graph" <<endl ;
        exit(1) ;
    }

    if(end_found == false)
    {
        cout << dest << "  not present in graph" <<endl ;
        exit(1) ;
    }

    vector <string> shortest_path_names ;
    vector <node*> temporary ;

    for (int i = 0 ; i < people.size() ; i++)
        temporary.push_back(people[i]) ;

    for (int i = 0 ; i < people.size() ; i++)
    {
        people[i] -> distance = 90000 ;
        people[i] -> visit = 0 ;
    }

    start_node -> distance = 0 ;

    while (temporary.size() > 0)
    {
        int min_index = min_index_finder(temporary) ;
        float min_distance = min_distance_finder(temporary) ;

        node *min_index_node = temporary[min_index] ;
        temporary.erase(temporary.begin() + min_index) ;  // delete the node that has been visited

        min_index_node -> visit = 1 ;

        for(int i = 0 ; i < min_index_node -> edges.size() ; i++)
        {
            if(min_index_node -> edges[i].Dest -> visit == 0)
            {
                float w = min_index_node -> edges[i].weight ;
                float update_distance = min_index_node -> distance + w ;

                if(min_index_node -> edges[i].Dest -> distance > update_distance)
                {
                    min_index_node -> edges[i].Dest -> distance = update_distance ;
                    min_index_node -> edges[i].Dest -> prev = min_index_node ;
                }
            }
        }
    }

    node *crap = end_node ;

    bool forever = true ;

    while(forever)
    {
        if(crap != start_node)
        {
            shortest_path_names.push_back(crap -> name) ;
            crap = crap -> prev ;
        }

        if (crap == start_node)
            break ;
    }

    shortest_path_names.push_back(start_node -> name) ;
    d = end_node -> distance ;

    reverse(shortest_path_names.begin() , shortest_path_names.end()) ;

    return shortest_path_names ;
}

bool operator < (edge a, edge b)
{
	if (a.weight < b.weight)
	{
		return true ;
	}

	return false ;
}

bool operator == (edge a, edge b)
{
	if (a.weight == b.weight)
	{
		return true ;
	}

	return false ;
}

bool operator > (edge a, edge b)
{
	if (a.weight > b.weight)
	{
		return true ;
	}

	return false ;
}

int main()
{
    bool isOn = false ;
    cout <<endl ;
	cout << "Initializing Graph..." <<endl ;
	cout <<endl ;
	Graph graph("friends.txt" , isOn) ;
	cout << "Done initializing!" <<endl ;
	cout <<endl ;
    cout << "#######################################" <<endl ;
	cout <<endl ;

	/**Task 6**/

	/*1*/
    for (int i = 0 ; i < graph.people.size() ; i++)
        graph.people[i] -> visit = 0 ;

    bool truth = graph.Reachable("Mannan" , "Ali") ; // Mannan - Ali , Mannan - Trump and Ali - Trump
	if (truth)
        cout << "Connection exists between Mannan and Ali" <<endl ;
    else
        cout << "No connection exist between Mannan and Ali" <<endl ;
    cout <<endl ;

    for (int i = 0 ; i < graph.people.size() ; i++)
        graph.people[i] -> visit = 0 ;

    truth = graph.Reachable("Mannan" , "Trump") ; // Mannan - Ali , Mannan - Trump and Ali - Trump
	if (truth)
        cout << "Connection exists between Mannan and Trump" <<endl ;
    else
        cout << "No connection exist between Mannan and Trump" <<endl ;
    cout <<endl ;

    for (int i = 0 ; i < graph.people.size() ; i++)
        graph.people[i] -> visit = 0 ;

    truth = graph.Reachable("Ali" , "Trump") ; // Mannan - Ali , Mannan - Trump and Ali - Trump
	if (truth)
        cout << "Connection exists between Ali and Trump" <<endl ;
    else
        cout << "No connection exist between Ali and Trump" <<endl ;

    cout <<endl ;
    cout << "#######################################" <<endl ;
    cout <<endl ;

    /**Hence connection exists between Mannan - Ali , Mannan - Trump and Ali - Trump and there exists a path between them. From this it can be
    deduced that the graph is undirected. And also the graph is connected that is every node is reachable from every other node.**/

    /*2*/

    cout << "Initializing graph with unit length weights" <<endl ;
	cout <<endl ;
	isOn = true ;
	Graph graph2("friends.txt" , isOn) ;
	cout << "Done initializing!" <<endl ;
	cout <<endl ;

    float min_cost = 0 ;
    vector <string> shortest = graph2.Dijkstra("Trump" , "Ali" , min_cost) ;
    for (int i = 0 ; i < shortest.size() ; i++)
    {
        if (i == shortest.size() - 1)
            cout << shortest[i] ;
        else
            cout << shortest[i] << " -- " ;
    }

    cout <<endl ;
    cout << "Path Distance :  " << min_cost <<endl ;
    cout <<endl ;
    shortest.clear() ;

    /*3*/

    float min_cost2 = 0 ;
    shortest = graph2.Dijkstra("Mannan" , "Trump" , min_cost2) ;
    for (int i = 0 ; i < shortest.size() ; i++)
    {
        if (i == shortest.size() - 1)
            cout << shortest[i] ;
        else
            cout << shortest[i] << " -- " ;
    }

    cout <<endl ;
    cout << "Path Distance :  " << min_cost2 <<endl ;
    cout <<endl ;
    cout << "#######################################" <<endl ;
    cout <<endl ;

    /**Hence Ali is 2 hops away from Trump and Mannan is 3 hops away from Trump**/

    /*4*/

    shortest.clear() ;
    float min_cost3 = 0 ;
    shortest = graph.Dijkstra("Trump" , "Ali" , min_cost3) ;
    for (int i = 0 ; i < shortest.size() ; i++)
    {
        if (i == shortest.size() - 1)
            cout << shortest[i] ;
        else
            cout << shortest[i] << " -- " ;
    }

    cout <<endl ;
    cout << "Path distance in terms of index of friendship :  " << min_cost3 <<endl ;
    cout <<endl ;

    shortest.clear() ;

    float min_cost4 = 0 ;
    shortest = graph.Dijkstra("Mannan" , "Trump" , min_cost4) ;
    for (int i = 0 ; i < shortest.size() ; i++)
    {
        if (i == shortest.size() - 1)
            cout << shortest[i] ;
        else
            cout << shortest[i] << " -- " ;
    }

    cout <<endl ;
    cout << "Path distance in terms of index of friendship:  " << min_cost4 <<endl ;
    cout <<endl ;
    cout << "#######################################" <<endl ;
    cout <<endl ;

    /**Hence Trump and Mannan has smaller value of path in terms of index of friendship that is 8
    whereas Trump and Ali have a path distance of 11 in terms of index of friendship**/

    /*5*/

    cout << "MST on weighted graph" <<endl ;
    cout <<endl ;
    vector <node*> span1 = graph.Kruskal() ;
    cout <<endl ;
    cout << "@@@@@@@@@@@@@@@@@@@@@@" <<endl ;
    cout <<endl ;
    cout << "MST on unit weight graph" <<endl ;
    cout <<endl ;
    vector <node*> span2 = graph2.Kruskal() ;
    cout <<endl ;
    cout << "#######################################" <<endl ;
    cout <<endl ;

    /**
       * There may be several minimum spanning trees of the same weight. If all the edge weights of a given graph are the same,
       then every spanning tree of that graph is minimum. (i.e. isUnitLength is on)

       * Implications drawn :
       1) Structure of MST changed when unit length weights were used.
       2) More than one MST possible for unit length weights graphs since all weights are equal and hence any edge can be picked
          as long as no cycle / loop is produced

       * Benefit a social media website can have from the MSTs I have produced :
       1) Since all users in a social media website are connected to each other i.e. they can open each other's profiles , send message
          hence social media can use my MSTs in order to check which users are close to each other or interact with each other more often
          and that path (users) could be connected in such a way that it forms a MST and less time is taken for common operations.

       * Applications of MST in terms of social connection graphs :
       1) Load on social network could be reduced by making use of MST. Every user (if friend with other) could be connected
       to each other in such a way that not only load would be reduced but complexity of different operations would also
       be enhanced.

       2) MST prevents loops / cycle. Hence data would safely be transferred to a user without being duplicated over the shortest possible time
       or least expensive path.
    **/
}

#endif
