#pragma once
#include "iostream"
using namespace std;

class LongNumber
{
public:
	// constructors
	LongNumber();								// declaration constructor 
	LongNumber(int LongNumberLengthReq);		// create Long Number of required length 
	LongNumber(char *);							// create Long Number from string with or without +/- at start
	LongNumber(const char *);					// create Long Number from string with or without +/- at start
	~LongNumber();								// destructor

												//Set Values
	void SetLongNumber(int AValue, int APos);					// set value at position in Long Number
	void SetLongNumberSign(int Sign);							// set the sign of a Long Number
	void SetLongNumberBase(int Base);							// set the base of a Long Number

																// Return Values
	int operator[](int i);																// Allows LN[i] access to Long Number
	int GetLongNumberLength();															// returns length of digits 
	int GetLongNumberSign();															// returns sign 
	int GetLongNumberBase();															// returns base
	friend LongNumber ReturnPart(LongNumber ArgA, int start, int length);				// returns part of a number - works like Mid - from start for length chars
	friend void PrintLongNumber(LongNumber ArgA);										// prints long number in verbose format from right to left (ie as it is stored)
	friend void PrintLongNumberLR(LongNumber ArgA);										// prints long number normally left to right with endl
	friend void PrintLongNumberLRNOENDL(LongNumber ArgA);										// prints long number normally left to right without endl

																						// Arithmetic Operations
																						// Basic + - * / =(assignment) 
	friend LongNumber LongNumberAdd(LongNumber ArgA, LongNumber ArgB);				// adds
	friend LongNumber LongNumberAddBase(LongNumber ArgA, LongNumber ArgB);			// adds base
	friend LongNumber operator+(LongNumber ArgA, LongNumber ArgB);					// overloads + 
	friend LongNumber LongNumberMultiply(LongNumber ArgA, LongNumber ArgB);			// multiplies two Long Numbers (base 10)
	friend LongNumber LongNumberMultiplyInt(LongNumber ArgA, int mult);				// multiplies a Long Number by an int
	friend LongNumber LongNumberMultiplyBase(LongNumber ArgA, LongNumber ArgB);		// multiplies two number not in base 10
	friend LongNumber operator*(LongNumber ArgA, LongNumber ArgB);					// overloads * for two Long Numbers
	friend LongNumber operator*(LongNumber ArgA, int mult);							// overloads * for one Long Number and mult int
	friend LongNumber LongNumberSubtract(LongNumber ArgA, LongNumber ArgB);			// subtracts
	friend LongNumber LongNumberSubtractBase(LongNumber ArgA, LongNumber ArgB);		// subtracts with base calculation
	friend LongNumber LongNumberSubtractTwosC(LongNumber ArgA, LongNumber ArgB);	// subtracts using twos complement
	friend LongNumber operator-(LongNumber ArgA, LongNumber ArgB);					// overloads -
	friend ostream& operator<< (ostream& stream, const LongNumber& ArgA); 
																					// void assign(LongNumber ArgB);												// assigns (not working)
																					// void operator=(LongNumber ArgB);												// overloads = (not working)

																					// comparison operators
	friend int LongNumberCompare(LongNumber ArgA, LongNumber ArgB);				// compares, returns 1 if >, 0 if equal and -1 if <
	friend bool operator==(LongNumber ArgA, LongNumber ArgB);					// equals
	friend bool operator!=(LongNumber ArgA, LongNumber ArgB);					// not equal
	friend bool operator>(LongNumber ArgA, LongNumber ArgB);					// greater
	friend bool operator<(LongNumber ArgA, LongNumber ArgB);					// less than
	friend bool operator>=(LongNumber ArgA, LongNumber ArgB);					// greater than or equal
	friend bool operator<=(LongNumber ArgA, LongNumber ArgB);					// less than or equal

																				// Tidying and concatenation
	friend LongNumber TrimLongNumber(LongNumber ArgA);							// trim leading zeros off Long Number 
	friend LongNumber Concatenate(LongNumber ArgA, LongNumber ArgB);			// Concatenate two Long Numbers
	friend LongNumber Pad(LongNumber ArgA, int PadLen);							// Adds left hand zeros to a Long Number
																				// these probably don't all need to be friend functions

																				// Base conversion functions
	friend LongNumber ConvertDectoBin(LongNumber ArgA);							// Base 10 Decimal to Base 2 Binary
	friend LongNumber ConvertBintoDec(LongNumber ArgA);							// Base 2 Binary to Base 10 Decimal - by doubling
	friend LongNumber ConvertBases(LongNumber ArgA, int Base);					// Converts any number to any base
	friend LongNumber TwosComplement(LongNumber ArgA, int BitLen);				// Returns the twos complement of a binary number


private:

	__int8* LongNumberValue;						// array of ints to hold long number 
	int LongNumberLength;							// number of digits in long number
	__int8 LongNumberSign;							// -1 = negative, +1 = positive
	__int8 LongNumberBase;							// base : 10 = Decimal, 2 = Binary, 16 = Hex


};


