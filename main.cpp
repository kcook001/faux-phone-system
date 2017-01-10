//main.cpp
//This is the client program for Assignment #3.  This program is designed to emulate a prototype for
//a beginning mobile phone for children.  The phone's features include text messaging (with a built-in
//contacts list), a basic calculator, and a maze game.  This client program primarily acts as the menu selection
//and hub between these three subprograms.  The purpose of the assignment is to demonstrate operator overloading
//in three different contexts, allowing the written classes of these subprograms to appear more naturally 
//integrated into the C++ language.
//CS 202  Assignment #3
//Keith Cook 2-17-2016

//Includes
#include <iostream>
#include "maze.h"
#include "texting.h"
#include "calculator.h"
using namespace std;

//Function prototypes
//Displays a welcome message.
void welcome();

//Displays the main options menu and returns the user's menu selection.
char options();

//The text messaging subprogram.
void texting(text_message_chain_collection & texts);

//Displays the text messaging options menu and returns the user's menu selection.
char textoptions();

//The calculator subprogram.
void calculator();

//Displays the calculator options menu and returns the user's menu selection.
char calcoptions();

//The maze game subprogram.
void maze_game(maze & game);

//Displays the maze options menu and returns the user's menu selection.
char maze_options();

int main()
{
	//Variables
	//Text messaging ADT
	const int CSIZE = 20; //Contacts list size
	text_message_chain_collection texts(CSIZE);
	
	//Maze Game ADT
	maze game;
	
	//Loads in the maze data from an external file, diaplays an error message if it can't.
	if(game.load("maze.txt") == 0)
     {
     	cout << "Maze data could not be loaded from file." << endl;
	 }
	
	//User menu choice
	char choice;
	
	//Main program
	welcome();
	
	//Main program loop
	do{
		choice = options();
		
		//
		if(choice == '1')
		{
			cout << "Text Messaging" << endl;
			texting(texts);
		} else if(choice == '2')
		{
			cout << "Calculator" << endl;
			calculator();
		} else if(choice == '3')
		{
			cout << "Maze" << endl;
			maze_game(game);
		}
	} while(choice != '0');  //Loop at user's discretion.
	
	return 0;
}

//Displays a welcome message.
void welcome()
{
	cout << "Welcome to the xPhone 800 CE Limited Edition Plus," << endl;
	cout << "the most advanced youth cell phone of the mid-80's!" << endl;
	cout << endl;
	return;
}

//Displays the main options menu and returns the user's menu selection.
char options()
{
	char choice;
	
	cout << "Here's what you can do: " << endl;
	
	do{
		cout << "1. Send or view text messages." << endl;
		cout << "2. Calculator" << endl;
		cout << "3. Maze" << endl;
		cout << "0. Exit program" << endl;
		cout << "Please enter the number of your selection:" << endl;
		cin >> choice;
		cin.ignore(20, '\n');
		
		cout << endl;
		
		//Error handling
		if(choice != '1' && choice != '2' && choice != '3' && choice != '0')
		{
			cout << "Please enter a number indicating a valid choice." << endl;
		}
		
	} while(choice != '1' && choice != '2' && choice != '3' && choice != '0');
	
	
	cout << endl;
	return choice;
}

