//texting.cpp
//Header implementation file for the text messenger-related classes used in Assignment #3.
//Paired with the header declaration file 'texting.h'
//This file contains the implemented functions for the four classes
//defined in the 'texting.h' header file.  This includes: the text message class, which is a message and a contact; 
//the text message node class, which adds node functionality; the text message chain
//class, which organizes and manages a linear-linked list of text message nodes; and
//the text message chain collection class, which collects chains of texts into an
//array organized by contact.
//CS 202  Assignment #3
//Keith Cook 2-17-2016

#include "texting.h"
#include <iostream>
#include <cstring>
using namespace std;

//Text Message Class Member Functions

//Default constructor
text_message::text_message()
{
	message = NULL;
	contact = NULL;
	return;
}

//Copy constructor
text_message::text_message(const text_message & source)
{
	message = new char[strlen(source.get_message()+1)];
	strcpy(message, source.get_message());
	
	contact = new char[strlen(source.get_contact()+1)];
	strcpy(contact, source.get_contact());
	
	return;
}

//Constructor with arguments
text_message::text_message(char * m, char * c)
{
	message = new char[strlen(m+1)];
	strcpy(message, m);
	
	contact = new char[strlen(c+1)];
	strcpy(contact, c);
	
	return;
}

//Destructor
text_message::~text_message()
{
	if(message) delete [] message;
	if(contact) delete [] contact;
	
	message = NULL;
	contact = NULL;
	
	return;
}

//Setter for text message
void text_message::set_message(char * m)
{
	if(message) delete [] message;
	message = new char[strlen(m+1)];
	strcpy(message, m);
	
	return;
}

//Getter for text message
char * text_message::get_message() const
{
	return message;
}

//Setter for contact
void text_message::set_contact(char * c)
{
	if(contact) delete [] contact;
	contact = new char[strlen(c+1)];
	strcpy(contact, c);
	
	return;
}

//Getter for contact
char * text_message::get_contact() const
{
	return contact;
}

//Displays the text message data.
void text_message::display()
{
	cout << "Sent from: you\nTo: " << contact << endl;
	cout << "Message: " << message << endl;
	return;
}

//Overloaded << operator, displays the text message.
ostream & operator<<(ostream & out, const text_message & to_out)
{
	out << "Sent from: you\nTo: " << to_out.get_contact()<< endl;
	out << "Message: " << to_out.get_message() << endl;
    return out;
}

//Text Message Node Class Member Functions
//Constructor
text_message_node::text_message_node()
{
	next = NULL;
	return;
}

//Constructor with base class object argument
text_message_node::text_message_node(text_message source):text_message(source)
{
	next = NULL;
	return;
}

//Destructor
text_message_node::~text_message_node()
{
	next = NULL;
	return;
}

//Setter for next pointer
void text_message_node::set_next(text_message_node * n)
{
	next = n;
	return;
}

//Getter for next pointer
text_message_node * text_message_node::get_next()
{
	return next;
}

//Text Message Chain Class Member Functions
//Default constructor
text_message_chain::text_message_chain()
{
	contact = NULL;
	head = NULL;
	return;
}

//Contructor with contact argument
text_message_chain::text_message_chain(char * c)
{
	contact = new char[strlen(c)];
	strcpy(contact, c);
	
	head = NULL;
	
	return;
}

//Copy constructor
text_message_chain::text_message_chain(const text_message_chain & source)
{
	if(!source.get_head()) return;
	
	text_message_node * current = head;
	text_message_node * scurrent = source.get_head();
	
	current = new text_message_node(*scurrent);
	scurrent = scurrent->get_next();
	
	while(scurrent)
	{
		current->next = new text_message_node(*scurrent);
		current = current->get_next();
		scurrent = scurrent->get_next();
	}
	
	current->next = NULL;
	
	contact = new char[strlen(scurrent->get_contact())];
	strcpy(contact, scurrent->get_contact());
	
	return;
	
}

//Destructor
text_message_chain::~text_message_chain()
{
	if(head) remove_all();
	head = NULL;
	
	if(contact) delete [] contact;
	contact = NULL;
	
	return;
}

//Setter for head pointer
void text_message_chain::set_head(text_message_node * h)
{
	head = h;
	return;
}

//Getter for head pointer
text_message_node * text_message_chain::get_head() const
{
	return head;
}

//Setter for contact
void text_message_chain::set_contact(char * c)
{
	contact = c;
}

//Getter for contact
char * text_message_chain::get_contact()
{
	return contact;
}

