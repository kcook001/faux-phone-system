//maze.cpp
//Header implementation file for the maze-related classes used in Assignment #3.
//Paired with the header declaration file 'maze.h'
//This file contains the implemented functions for the two classes
//defined in the 'maze.h' header file.  This includes the maze node class (representing
//a single point in a maze) and the maze linked list / managing class.
//CS 202  Assignment #3
//Keith Cook 2-17-2016

#include "maze.h"
#include <iostream>   //Included for I/O
#include <fstream>    //Included for reading from an external file.
using namespace std;

//Maze Node Class Functions

//Default constructor
maze_node::maze_node()
{
	data = 0;
	
	north = NULL;
	south = NULL;
	east = NULL;
	west = NULL;
	
	next = NULL;
	
	return;
}

//Argument constructor
maze_node::maze_node(int d)
{
	data = d;
	
	north = NULL;
	south = NULL;
	east = NULL;
	west = NULL;
	
	next = NULL;
	
	return;
}

//Destructor
maze_node::~maze_node()
{
	data = 0;
	
	north = NULL;
	south = NULL;
	east = NULL;
	west = NULL;
	
	next = NULL;
	
	return;
}

//Setter for directional pointers
void maze_node::set_directions(maze_node * n, maze_node * s, maze_node * e, maze_node * w)
{
	north = n;
	south = s;
	east = e;
	west = w;
	
	return;
}

//Getter for north pointer
maze_node * maze_node::go_north() const
{
	return north;
}

//Getter for south pointer
maze_node * maze_node::go_south() const
{
	return south;
}

//Getter for east pointer
maze_node * maze_node::go_east() const
{
	return east;
}

//Getter for west pointer
maze_node * maze_node::go_west() const
{
	return west;
}

//Getter for next pointer
maze_node * maze_node::get_next()
{
	return next;
}

//Setter for next pointer
void maze_node::set_next(maze_node * n)
{
	next = n;
	return;
}

//Getter for int data member
int maze_node::get_data()
{
	return data;
}

//Maze Class Functions

//Default constructor
maze::maze()
{
	head = NULL;
	current = NULL;
	start = NULL;
	end = NULL;
	
	return;
}

//Destructor
maze::~maze()
{
	if(head) *this-=0;  //If the maze contains nodes, remove all.
	head = NULL;
	current = NULL;
	start = NULL;
	end = NULL;
	
	return;
}

//Load maze data from an external file.
int maze::load(const char * filename)
{
	//Attempt to open the specified file.
     ifstream file_in;
     file_in.open(filename);
     if(!file_in)
     {
         return 0;   //Abort if file not found.
     }
	
	//Temp variables
	int nodes = 0; //Number of nodes in the maze.
	int n = 0;     //North connection.
	int s = 0;     //South connection.
	int e = 0;     //East connection.
	int w = 0;     //West connection.
	int st = 0;    //Start location.
	int en = 0;    //End location.
	
	maze_node * ptr = NULL;
	
	//Read first line and build initial (linear) list
     file_in >> nodes;
     file_in.ignore(100, '\n');
     
     build(nodes);
     
    //Read each line and set the direction pointers for each node.
    for(int i = 0; i < nodes; ++i)
    {
          
          file_in >> n;
          file_in.ignore(100, ',');
          
          file_in >> s;
          file_in.ignore(100, ',');
          
          file_in >> e;
          file_in.ignore(100, ',');
          
          file_in >> w;
          file_in.ignore(100, '\n');
          
          set_directions(i+1, n, s, e, w);
	}
	
	//Read and set maze pointers
	file_in >> st;
    file_in.ignore(100, ',');
          
    file_in >> en;
    file_in.ignore(100, '\n');
    
    ptr = head;
    while(ptr)
    {
    	if(ptr->get_data() == st) start = ptr;
    	if(ptr->get_data() == en) end = ptr;
    	ptr = ptr->get_next();
	}
	
	current = start;
	
	//Close file
    file_in.close();
    file_in.clear();
    
    //Returns size of the maze (0 indicates the maze was not built / is empty).
    return nodes;
}