//The text messaging subprogram.
void texting(text_message_chain_collection & texts)
{
	//Variables
    char choice;
    
    //Temp contact and size.
    char * tempc = NULL;;
    int csize = 25;
    
    //Temp message and size
    char * tempm = NULL;
    int msize = 255;
    
    //Temp text message object
    text_message * temptm = NULL;
    
    //Allocate memory.
    tempc = new char[csize];
    tempm = new char[msize];            
    
    //Text messaging loop
    do
	{
		choice = textoptions(); //Display options and get user choice.
		if(choice == '1') //Send new message
		{
			cout << "New message:" << endl;
			
			cout << "Please enter the contact you'd like to send a message to." << endl;
			cin.get(tempc, csize - 1, '\n');
			cin.ignore(100, '\n');
			
			cout << "Please enter your message." << endl;
			cin.get(tempm, msize - 1, '\n');
			cin.ignore(100, '\n');
			
			//Create new text message object from temp variables
			temptm = new text_message(tempm, tempc);
			
			//Add new message to data structure.
			texts += *temptm;
			
			//Delete temp object to reset for future messages.
			delete temptm;
			
		} else if(choice == '2') //View contacts
		{
			//Display contacts or error message if no contacts exist.
			cout << "Contacts:" << endl;
			if(texts.display_contacts() == 0) cout << "You have no saved contacts." << endl;
			
		} else if(choice == '3') //View single text thread.
		{
			//Get contact name.
			cout << "Please enter the contact you'd like to view your conversation with." << endl;
			cin.get(tempc, csize - 1, '\n');
			cin.ignore(100, '\n');
			
			//If the contact is in the data structure, display the relevant messages.
			if(texts.is_contact(tempc))
			{
                 texts.display_chain(tempc);
            } else {
                 cout << tempc << " is not in your contacts list." << endl;
            }
            
			
		} else if(choice == '4') //Display all messages
		{
			cout << "Displaying all messages:" << endl;
			cout << texts;
			//texts.display_all();
		}
	}while(choice != '0');
	
	//Clean up temp variable memory.
	if(tempc) delete [] tempc;
	if(tempm) delete [] tempm;
	
	return;
}

//Displays the text messaging options menu and returns the user's menu selection.
char textoptions()
{
	char choice;
	
	cout << endl << endl << "Text Messaging Menu: " << endl;
	
	do{
		cout << "1. Send a new text" << endl;
		cout << "2. View contacts" << endl;
		cout << "3. View all texts with a single contact" << endl;
		cout << "4. View all texts with all contacts" << endl;
		cout << "0. Exit text messaging" << endl;
		cout << "Please enter the number of your selection:" << endl;
		cin >> choice;
		cin.ignore(20, '\n');
		
		cout << endl;
		
		if(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '0')
		{
			cout << "Please enter a number indicating a valid choice." << endl;
		}
		
	} while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '0');
	
	
	cout << endl;
	return choice;
}

//The calculator subprogram
void calculator()
{
	//Calculator operand objects
	calcop val1;
	calcop val2;
	calcop result;
	
	//Temp float variable
	float temp;
	
	//User choice
	char choice;
	
	//Main subprogram loop
	do
	{
		choice = calcoptions(); //Show options and get user choice
		
		//If not exiting, get the two operands and set the corresponding objects.
		if(choice == '1' || choice == '2' || choice == '3' || choice == '4')
		{
			cout << "Please enter the first operand." << endl;
			cin >> temp;
			cin.ignore(20, '\n');
			val1.set_val(temp);
			
			cout<< endl << "Please enter the second operand." << endl;
			cin >> temp;
			cin.ignore(20, '\n');
			val2.set_val(temp);
			
			cout << endl;
			
		}
		if(choice == '1') //Addition
		{
			result = val1 + val2;
			cout << "Result: " << result.get_val() << endl << endl;
			
		} else if(choice == '2') //Subtraction
		{
			result = val1 - val2;
			cout << "Result: " << result.get_val() << endl << endl;
			
		} else if(choice == '3') //Multiplication
		{
			result = val1 * val2;
			cout << "Result: " << result.get_val() << endl << endl;
			
		} else if(choice == '4') //Division
		{
			result = val1 / val2;
			cout << "Result: " << result.get_val() << endl << endl;
		}
	}while(choice != '0'); //Loop at user's discretion.
	
	return;
}

