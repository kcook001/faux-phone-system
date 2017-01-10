//maze.h
//Header declaration file for maze classes used in Assignment 3.
//This is the declaration for the two maze game-related classes for this assignment;
//the maze node class represents a single point or tile in the maze with connections
//to other maze nodes, and the maze class organizes maze nodes into a the maze proper,
//implemented as a non-linear linked list ADT.
//CS 202  Assignment #3
//Keith Cook 2-17-2016

//Maze Node class
class maze_node
{
	public:
		maze_node();         //Default constructor
		maze_node(int d);    //Data argument constructor
		~maze_node();        //Destructor
		
		void set_directions(maze_node * _n, maze_node * _s, maze_node * _e, maze_node * _w);  //Setter for directional node pointers.
		
		//Getters for directional node pointers.
		maze_node * go_north() const;      
		maze_node * go_south() const;
		maze_node * go_east() const;
		maze_node * go_west() const;
		
		//Getter and setter for next pointer (used for builing the maze)
		maze_node * get_next();
		void set_next(maze_node * n);
		
		//Getter for int data member (used for builing the maze)
		int get_data();
		
	private:
		//Directional node pointers		
		maze_node * north;
		maze_node * south;
		maze_node * east;
		maze_node * west;

		int data;               //Integer data
		maze_node * next;       //Next pointer
};

//Maze Class (a "non-linear" linked list)
class maze
{
	public:
		maze();  //Constructor
		~maze(); //Destructor
		
		//Maze building and destruction functions
		int load(const char * filename);
		bool build(int num_nodes);
		void add(int data);
		void set_directions(int d, int n, int s, int e, int w);
		void remove_all();
		
		//Overloaded wrapper operators
		maze & operator+=(const int to_add); //Adds a node to the maze ADT.
		maze & operator-=(int);              //Removes all nodes from the maze ADT.
		
		//Overloaded gameplay operators
		maze & operator!();   //Moves the current location pointer "north".
		maze & operator-();   //Moves the current location pointer "south".
		maze &operator++();   //Moves the current location pointer "east".
		maze & operator--();  //Moves the current location pointer "west".
		
		bool is_end();     //Returns true if the current pointer points to the same node as the end pointer (meaning the game is over)
		bool is_start();   //Returns true if the current pointer points to the same node as the start pointer
		void reset();      //Resets the current pointer to the same node as the start pointer.
		
		bool can_go_n();   //Returns true if the user if movement to the north is allowed (i.e. if a node exists in that direction).
		bool can_go_s();   //Returns true if the user if movement to the south is allowed (i.e. if a node exists in that direction).
		bool can_go_e();   //Returns true if the user if movement to the east is allowed (i.e. if a node exists in that direction).
		bool can_go_w();   //Returns true if the user if movement to the west is allowed (i.e. if a node exists in that direction).
		
		bool exists();     //Returns true if the maze head pointer is not null.
		
		
	private:
		maze_node * head;     //Head pointer (used to build the maze)
		maze_node * start;    //Start pointer (player start position)
		maze_node * end;      //End pointer (position of the end of the maze/win condition)
		maze_node * current;  //Current pointer (current position of the player in the maze)
};
