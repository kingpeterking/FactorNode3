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

	// Creates a new node
	ParentNode = nullptr;
	NumberOfChildren = 0;							// Haven't added children yet
	Level = 0;
	AValue = Zero;
	BValue = Zero;
	Total = Zero;
	Remainder = Zero;
	FactorComplete = false;
}


FactorNode::FactorNode(FactorNode * FactorNodeParentPassed, int LevelPassed, LongNumber AValuePassed, LongNumber BValuePassed, LongNumber TotalPassed, LongNumber RemainderPassed, bool FactorCompletePassed)
{
	// Creates a new node
	ParentNode = FactorNodeParentPassed;
	NumberOfChildren = 0;							// Haven't added children yet
	Level = LevelPassed;
	AValue = AValuePassed;
	BValue = BValuePassed;
	Total = TotalPassed;
	Remainder = RemainderPassed;
	ChildrenNodes = new FactorNode*[20]();			// create space for 20 children
	FactorComplete = FactorCompletePassed;

}

FactorNode::~FactorNode()
{
}

void FactorNode::FactorNodeAddChild(FactorNode* FactorNodeChildPassed)
{
	NumberOfChildren++;
	ChildrenNodes[NumberOfChildren] = FactorNodeChildPassed;
}

FactorNode *FactorNode::GetChild(int iChildIndex)
{
	return ChildrenNodes[iChildIndex];
}

FactorNode * FactorNode::GetParentFromChild()
{
	return ParentNode;
}

FactorNode * GetChildFromParent(FactorNode * Parent, int iChildIndex)
{
	return Parent->ChildrenNodes[iChildIndex];
}



void FactorNode::SetChild(FactorNode & Child)
{
	NumberOfChildren++;
	ChildrenNodes[NumberOfChildren] = &Child;
}



void SetParentChild(FactorNode * Parent, FactorNode & Child)
{
	int iNoChildren = Parent->GetNumberOfChidren();
	Parent->ChildrenNodes[iNoChildren] = &Child;
	iNoChildren++;
	Parent->SetNumberOfChildren(iNoChildren);
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

void FactorNode::SetNumberOfChildren(int NumberOfChildrenPassed)
{
	NumberOfChildren = NumberOfChildrenPassed;
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

int FactorNode::GetLevel()
{
	return Level;
}

int FactorNode::GetNumberOfChidren()
{
	return NumberOfChildren;
}

bool FactorNode::GetFactorComplete()
{
	return FactorComplete;
}




void PrintFactorNode(FactorNode * FNode)
{
	// Print the details for this node
	cout << "Node : " << endl;

	cout << "  NumberOfChildren : " << FNode->GetNumberOfChidren() << endl;
	cout << "  Level : " << FNode->GetLevel() << endl;

	cout << "  AValue : ";
	PrintLongNumberLR(FNode->GetAValue());
	cout << "  BValue : ";
	PrintLongNumberLR(FNode->GetBValue());
	cout << "  Total : ";
	PrintLongNumberLR(FNode->GetTotal());
	cout << "  Remainder : ";
	PrintLongNumberLR(FNode->GetRemainder());
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
