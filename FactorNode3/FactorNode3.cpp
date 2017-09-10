// FactorNode2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "FactorClass.h"
#include "LongNumber.h"
using namespace std;

int CreateChidNodes(FactorNode * FNode, int Level, LongNumber LNTarget);
int CreateChidNodes2(LongNumber LNTarget, int LevelPassed, LongNumber AValuePassed, LongNumber BValuePassed, LongNumber TotalPassed, LongNumber RemainderPassed);
int CreateChidNodesQueue(LongNumber LNTarget, int LevelPassed, LongNumber AValuePassed, LongNumber BValuePassed, LongNumber TotalPassed, LongNumber RemainderPassed);

// 	Create 1 and 0 as Long Numbers - here so they have global scope and don't need to reinitialise in each routine
LongNumber One(1);
LongNumber Zero(1);
LongNumber MinusOne(1);

// Counter for number solved
int SolvedCount = 0;
int IterationCount = 0; 


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

	cout << "Factoriser START\n";
	cout << "Input Number : ";
	PrintLongNumberLR(LNTarget);

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

	// create head of list 
	FactorNode FHead(nullptr, 0, Zero, Zero, Zero, Zero, false);
	FactorNode * FHeadPt = & FHead;

	// Create the children 
	// int SolvedCount = CreateChidNodes(FHeadPt, 0, LNTarget);			// Level = 1, Head = 0
	int SolvedCount = CreateChidNodes2(LNTarget, 0, Zero, Zero, Zero, Zero);
	// int SolvedCount = CreateChidNodesQueue(LNTarget, 0, Zero, Zero, Zero, Zero);

	cout << "Factoriser : Found : " << SolvedCount << " END" << endl;
	return 0;
}

int CreateChidNodes(FactorNode * FNode, int Level, LongNumber LNTarget)
{
	//cout << endl << "Start create Child Function" << endl;
	int ResultLen = LNTarget.GetLongNumberLength();
	LongNumber AValue = FNode->GetAValue(); 
		//cout << "AValue : ";
		//PrintLongNumberLR(AValue);
	LongNumber BValue = FNode->GetBValue();
		//cout << "BValue : ";
		//PrintLongNumberLR(BValue);
	LongNumber Total = FNode->GetTotal();
		//cout << "Total : ";
		//PrintLongNumberLR(BValue);
	LongNumber CountA(1);
	LongNumber CountB(1);
	LongNumber Mult1(2);
	LongNumber Mult2(ResultLen * 2);
	LongNumber Mult3(ResultLen * 2);
	LongNumber MultResult(ResultLen * 2 );
	LongNumber MultValue(ResultLen * 2);
	LongNumber Remainder(ResultLen * 2);
	LongNumber MultResultRP(1);
	LongNumber LNTargetRP(1);
	LongNumber AValueNew(ResultLen * 2);
	LongNumber BValueNew(ResultLen * 2);

	int iTarget = LNTarget[Level];
		//cout << "LNTarget : ";
		//PrintLongNumberLR(LNTarget);
		//cout << "iTarget : " << iTarget << endl;

	for (int iCountA = 0; iCountA <= 9; iCountA++)
	{
		for (int iCountB = 0; iCountB <= 9; iCountB++)
		{
			// Start of loop 
				//cout << endl << "Loop Start " << endl;
				//cout << "Level : " << Level << endl;
			
			CountA = One * iCountA;
			CountB = One * iCountB;
			if (Level > 0)
			{
				AValueNew = Concatenate(CountA, AValue);
				//cout << "AValueNew : ";
				//PrintLongNumberLR(AValueNew);
				BValueNew = Concatenate(CountB, BValue);
				//cout << "BValue : ";
				//PrintLongNumberLR(BValueNew);
			}
			else
			{
				// otherwise A and B are not added to previous values 
				AValueNew = CountA;
				//cout << "AValueNew : ";
				//PrintLongNumberLR(AValueNew);
				BValueNew = CountB;
				//cout << "BValueNew : ";
				//PrintLongNumberLR(BValueNew);
			}
			MultResult = AValueNew * BValueNew;
			// PrintLongNumberLR(MultResult);
			MultResultRP = ReturnPart(MultResult, Level, 1);				// checks not working
				//cout << "MultResultRP : ";
				//PrintLongNumberLR(MultResultRP);
			if (MultResultRP == MinusOne) 
				{ 
				//cout << "Minus One"; 
				} else
				{ 
				LNTargetRP = ReturnPart(LNTarget, Level, 1);
					//cout << "LNTargetRP : ";
					//PrintLongNumberLR(LNTargetRP);
			
					if (MultResultRP == LNTargetRP)
					{

						MultValue = AValueNew * BValueNew;
						//cout << "MultValue : ";
						//PrintLongNumberLR(MultValue);

						if (MultValue <= LNTarget)
						{
							LongNumber Remainder = LNTarget - MultValue;
							//cout << "Remainder : ";
							//PrintLongNumberLR(Remainder);
							bool FactorComplete = false;
							if (Remainder == Zero) { FactorComplete = true; }
							FactorNode * FNewNodePt = new FactorNode(FNode, Level + 1, AValueNew, BValueNew, MultValue, Remainder, FactorComplete);
							//cout << "FNewNodePt : " << &FNewNodePt << endl;
							//cout << "AValue : ";
							//PrintLongNumberLR(AValueNew);
							//cout << "BValue : ";
							//PrintLongNumberLR(BValueNew);
							SetParentChild(FNode, *FNewNodePt);
							if (FactorComplete)
							{
								PrintFactorNode(FNewNodePt);				// if solved then print
								SolvedCount++;
							}
							else
							{
								//cout << "Recursing" << endl;
								CreateChidNodes(FNewNodePt, Level + 1, LNTarget);
							}
						}
					}
				}
			}
		}

	return SolvedCount;
}