//Adds a text message to the text message chain.
void text_message_chain::add(const text_message & to_add)
{
	text_message_node * temp = new text_message_node(to_add);
	text_message_node * ptr1 = NULL;
	text_message_node * ptr2 = NULL;
	
	if(!head)
	{
		head = temp;
	} else {
		{
		 ptr1 = head;
		 
		 while(ptr1)
		 {
		      ptr2 = ptr1;
		      ptr1 = ptr1->get_next();
		 }
		 ptr1 = temp;
		 ptr2->set_next(ptr1);
		 
		}
	}
	
	return;
		
}

//Returns a pointer to a text message with a message matching the one supplied.
text_message * text_message_chain::retrieve(char * m_to_find)
{
	text_message_node * current = head;
	
	while(current && strcmp(current->get_message(), m_to_find) != 0)
	{
		current = current->get_next();
	}
	
	return current;
}

//Finds and removes a text message from the list with a message matching the one supplied.
bool text_message_chain::remove(text_message * to_remove)
{
	text_message_node * current = head;
    text_message_node * prev = NULL;
     
	while(current && strcmp(current->get_message(), to_remove->get_message()) != 0)
	{
	  prev = current;
	  current = current->get_next();
	}
	
	if(current)
	{
	  prev->set_next(current->get_next());
	  current->set_next(NULL);
	  delete current;
	  return true;
	}
	
	return false;
}

//Removes all text messages from the chain.
void text_message_chain::remove_all()
{
	if(!head) return;
	
	text_message_node * current = head;
	text_message_node * to_delete = NULL;
	
	while(current)
	{
		to_delete = current;
		current = current->get_next();
		delete to_delete;
	}
	
	return;
}

//Displays all text messages in the chain.
int text_message_chain::display_all()
{	
	text_message_node * current = head;
	int count = 0;
	
	while(current)
	{
		cout << "Message #" << count + 1 << endl;
		current->display();
		++count;
		current = current->get_next();
		cout << endl;
	}
	return count;
}

//Overloaded << operator, displays all messages in the chain.
ostream & operator<<(ostream & out, const text_message_chain & to_out)
{
	text_message_node * current = to_out.get_head();
	int count = 0;
	
	while(current)
	{
		out << "Message #" << count + 1 << endl;
		out << current << endl;
		++count;
		current = current->get_next();
	}
	
    return out;
}

//Text Message Chain Collection Class Member Functions
//Default constructor.
text_message_chain_collection::text_message_chain_collection()
{
	collection = NULL;
	size = 0;
	items = 0;
	
	return;
}

//Constructor with int size argument.
text_message_chain_collection::text_message_chain_collection(int s)
{
	size = s;
	items = 0;
	collection = new text_message_chain*[size];
	
	for(int i = 0; i < size; ++i)
	{
		collection[i] = NULL;
	}
	
	return;
}

//Copy constructor.
text_message_chain_collection::text_message_chain_collection(const text_message_chain_collection & source)
{
	if(source.get_size() == 0) return;
	
	size = source.get_size();
	items = 0;
	collection = new text_message_chain*[size];
	
	for(int i = 0; i < size; ++i)
	{
		collection[i] = new text_message_chain(*source.collection[i]);
		if(collection[i]) ++items;
	}
	
	return;
}

//Destructor
text_message_chain_collection::~text_message_chain_collection()
{
	remove_all();
	collection = NULL;
	size = 0;
	items = 0;
	
	return;
}

//Adds a text message to the collection.
void text_message_chain_collection::add(const text_message & to_add)
{
	//Returns an error message if the collection does not exist and cannot be made (size = 0)
	if(!collection && size == 0)
	{
		cout << "Cannot create a collection of size 0.  Aborting action." <<endl;
		return;
	}
	
	//If the colection does not exist, create it.
	if(!collection)
	{
		collection = new text_message_chain*[size];
	
		for(int i = 0; i < size; ++i)
		{
			collection[i] = NULL;
		}
		items = 0;
	}
	
	//If the contact already has a chain in the collection, add the new text to the existing chain.
	for(int i = 0; i < items; ++i)
	{
		if(strcmp(collection[i]->get_contact(), to_add.get_contact()) == 0)
		{
			collection[i]->add(to_add);
			cout << "Message sent!" << endl;
			return;
		}
	}
	
	//Otherwise, create a new chain for the contact and add there.
	for(int i = 0; i < size; ++i)
	{
		if(collection[i] == NULL)
		{
			collection[i] = new text_message_chain(to_add.get_contact());
			collection[i]->add(to_add);
			++items;
			cout << "Message sent!" << endl;
			return;
		}
	}
	
	//If the contacts list is full, display an error message.
	cout << "Sorry, your allowed contacts list is full, so no new contacts may be added.  Texts cannot be sent to non-contacts.  Your message was not sent." <<endl;
	
	return;
}

