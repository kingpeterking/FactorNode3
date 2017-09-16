#pragma once
#include "iostream"
#include "vector"
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
	int GetValue(int i);																// returns int in position i 
	int GetLongNumberLength();															// returns length of digits 
	int GetLongNumberSign();															// returns sign 
	int GetLongNumberBase();															// returns base
	
	friend void PrintLongNumber(LongNumber ArgA);										// prints long number in verbose format from right to left (ie as it is stored)
	friend void PrintLongNumberLR(LongNumber ArgA);										// prints long number normally left to right with endl
	friend void PrintLongNumberLRNOENDL(LongNumber ArgA);								// prints long number normally left to right without endl
	friend ostream& operator<< (ostream& stream, const LongNumber& ArgA);				// overloads << for Long Numbers

	// Arithmetic Operations
	friend LongNumber LongNumberAdd(LongNumber ArgA, LongNumber ArgB);				// adds
	friend LongNumber LongNumberMultiply(LongNumber ArgA, LongNumber ArgB);			// multiplies two Long Numbers (base 10)

	// comparison operators
	friend int LongNumberCompare(LongNumber ArgA, LongNumber ArgB);				// compares, returns 1 if >, 0 if equal and -1 if <


	// Tidying and concatenation
	friend LongNumber TrimLongNumber(LongNumber ArgA);							// trim leading zeros off Long Number 
	friend LongNumber Concatenate(LongNumber ArgA, LongNumber ArgB);			// Concatenate two Long Numbers
	friend LongNumber ConcatenateIntLN(int A, LongNumber ArgB);
	friend LongNumber Pad(LongNumber ArgA, int PadLen);							// Adds left hand zeros to a Long Number
	// these probably don't all need to be friend functions


private:

	vector <int> LongNumberValue;					// vector to hold the digits of the long number
	int LongNumberLength;							// number of digits in long number
	__int8 LongNumberSign;							// -1 = negative, +1 = positive
	__int8 LongNumberBase;							// base : 10 = Decimal, 2 = Binary, 16 = Hex


};


