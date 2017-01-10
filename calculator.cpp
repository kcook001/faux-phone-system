//calculator.cpp
//Header implementation file for the calculator operand class used in Assignment #3.
//Paired with the header declaration file 'calculator.h'
//This file contains the implemented functions for the calculator (operand) class
//defined in the 'calculator.h' header file.
//CS 202  Assignment #3
//Keith Cook 2-17-2016

#include "calculator.h"
using namespace std;

//Calculator operands member functions
//Constructor
calcop::calcop()
{
	value = 0;
	return;
}

//Destructor
calcop::~calcop()
{
	value = 0;
	return;
}

//Setter
void calcop::set_val(float v)
{
	value = v;
	return;
}

//Getter
float calcop::get_val() const
{
	return value;
}

//Overloaded assignment operator
calcop & calcop::operator=(const calcop & source)
{
	value = source.get_val();
	return *this;
}

//Overloaded addition and assignment combination operator
calcop & calcop::operator+=(const calcop & source)
{
	value += source.get_val();
	return *this;
}

//Overloaded subtraction and assignment combination operator
calcop & calcop::operator-=(const calcop & source)
{
	value -= source.get_val();
	return *this;
}

//Overloaded multiplication  and assignment combination operator
calcop & calcop::operator*=(const calcop & source)
{
	value *= source.get_val();
	return *this;
}

//Overloaded division and assignment combination operator
calcop & calcop::operator/=(const calcop & source)
{
	value /= source.get_val();
	return *this;
}

//Overloaded addition operator
calcop calcop::operator+(const calcop & source) const
{
	calcop result;
	result.set_val(value + source.get_val());
	return result;
}

//Overloaded subtraction operator
calcop calcop::operator-(const calcop & source) const
{
	calcop result;
	result.set_val(value - source.get_val());
	return result;
}

//Overloaded multiplication operator
calcop calcop::operator*(const calcop & source) const
{
	calcop result;
	result.set_val(value * source.get_val());
	return result;
}

//Overloaded division operator
calcop calcop::operator/(const calcop & source) const
{
	calcop result;
	result.set_val(value / source.get_val());
	return result;
}

//Comparison operators (functional, but not used)

//Overloaded equal to operator
bool calcop::operator==(const calcop & source)const
{
	if(value == source.get_val()) return true;
	return false;
}

//Overloaded not eqaul to operator
bool calcop::operator!=(const calcop & source)const
{
	if(value == source.get_val()) return false;
	return true;
}

//Overloaded less than operator
bool calcop::operator<(const calcop & source)const
{
	if(value < source.get_val()) return true;
	return false;
}

//Overloaded less than or equal to operator
bool calcop::operator<=(const calcop & source)const
{
	if(value <= source.get_val()) return true;
	return false;
}

//Overloaded greater than operator
bool calcop::operator>(const calcop & source)const
{
	if(value > source.get_val()) return true;
	return false;
}

//Overloaded greater than or equal to operator
bool calcop::operator>=(const calcop & source)const
{
	if(value >= source.get_val()) return true;
	return false;
}