//Returns a pointer to the text message chain with a matching contact, or NULL if not found.
text_message_chain * text_message_chain_collection::retrieve(char * c_to_find)
{
	text_message_chain * temp = NULL;
	for(int i = 0; i < items; ++i)
	{
		if(strcmp(collection[i]->get_contact(), c_to_find))
		{
			temp = collection[i];
			return temp;
		}
	}
	return temp;
}

//Deletes the chain with the matching contact, returning true if the delete was successful and false if the chain was not found.
bool text_message_chain_collection::remove(char * c_to_remove)
{
	for(int i = 0; i < items; ++i)
	{
		if(strcmp(collection[i]->get_contact(), c_to_remove))
		{
			delete collection[i];
			return true;
		}
	}
	return false;
}

//Removes every chain in the collection.
void text_message_chain_collection::remove_all()
{
	if(!collection) return;
	
	for(int i = 0; i < size; ++i)
	{
		if(collection[i]) collection[i]->remove_all();
	}
	
	delete [] collection;
	
	collection = NULL;
	size = 0;
	
	return;
}

//Displays every chain in the collection.
int text_message_chain_collection::display_all()
{
	if(!collection) return 0;
	
	int count = 0;
	
	for(int i = 0; i < items; ++i)
	{
		if(collection[i])
		{
    		cout << "Contact: " << collection[i]->get_contact() << endl;
    		collection[i]->display_all();
    		++count;
        }
	}
	
	return count;
}

//Returns true if the supplied contact has a chain in the collection.
bool text_message_chain_collection::is_contact(char * c)
{
     if(!collection) return false;
	
	for(int i = 0; i < items; ++i)
	{
		if(strcmp(collection[i]->get_contact(), c) == 0) return true;
	}
	
	return false;
}

//Displays the chain associated with the supplied contact.
void text_message_chain_collection::display_chain(char * c)
{
    if(!collection) return;
	
	for(int i = 0; i < items; ++i)
	{
		if(strcmp(collection[i]->get_contact(), c) == 0)
		{
    		cout << "Contact: " << collection[i]->get_contact() << endl;
    		collection[i]->display_all();
    		cout << endl;
        }
	}
	
	return;
}

//Displays a list of all contacts with chains in the collection.
int text_message_chain_collection::display_contacts()
{
    if(!collection) return 0;
	
	int count = 0;
	
	for(int i = 0; i < items; ++i)
	{
		if(collection[i])
		{
		    cout << "#" << i+1 << ": " << collection[i]->get_contact() << endl;
		    ++count;
        }
	}
	
	return count;
}

//Overloaded = operator, performs a deep copy.
text_message_chain_collection & text_message_chain_collection::operator=(const text_message_chain_collection & source)
{
    if(&source == this)
    {
         cout << "Assignment operation failed: self-assignment attempted." << endl << endl;
         return *this;
    }
    
    remove_all();
    
    collection = new text_message_chain*[size];
    
    for(int i = 0; i < source.get_items(); ++i)
    {
    	collection[i] = new text_message_chain(*source.get_collection()[i]);
	}
    
    return *this;
}

//Overloaded += operator, adds a text to the collection.
text_message_chain_collection & text_message_chain_collection::operator+=(const text_message & to_add)
{
    add(to_add);
    return *this;
}

//Overloaded -= operator, removes a text message from the collection.
text_message_chain_collection & text_message_chain_collection::operator-=(const text_message & to_remove)
{
    remove(to_remove.get_message());
    return *this;
}

//Overloaded << operator, displays all messages in the collection.
ostream & operator<<(ostream & out, const text_message_chain_collection & to_out)
{
	
	if(!to_out.get_collection()) return out;
	
	int count = 0;
	
	for(int i = 0; i < to_out.get_items(); ++i)
	{
		if(to_out.get_collection()[i] != NULL)
		{
    		out << "Contact: " << to_out.get_collection()[i]->get_contact() << endl;
    		to_out.get_collection()[i]->display_all();
    		out << endl;
    		++count;
        }
	}
	
	return out;
	
}
