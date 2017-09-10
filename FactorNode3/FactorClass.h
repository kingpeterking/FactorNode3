#pragma once
#include "LongNumber.h"

class FactorNode
{
public:

	// Constructors and destructors
	FactorNode();									// default constructor
													// constructor with data
	FactorNode(
		LongNumber TargetPassed, 
		int LevelPassed,
		LongNumber AValuePassed,
		LongNumber BValuePassed,
		LongNumber TotalPassed,
		LongNumber RemainderPassed,
		bool FactorCompletePassed
			);
	~FactorNode();									// Destructor


	// Set Values
	void SetTarget(LongNumber TargetPassed);
	void SetLevel(int LevelPassed);
	void SetAValue(LongNumber AValuePassed);
	void SetBValue(LongNumber BValuePassed);
	void SetRemainder(LongNumber RemainderPassed);
	void SetFactorComplete(bool YN);

	// Return Values
	LongNumber GetTarget();
	int GetLevel();
	LongNumber GetAValue();
	LongNumber GetBValue();
	LongNumber GetRemainder();
	LongNumber GetTotal();
	bool GetFactorComplete();

	// Print Node
	friend void PrintFactorNode(FactorNode* FNode);

private:

	LongNumber Target; 
	int Level; 
	LongNumber AValue;
	LongNumber BValue;
	LongNumber Total;
	LongNumber Remainder;
	bool FactorComplete; 


};

