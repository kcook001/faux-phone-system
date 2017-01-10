//texting.h
//Header declaration file for text messaging-related classes used in Assignment 3.
//These classes include: the text message class, which is a message and a contact; 
//the text message node class, which adds node functionality; the text message chain
//class, which organizes and manages a linear-linked list of text message nodes; and
//the text message chain collection class, which collects chains of texts into an
//array organized by contact.
//CS 202  Assignment #3
//Keith Cook 2-17-2016


#include <iostream>
using namespace std;

//Text Message class
class text_message
{
	public:
		//Constructors and virtual destructor.
		text_message();
		text_message(const text_message & source);
		text_message(char * m, char * c);
		virtual ~text_message();
		
		//Message setter and getter
		void set_message(char * m);
		char * get_message() const;
		
		//Contact setter and getter
		void set_contact(char * c);
		char * get_contact() const;
		
		//Display function.
		void display();
		
		//Overloaded output operator (friend class)
		friend ostream & operator<<(ostream & out, const text_message &);
		
	private:
		char * message;  //Message
		char * contact;  //Contact
};

//Text Message Node class
class text_message_node: public text_message
{
	public:
		//Constructors and destructor
		text_message_node();
		text_message_node(text_message);
		~text_message_node();
		
		//Next pointer setter and getter
		void set_next(text_message_node * n);
		text_message_node * get_next();
		
	//private:
		text_message_node * next;  //Next pointer
};

//Text Message Chain class
class text_message_chain
{
	public:
		//Constructors and destructor.
		text_message_chain();
		text_message_chain(char * c);
		text_message_chain(const text_message_chain & source);
		~text_message_chain();
		
		//Head pointer setter and getter
		void set_head(text_message_node * h);
		text_message_node * get_head() const;
		
		//Contact setter and getter
		void set_contact(char *);
		char * get_contact();
		
		//LLL ADT utility functions.
		void add(const text_message & to_add);
		text_message * retrieve(char * m_to_find);
		bool remove(text_message * to_remove);
		void remove_all();
		int display_all();
		
		//Overloaded output operator (friend class)
		friend ostream & operator<<(ostream & out, const text_message_chain &);
		
	private:
		text_message_node * head;  //Head pointer
		char * contact;            //Contact
};

//Text Message Chain Collection class
class text_message_chain_collection
{
	public:
		//Constructors and destructor
		text_message_chain_collection();
		text_message_chain_collection(int s);
		text_message_chain_collection(const text_message_chain_collection & source);
		~text_message_chain_collection();
		
		//Getters
		int get_size() const {return size;};
		int get_items() const {return items;};
		text_message_chain ** get_collection() const {return collection;};
		
		//Array utility functions.
		void add(const text_message & to_add);
		text_message_chain * retrieve(char * c_to_find);
		bool remove(char * c_to_remove);
		void remove_all();
		int display_all();
		
		bool is_contact(char * c);     //Returns true if the supplied contact is in the ADT.
		void display_chain(char * c);  //Displays a text chain for a specific contact.
		int display_contacts();        //Displays a list of all registered contacts.
		
		//Overloaded operators (members)
		text_message_chain_collection & operator=(const text_message_chain_collection &);
		text_message_chain_collection & operator+=(const text_message &);
		text_message_chain_collection & operator-=(const text_message &);
		
		//Overloaded I/O operators (friend classes)
		friend ostream & operator<<(ostream & out, const text_message_chain_collection &);
				
	private:
		text_message_chain ** collection; //Collection array
		int size;   //Size (max number of contacts)
		int items;  //Number of items in the array.
};
