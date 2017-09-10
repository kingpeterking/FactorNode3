#pragma once
#include "LongNumber.h"

class FactorNode
{
public:

	// Constructors and destructors
	FactorNode();									// default constructor
													// constructor with data
	FactorNode(FactorNode *FactorNodeParentPassed, int Level, LongNumber AValuePassed, LongNumber BValuePassed, LongNumber TotalPassed, LongNumber RemainderPassed, bool FactorCompletePassed);
	~FactorNode();									// Destructor

													// Add child and return child
	void FactorNodeAddChild(FactorNode *FactorNodeChildPassed);
	FactorNode * GetChild(int iChildIndex);
	friend FactorNode * GetChildFromParent(FactorNode * Parent, int iChildIndex);
	FactorNode * GetParentFromChild(); 
	// FactorNode Operator[](int iChildIndex);

	// Set Values
	void SetChild(FactorNode &Child);
	void SetAValue(LongNumber AValuePassed);
	void SetBValue(LongNumber BValuePassed);
	void SetRemainder(LongNumber RemainderPassed);
	void SetNumberOfChildren(int NumberOfChildrenPassed);
	friend void SetParentChild(FactorNode* Parent, FactorNode& Child);
	void SetFactorComplete(bool YN);

	// Return Values
	LongNumber GetAValue();
	LongNumber GetBValue();
	LongNumber GetRemainder();
	LongNumber GetTotal();
	int GetLevel();
	int GetNumberOfChidren();
	bool GetFactorComplete();

	// Print Node
	friend void PrintFactorNode(FactorNode* FNode);

private:

	FactorNode* ParentNode;
	FactorNode** ChildrenNodes;
	int NumberOfChildren;
	int Level;

	LongNumber AValue;
	LongNumber BValue;
	LongNumber Total;
	LongNumber Remainder;

	bool FactorComplete; 


};