//Displays the calculator options menu and returns the user's menu selection.
char calcoptions()
{
	char choice;
	
	cout << endl << endl << "Calculator Menu: " << endl;
	
	do{
		cout << "1. Add" << endl;
		cout << "2. Subtract" << endl;
		cout << "3. Multiply" << endl;
		cout << "4. Divide" << endl;
		cout << "0. Exit calculator" << endl;
		cout << "Please enter the number of your selection:" << endl;
		cin >> choice;
		cin.ignore(20, '\n');
		
		cout << endl;
		
		if(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '0')
		{
			cout << "Please enter a number indicating a valid choice." << endl;
		}
		
	} while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '0');
	
	
	cout << endl;
	return choice;
}

//The maze game subprogram
void maze_game(maze & game)
{
	//User choice variable
    char choice;
    
    //Abort if no maze data.
	if(!game.exists())
	{
		cout << "Maze data could not be loaded from the external file.  Returning to main menu." << endl << endl;
		return;
	}
	
	//Title
	cout << endl << endl << "The Amazing Maze: The Game" << endl;
	     
	//Main subprogram loop
    do
	{
		//If game is over, display message, reset and exit.
        if(game.is_end())
        {
             cout << "Congratulations, adventurer!  Through much trial and" << endl;
             cout << "hardship, you have managed to find the end of the maze." << endl;
             cout << "Fortune and fame (not pictured) are now yours" << endl;
             cout << "for the taking!" << endl;
             cout << "Thank you for playing!" << endl;
             cout << "Returning to main menu." << endl << endl;
             
             game.reset();
             return;
        }
        
        //Display current position (at start or not)
        if(game.is_start())
        {
             cout << "You are at the beginning of the maze." << endl;
        } else {
			cout << "You are somewhere in the maze." << endl;
		}
		
		//Give movement options.
		cout << "From here, you are able to go:" << endl;
		if(game.can_go_n()) cout << "North" << endl;
		if(game.can_go_s()) cout << "South" << endl;
		if(game.can_go_e()) cout << "East" << endl;
		if(game.can_go_w()) cout << "West" << endl;
        cout << endl;
        
        //Show input options and get user choice.
		choice = maze_options();
		if(choice == '1') //Move north
		{
			if(game.can_go_n())
			{
                 !game;
                 cout << "You cautiously move to the north." << endl << endl;
            } else {
                 cout << "You cannot go north from here.  Pick a different direction." << endl << endl;
            }
		} else if(choice == '2') //Move south
		{
			if(game.can_go_s())
			{
                 -game;
                 cout << "You carefully creep to the south." << endl << endl;
            } else {
                 cout << "You cannot go south from here.  Pick a different direction." << endl << endl;
            }
		} else if(choice == '3') //Move east
		{
			if(game.can_go_e())
			{
                 ++game;
                 cout << "You quietly tiptoe to the east." << endl << endl;
            } else {
                 cout << "You cannot go east from here.  Pick a different direction." << endl << endl;
            }
		} else if(choice == '4') //Move west
		{
			if(game.can_go_w())
			{
                 --game;
                 cout << "You confidently strut to the west." << endl << endl;
            } else {
                 cout << "You cannot go west from here.  Pick a different direction." << endl << endl;
            }
		} else if(choice == '5') //Thy Dungeon Man Easter Egg
		{
            cout << "You cannot go Dennis from here.  Pick a different direction." << endl << endl;
		}
	}while(choice != '0');
	
	//Exit message and reset.
	if(choice == '0')
	{
        cout << "Carefully backtracking to the entrance, you leave the maze." << endl << endl;
        game.reset();
    }
	return;
}

//Displays the maze game options menu and returns the user's menu selection.
char maze_options()
{
    char choice;
	
	do{
		cout << "1. Go north." << endl;
		cout << "2. Go south" << endl;
		cout << "3. Go east" << endl;
		cout << "4. Go west" << endl;
		cout << "0. Escape! (exit the maze)" << endl;
		cout << "Please enter the number of your selection:" << endl;
		cin >> choice;
		cin.ignore(20, '\n');
		
		cout << endl;
		
		if(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '0')
		{
			cout << "Please enter a number indicating a valid choice." << endl;
		}
		
	} while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '0');
	
	
	cout << endl;
	
	return choice;
}