int CreateChidNodes2(LongNumber LNTarget, int LevelPassed, LongNumber AValuePassed, LongNumber BValuePassed, LongNumber TotalPassed, LongNumber RemainderPassed)
{
	// without using nodes
	// cout << "Iteration Count " << IterationCount++ << endl;

	int Level = LevelPassed;
	//cout << endl << "Start create Child Function" << endl;
	int ResultLen = LNTarget.GetLongNumberLength();
	//cout << "AValue : ";
	//PrintLongNumberLR(AValue);
	//cout << "BValue : ";
	//PrintLongNumberLR(BValue);
	LongNumber Total = TotalPassed;
	//cout << "Total : ";
	//PrintLongNumberLR(BValue);
	LongNumber CountA(1);
	LongNumber CountB(1);
	//LongNumber Mult1(2);
	//LongNumber Mult2(ResultLen * 2);
	//LongNumber Mult3(ResultLen * 2);
	LongNumber MultResult(ResultLen * 2);
	LongNumber MultValue(ResultLen * 2);
	LongNumber Remainder(ResultLen * 2);
	LongNumber MultResultRP(1);
	LongNumber LNTargetRP(1);
	LongNumber AValueNew(ResultLen * 2);
	LongNumber BValueNew(ResultLen * 2);

	int iTarget = LNTarget[Level];
	//cout << "LNTarget : ";
	//PrintLongNumberLR(LNTarget);
	//cout << "iTarget : " << iTarget << endl;

	for (int iCountA = 0; iCountA <= 9; iCountA++)
	{
		for (int iCountB = 0; iCountB <= 9; iCountB++)
		{
			// Start of loop 
			//cout << endl << "Loop Start " << endl;
			//cout << "Level : " << Level << endl;

			CountA = One * iCountA;
			CountB = One * iCountB;
			if (Level > 0)
			{
				AValueNew = Concatenate(CountA, AValuePassed);
				//cout << "AValueNew : ";
				//PrintLongNumberLR(AValueNew);
				BValueNew = Concatenate(CountB, BValuePassed);
				//cout << "BValue : ";
				//PrintLongNumberLR(BValueNew);
			}
			else
			{
				// otherwise A and B are not added to previous values 
				AValueNew = CountA;
				//cout << "AValueNew : ";
				//PrintLongNumberLR(AValueNew);
				BValueNew = CountB;
				//cout << "BValueNew : ";
				//PrintLongNumberLR(BValueNew);
			}
			MultResult = AValueNew * BValueNew;
			// PrintLongNumberLR(MultResult);
			MultResultRP = ReturnPart(MultResult, Level, 1);				// checks not working
																			//cout << "MultResultRP : ";
																			//PrintLongNumberLR(MultResultRP);
			if (MultResultRP == MinusOne)
			{
				//cout << "Minus One"; 
			}
			else
			{
				LNTargetRP = ReturnPart(LNTarget, Level, 1);
				//cout << "LNTargetRP : ";
				//PrintLongNumberLR(LNTargetRP);

				if (MultResultRP == LNTargetRP)
				{

					MultValue = AValueNew * BValueNew;
					//cout << "MultValue : ";
					//PrintLongNumberLR(MultValue);

					if (MultValue <= LNTarget)
					{
						LongNumber Remainder = LNTarget - MultValue;
						//cout << "Remainder : ";
						//PrintLongNumberLR(Remainder);
						bool FactorComplete = false;
						if (Remainder == Zero) { FactorComplete = true; }
						//cout << "AValue : ";
						//PrintLongNumberLR(AValueNew);
						//cout << "BValue : ";
						//PrintLongNumberLR(BValueNew);
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
							//cout << "Recursing" << endl;
							CreateChidNodes2(LNTarget, Level + 1, AValueNew, BValueNew, Total, Remainder);
						}
					}
				}
			}
		}
	}

	return SolvedCount;

}




