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
	Target = Zero;
	Level = 0;
	AValue = Zero;
	BValue = Zero;
	Total = Zero;
	Remainder = Zero;
	FactorComplete = false;
}


FactorNode::FactorNode(
	LongNumber TargetPassed,
	int LevelPassed,
	LongNumber AValuePassed,
	LongNumber BValuePassed,
	LongNumber TotalPassed,
	LongNumber RemainderPassed,
	bool FactorCompletePassed)
{
	// Creates a new node with the data passed
	Target = TargetPassed;
	Level = LevelPassed;
	AValue = AValuePassed;
	BValue = BValuePassed;
	Total = TotalPassed;
	Remainder = RemainderPassed;
	FactorComplete = FactorCompletePassed;

}

FactorNode::~FactorNode()
{
}



void FactorNode::SetTarget(LongNumber TargetPassed)
{
	Target = TargetPassed;
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

void FactorNode::SetRemainder(LongNumber RemainderPassed)
{
	Remainder = RemainderPassed;
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

LongNumber FactorNode::GetRemainder()
{
	return Remainder;
}

LongNumber FactorNode::GetTotal()
{
	return Total;
}

LongNumber FactorNode::GetTarget()
{
	return Target;
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
	cout << "Target : " << FNode->GetTarget() << endl;
	cout << "  Level : " << FNode->GetLevel() << endl;
	cout << "  AValue : " << FNode->GetAValue() << endl;
	cout << "  BValue : " << FNode->GetBValue() << endl;
	cout << "  Total : " << FNode->GetTotal() << endl;
	cout << "  Remainder : " << FNode->GetRemainder() << endl;
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