//Builds the inital linked list framework for the maze (a LLL with sequential int data members)
bool maze::build(int num_nodes)
{
	if(num_nodes < 1) return false;
	
	for(int i = 0; i < num_nodes; ++i)
	{
		*this += (i+1);
	}
	
	return true;
}

//Adds a new node to the maze linked list with the supplied data value.
void maze::add(int data)
{
	maze_node * ptr1 = NULL;
	maze_node * ptr2 = NULL;
	
	if(!head)
	{
		head = new maze_node(data);
		head->set_next(NULL);
	} else {
		ptr1 = head;
         
         while(ptr1)
         {
              ptr2 = ptr1;
              ptr1 = ptr1->get_next();
         }
         ptr1 = new maze_node(data);
         ptr2->set_next(ptr1);
	}
	
	return;
}

//Sets the directional pointers for a single node in the maze.
void maze::set_directions(int d, int n, int s, int e, int w)
{
	maze_node * ptr1 = head;
	maze_node * ptr2 = head;
	
	maze_node * nptr = NULL;
	maze_node * sptr = NULL;
	maze_node * eptr = NULL;
	maze_node * wptr = NULL;
	
	//Abort if empty.
	if(!ptr1) return;
	
	//First, find the node with the supplied data type and set the first pointer to it.
	while(ptr1 && ptr1->get_data() != d)
	{
		ptr1 = ptr1->get_next();
	}
	
	//Abort if the specified node is not found.
	if(!ptr1) return;
	
	//Step through the list and set the temporary directional pointers to the nodes with the supplied data value.  A zero data value indicates no (i.e. null) connection.
	while(ptr2)
	{
		if(ptr2->get_data() == n) nptr = ptr2;
		if(ptr2->get_data() == s) sptr = ptr2;
		if(ptr2->get_data() == e) eptr = ptr2;
		if(ptr2->get_data() == w) wptr = ptr2;
		ptr2 = ptr2->get_next();
	}
	
	//Set the node directional pointers to the found locations.
	ptr1->set_directions(nptr, sptr, eptr, wptr);
	
	return;
}

//Removes all nodes in the maze.  Used by the destructor and -= operator.
void maze::remove_all()
{
	if(!head) return;
	
	maze_node * to_delete = head;
	
	while(head)
	{
		head = head->get_next();
		delete to_delete;
		to_delete = head;
	}
	
	return;
}

//Overloaded += operator, adds a node to the maze.
maze & maze::operator+=(const int to_add)
{
    add(to_add);
    return *this;
}

//Overloaded -= operator, removes all nodes from the maze (the int argument is not used).
maze & maze::operator-=(int)
{
    remove_all();
    return *this;
}

//Overloaded ! operator, moves the current pointer to the north.
maze & maze::operator!()
{
    current = current->go_north();
    return *this;
}

//Overloaded - operator, moves the current pointer to the south.
maze & maze::operator-()
{
    current = current->go_south();
    return *this;
}

//Overloaded ++ prefix operator, moves the current pointer to the east.
maze & maze::operator++()
{
    current = current->go_east();
    return *this;
}

//Overloaded --prefix operator, moves the current pointer to the west.
maze & maze::operator--()
{
    current = current->go_west();
    return *this;
}

//Returns true if the current pointer points to the same node as the end pointer.
bool maze::is_end()
{
	if(current == end) return true;
	return false;
}

//Returns true if the current pointer points to the same node as the start pointer.
bool maze::is_start()
{
	if(current == start) return true;
	return false;
}

//Sets the current pointer to the same node as the start pointer.
void maze::reset()
{
	current = start;
	return;
}

//Returns true if the north pointer is not null / movement north is possible.
bool maze::can_go_n()
{
     if(current->go_north()) return true;
     return false;
}

//Returns true if the south pointer is not null / movement south is possible.
bool maze::can_go_s()
{
     if(current->go_south()) return true;
     return false;
}

//Returns true if the east pointer is not null / movement east is possible.
bool maze::can_go_e()
{
     if(current->go_east()) return true;
     return false;
}

//Returns true if the west pointer is not null / movement west is possible.
bool maze::can_go_w()
{
     if(current->go_west()) return true;
     return false;
}

//Returns true if the head pointer is not null.
bool maze::exists()
{
	if(!head) return false;
	return true;
}
