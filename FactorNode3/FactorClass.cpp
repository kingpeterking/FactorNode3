#include "stdafx.h"
#include "FactorClass.h"
#include "iostream"
using namespace std;

FactorNode::FactorNode()
{
	// Create 0 as a Long Number
	LongNumber Zero(1);
	Zero.SetLongNumber(0, 0);
	Zero.SetLongNumberBase(10);
	Zero.SetLongNumberSign(0);

	// Creates a new node with no data or values 
	Level = 0;
	AValue = Zero;
	BValue = Zero;
	FactorComplete = false;
}


FactorNode::FactorNode(
	int LevelPassed,
	LongNumber AValuePassed,
	LongNumber BValuePassed,
	bool FactorCompletePassed)
{
	// Creates a new node with the data passed
	Level = LevelPassed;
	AValue = AValuePassed;
	BValue = BValuePassed;
	FactorComplete = FactorCompletePassed;

}

FactorNode::~FactorNode()
{
}


void FactorNode::SetLevel(int LevelPassed)
{
	Level = LevelPassed;
}

void FactorNode::SetAValue(LongNumber AValuePassed)
{
	AValue = AValuePassed;
}

void FactorNode::SetBValue(LongNumber BValuePassed)
{
	BValue = BValuePassed;

}

void FactorNode::SetFactorComplete(bool YN)
{
	FactorComplete = YN;
}



LongNumber FactorNode::GetAValue()
{
	return AValue;
}

LongNumber FactorNode::GetBValue()
{
	return BValue;
}


int FactorNode::GetLevel()
{
	return Level;
}

bool FactorNode::GetFactorComplete()
{
	return FactorComplete;
}


void PrintFactorNode(FactorNode * FNode)
{
	// Print the details for this node
	cout << "Node : " << endl;
	cout << "  Level : " << FNode->GetLevel() << endl;
	cout << "  AValue : " << FNode->GetAValue() << endl;
	cout << "  BValue : " << FNode->GetBValue() << endl;
	cout << "  Factor Complete: ";
	if (FNode->GetFactorComplete())
	{
		cout << "Y";
	}
	else
	{
		cout << "N";
	}
	cout << endl;

}
