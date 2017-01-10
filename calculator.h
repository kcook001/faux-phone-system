//calcluator.h
//Header declaration file for calculator operand class used in Assignment 3.
//This is the declaration for the calculator operand class, which represents a single 
//numeric value on which mathematical operations are applied utilizing operator overloading.
//CS 202  Assignment #3
//Keith Cook 2-17-2016

//Calculator Opernad Class
class calcop
{
	public:
		calcop();                  //Constructor
		~calcop();                 //Destructor
		
		void set_val(float v);     //Setter for value.
		float get_val() const;     //Getter for value.
		
		calcop & operator=(const calcop & source);   //Overloaded assignment operator.
		
		calcop & operator+=(const calcop & source);  //Overloaded addition and assignment combination operator.
		calcop & operator-=(const calcop & source);  //Overloaded subtraction and assignment combination operator.
		calcop & operator*=(const calcop & source);  //Overloaded multiplication and assignment combination operator.
		calcop & operator/=(const calcop & source);  //Overloaded division and and assignment combination operator.
		
		calcop operator+(const calcop &) const;      //Overloaded addition operator.
		calcop operator-(const calcop &) const;      //Overloaded subtraction operator.
		calcop operator*(const calcop &) const;      //Overloaded multiplication operator.
		calcop operator/(const calcop &) const;      //Overloaded division operator.
		
		
		//Comparison operators (functional, but not used)
		bool operator==(const calcop &)const;
		bool operator!=(const calcop &)const;
		bool operator<(const calcop &)const;
		bool operator<=(const calcop &)const;
		bool operator>(const calcop &)const;
		bool operator>=(const calcop &)const;
		
		
	private:
		float value;                //Float value of the operand.
};
