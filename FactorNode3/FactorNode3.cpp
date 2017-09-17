// FactorNode2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "FactorClass.h"
#include "LongNumber.h"
#include "FactorNodeQueue.h"
#include "thread"
#include "fstream"
using namespace std;

// Function Declarations
void CreateChidNodesQueue();
void InitialiseLongNumbers();
void PrintQueueInfo();

// 	Create 1 and 0 as Long Numbers - here so they have global scope and don't need to reinitialise in each routine
LongNumber One(1);
LongNumber Zero(1);
LongNumber MinusOne(1);

// Set the target as a global variable so we don't need to pass it around and copy it
LongNumber *LNTarget;
int ResultLen;
int IterCount;

// Create the queue
FactorNodeQueue FNQueue;

// Counter for number solved - global so it doesn't need to be passed around and copied
int SolvedCount = 0;

int main(int argc, char* argv[])
{
	// check passed a number to factor
	if (argc <= 1)
	{
		cout << "Insufficient arguments" << endl; 
		return 0;
	}

	// Get the number to be factorised from the command line and create as long number and set pointer to it
	char * Target = argv[1];
	LongNumber ArgPassed(Target);
	LNTarget = &ArgPassed;
	ResultLen = ArgPassed.GetLongNumberLength();

	// set up One, Zero and MinusOne
	InitialiseLongNumbers();
	IterCount = 0; 

	cout << "Factoriser START\n";
	cout << "Input Number : ";
	PrintLongNumberLR(ArgPassed);

	// Clear the text file for node overflow
	remove("QueueNode.txt");

	// Create the head item on the queue
	FactorNode FNHeadofQueue( 
		0,													// LevelPassed,
		Zero,												// AValuePassed,
		Zero,												// BValuePassed,
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
		// PrintQueueInfo();
	}

	cout << "Factoriser : Found : " << SolvedCount << " Steps : " << IterCount << " END" << endl;
	return 0;
}





void CreateChidNodesQueue()
{
	if (FNQueue.ReturnQueueSize() != 0)
	{

		// Add new elements to the queue or solve ones that are already there 
		//cout << "Create Children Nodes" << endl;

		// Get the next element from the queue 
		FactorNode FNItem = FNQueue.Pop();

		// Get the details from the FactorNode
		int Level = FNItem.GetLevel();
		// cout << "Level : " << Level << endl;
		LongNumber AValuePassed = FNItem.GetAValue();
		LongNumber BValuePassed = FNItem.GetBValue();
		// cout << " AValuePassed : " << AValuePassed << " BValuePassed : " << BValuePassed << endl;
		LongNumber MultResult(ResultLen * 2);									// Result of A * B 

		int iTarget = LNTarget->GetValue(Level);
		int iRes = 0;

		for (int iCountA = 0; iCountA <= 9; iCountA++)
		{
			int BCountFrom = 0;
			if (Level == 0) { BCountFrom = iCountA; }
			for (int iCountB = BCountFrom; iCountB <= 9; iCountB++)
			{
				AValuePassed.SetLongNumber(iCountA, Level);
				BValuePassed.SetLongNumber(iCountB, Level);
			
				MultResult = LongNumberMultiply(AValuePassed, BValuePassed);
				// cout << " MultResult : " << MultResult << " AValuePassed : " << AValuePassed << " BValuePassed : " << BValuePassed << endl;
				iRes = MultResult.GetValue(Level);				

				if (iRes == iTarget)
				{
					bool FactorComplete = false; 
					int CompResult = LongNumberCompare(MultResult, *LNTarget);			// compares, returns 1 if >, 0 if equal and -1 if <
					// cout << "Comp Result : " << CompResult << " MultResult : " << MultResult << " LNTarget : " << *LNTarget << endl;
					switch (CompResult)
					{
					case -1:			// less than
						{FactorNode FNAdd(
							Level + 1,			// LevelPassed
							AValuePassed,		// AValuePassed
							BValuePassed,		// BValuePassed
							false				// FactorCompletePassed
						);
						// PrintFactorNode(&FNAdd);
						FNQueue.Push(FNAdd);
						break;
						}
					case 0:				// solved
						FactorComplete = true; 
						cout << "SOLVED " << endl;
						cout << "AValue : ";
						PrintLongNumberLR(AValuePassed);
						cout << "BValue : ";
						PrintLongNumberLR(BValuePassed);
						cout << "QL:" << FNQueue.ReturnQueueSize() << endl;
						SolvedCount++;
						break;
					case 1: // greater than so exit B loop
						goto ExitBLoop;
						break;
					default:
						break;
					} // end switch

					
				} // end if result
				
			} // end B loop
		ExitBLoop:;
			IterCount++;
		} // end A loop

	} // end if queue

} // end function 

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
	int Len = FNQueue.ReturnQueueSize();
	cout << "Size of Queue : " << Len << endl;
}
