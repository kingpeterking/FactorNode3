// FactorNode2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "FactorClass.h"
#include "LongNumber.h"
#include "FactorNodeQueue.h"
#include "thread"
using namespace std;

// Function Declarations
void CreateChidNodesQueue();
void InitialiseLongNumbers();
void PrintQueueInfo();

// 	Create 1 and 0 as Long Numbers - here so they have global scope and don't need to reinitialise in each routine
LongNumber One(1);
LongNumber Zero(1);
LongNumber MinusOne(1);
// Create the queue
FactorNodeQueue FNQueue;

// Counter for number solved
int SolvedCount = 0;

int main(int argc, char* argv[])
{
	// check passed a number to factor
	if (argc <= 1)
	{
		cout << "Insufficient arguments" << endl; 
		return 0;
	}

	// Get the number to be factorised from the command line and create as long number
	char * Target = argv[1];
	LongNumber LNTarget(Target);
	int iTarget = LNTarget[0];

	// set up One, Zero and MinusOne
	InitialiseLongNumbers();

	cout << "Factoriser START\n";
	cout << "Input Number : ";
	PrintLongNumberLR(LNTarget);

	// Create the head item on the queue
	FactorNode FNHeadofQueue( 
		LNTarget,											// TargetPassed,
		0,													// LevelPassed,
		Zero,												// AValuePassed,
		Zero,												// BValuePassed,
		Zero,												// TotalPassed,
		Zero,												// RemainderPassed,
		false												// FactorCompletePassed
	);
	FNQueue.Push(FNHeadofQueue);

	// kick off the threads that will consume and create new queue items
	using namespace placeholders;
	while (FNQueue.ReturnQueueSize() > 0)
	{
		thread CreateConsume0(&CreateChidNodesQueue);
		thread CreateConsume1(&CreateChidNodesQueue);
		thread CreateConsume2(&CreateChidNodesQueue);
		thread CreateConsume3(&CreateChidNodesQueue);
		thread CreateConsume4(&CreateChidNodesQueue);

		CreateConsume0.join();
		CreateConsume1.join();
		CreateConsume2.join();
		CreateConsume3.join();
		CreateConsume4.join();
		PrintQueueInfo();
	}




	cout << "Factoriser : Found : " << SolvedCount << " END" << endl;
	return 0;
}





void CreateChidNodesQueue()
{
	if (FNQueue.ReturnQueueSize() != 0)
	{


		// Add new elements to the queue or solve ones that are already there 
		// cout << "Create Child" << endl;

		// Get the next element from the queue 
		FactorNode FNItem = FNQueue.Pop();

		// Get the details from the FactorNode
		LongNumber LNTarget = FNItem.GetTarget();
		int Level = FNItem.GetLevel();
		LongNumber AValuePassed = FNItem.GetAValue();
		LongNumber BValuePassed = FNItem.GetBValue();
		LongNumber Total = FNItem.GetTotal();
		LongNumber RemainderPassed = FNItem.GetRemainder();

		int ResultLen = LNTarget.GetLongNumberLength();

		LongNumber CountA(1);
		LongNumber CountB(1);
		LongNumber MultResult(ResultLen * 2);
		LongNumber MultValue(ResultLen * 2);
		LongNumber Remainder(ResultLen * 2);
		LongNumber MultResultRP(1);
		LongNumber LNTargetRP(1);
		LongNumber AValueNew(ResultLen * 2);
		LongNumber BValueNew(ResultLen * 2);

		int iTarget = LNTarget[Level];

		for (int iCountA = 0; iCountA <= 9; iCountA++)
		{
			int BCountFrom = 0;
			if (Level == 0) { BCountFrom = iCountA; }
			for (int iCountB = BCountFrom; iCountB <= 9; iCountB++)
			{
				CountA = One * iCountA;
				CountB = One * iCountB;
				if (Level > 0)
				{
					AValueNew = Concatenate(CountA, AValuePassed);
					BValueNew = Concatenate(CountB, BValuePassed);
				}
				else
				{
					// otherwise A and B are not added to previous values 
					AValueNew = CountA;
					BValueNew = CountB;
				}
				MultResult = AValueNew * BValueNew;
				MultResultRP = ReturnPart(MultResult, Level, 1);				// checks not working
				if (MultResultRP == MinusOne)
				{
					//cout << "Minus One"; 
				}
				else
				{
					LNTargetRP = ReturnPart(LNTarget, Level, 1);
					if (MultResultRP == LNTargetRP)
					{
						MultValue = AValueNew * BValueNew;
						if (MultValue <= LNTarget)
						{
							LongNumber Remainder = LNTarget - MultValue;
							bool FactorComplete = false;
							if (Remainder == Zero) { FactorComplete = true; }
							if (FactorComplete)
							{
								// if solved then print
								cout << "SOLVED " << endl;
								cout << "AValue : ";
								PrintLongNumberLR(AValueNew);
								cout << "BValue : ";
								PrintLongNumberLR(BValueNew);
								SolvedCount++;
							}
							else
							{
								// cout << "Adding to Queue" << endl;
								// CreateChidNodes2(LNTarget, Level + 1, AValueNew, BValueNew, Total, Remainder);
								FactorNode FNAdd(
									LNTarget,		// TargetPassed
									Level + 1,		// LevelPassed
									AValueNew,		// AValuePassed
									BValueNew,		// BValuePassed
									Total,			// TotalPassed
									Remainder,		// RemainderPassed
									false			// FactorCompletePassed
								);
								// PrintFactorNode(&FNAdd);
								FNQueue.Push(FNAdd);

							}
						}
					}
				}
			}
		}

	}

}

void InitialiseLongNumbers()
{
	// 	Set One as a Long Number
	One.SetLongNumber(1, 0);
	One.SetLongNumberBase(10);
	One.SetLongNumberSign(1);
	// Create zero as a Long Number
	Zero.SetLongNumber(0, 0);
	Zero.SetLongNumberBase(10);
	Zero.SetLongNumberSign(1);
	// Create minus one as a Long Number
	MinusOne.SetLongNumber(1, 0);
	MinusOne.SetLongNumberBase(10);
	MinusOne.SetLongNumberSign(-1);

}


void PrintQueueInfo()
{
	//int Len = FNQueue.ReturnQueueSize();
	//cout << "Size of Queue : " << Len << endl;
}