int CreateChidNodesQueue(LongNumber LNTarget, int LevelPassed, LongNumber AValuePassed, LongNumber BValuePassed, LongNumber TotalPassed, LongNumber RemainderPassed)
{
	// without using nodes
	cout << "Iteration Count " << IterationCount++ << endl;

	int Level = LevelPassed;
	//cout << endl << "Start create Child Function" << endl;
	int ResultLen = LNTarget.GetLongNumberLength();
	//cout << "AValue : ";
	//PrintLongNumberLR(AValue);
	//cout << "BValue : ";
	//PrintLongNumberLR(BValue);
	LongNumber Total = TotalPassed;
	//cout << "Total : ";
	//PrintLongNumberLR(BValue);
	LongNumber CountA(1);
	LongNumber CountB(1);
	//LongNumber Mult1(2);
	//LongNumber Mult2(ResultLen * 2);
	//LongNumber Mult3(ResultLen * 2);
	LongNumber MultResult(ResultLen * 2);
	LongNumber MultValue(ResultLen * 2);
	LongNumber Remainder(ResultLen * 2);
	LongNumber MultResultRP(1);
	LongNumber LNTargetRP(1);
	LongNumber AValueNew(ResultLen * 2);
	LongNumber BValueNew(ResultLen * 2);

	int iTarget = LNTarget[Level];
	//cout << "LNTarget : ";
	//PrintLongNumberLR(LNTarget);
	//cout << "iTarget : " << iTarget << endl;

	for (int iCountA = 0; iCountA <= 9; iCountA++)
	{
		for (int iCountB = 0; iCountB <= 9; iCountB++)
		{
			// Start of loop 
			//cout << endl << "Loop Start " << endl;
			//cout << "Level : " << Level << endl;

			CountA = One * iCountA;
			CountB = One * iCountB;
			if (Level > 0)
			{
				AValueNew = Concatenate(CountA, AValuePassed);
				//cout << "AValueNew : ";
				//PrintLongNumberLR(AValueNew);
				BValueNew = Concatenate(CountB, BValuePassed);
				//cout << "BValue : ";
				//PrintLongNumberLR(BValueNew);
			}
			else
			{
				// otherwise A and B are not added to previous values 
				AValueNew = CountA;
				//cout << "AValueNew : ";
				//PrintLongNumberLR(AValueNew);
				BValueNew = CountB;
				//cout << "BValueNew : ";
				//PrintLongNumberLR(BValueNew);
			}
			MultResult = AValueNew * BValueNew;
			// PrintLongNumberLR(MultResult);
			MultResultRP = ReturnPart(MultResult, Level, 1);				// checks not working
																			//cout << "MultResultRP : ";
																			//PrintLongNumberLR(MultResultRP);
			if (MultResultRP == MinusOne)
			{
				//cout << "Minus One"; 
			}
			else
			{
				LNTargetRP = ReturnPart(LNTarget, Level, 1);
				//cout << "LNTargetRP : ";
				//PrintLongNumberLR(LNTargetRP);

				if (MultResultRP == LNTargetRP)
				{

					MultValue = AValueNew * BValueNew;
					//cout << "MultValue : ";
					//PrintLongNumberLR(MultValue);

					if (MultValue <= LNTarget)
					{
						LongNumber Remainder = LNTarget - MultValue;
						//cout << "Remainder : ";
						//PrintLongNumberLR(Remainder);
						bool FactorComplete = false;
						if (Remainder == Zero) { FactorComplete = true; }
						//cout << "AValue : ";
						//PrintLongNumberLR(AValueNew);
						//cout << "BValue : ";
						//PrintLongNumberLR(BValueNew);
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
							//cout << "Recursing" << endl;
							// CreateChidNodes2(LNTarget, Level + 1, AValueNew, BValueNew, Total, Remainder);
							cout << "Add to Queue : " << endl;
							cout << "LNTarget : " << LNTarget << endl;
							cout << "Level + 1 : " << Level + 1 << endl;
							cout << "AValueNew : " << AValueNew << endl;
							cout << "BValueNew : " << BValueNew << endl;
							cout << "Total : " << Total << endl;
							cout << "Remainder : " << Remainder << endl;
						}
					}
				}
			}
		}
	}

	return SolvedCount;

}
