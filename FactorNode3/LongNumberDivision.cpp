#include "stdafx.h"
#include "LongNumberDivision.h"
#include "iostream"
using namespace std;


LongNumberDivision::LongNumberDivision()
{
}

LongNumberDivision::LongNumberDivision(int QuotientLength, int RemainderLength)
{
	quotient = LongNumber(QuotientLength);
	remainder = LongNumber(RemainderLength);

}


LongNumberDivision::~LongNumberDivision()
{
}

void LongNumberDivision::SetLongNumberDivisionQuotient(LongNumber ArgA)
{
	quotient = ArgA;
}

void LongNumberDivision::SetLongNumberDivisionRemainder(LongNumber ArgA)
{
	remainder = ArgA;
}

LongNumber LongNumberDivision::GetQuotient()
{
	return quotient;
}

LongNumber LongNumberDivision::GetRemainder()
{
	return remainder;
}

void PrintLongNumberDivision(LongNumberDivision ArgA)
{
	cout << "Quotient : ";
	PrintLongNumberLR(ArgA.GetQuotient());
	cout << "Remainder : ";
	PrintLongNumberLR(ArgA.GetRemainder());

}


LongNumberDivision LongNumberDivide(LongNumber ArgA, LongNumber ArgB)
{
	// Long Number Division for base 10

	// Get length of Arguments to function 
	int LenA = ArgA.GetLongNumberLength();
	int LenB = ArgB.GetLongNumberLength();

	// Check that A is greater than B - if not exit
	if (ArgB > ArgA)
	{
		// Set remainder to be ArgA, quotient is zero
		LongNumber Quotient(1);
		Quotient.SetLongNumberSign(1);
		Quotient.SetLongNumber(0, 0);

		LongNumberDivision Result(1, LenB);
		Result.SetLongNumberDivisionQuotient(Quotient);
		Result.SetLongNumberDivisionRemainder(ArgA);
		return Result;

	}

	// Set up the Long Number Registers that will hold the working 
	// ArgA and ArgB are used directly from function arguments
	// LenA is the max length that these can be
	LongNumber Quotient(LenA + 1);
	LongNumber AWorking(LenA + 1);
	LongNumber Sum(LenA + 1);					// Sum needs to be larger to cope with Q = 10 
	LongNumber NextDigit(1);
	LongNumberDivision Result(LenA + 1, LenA + 1);

	// Set up the pointers
	// No need for a ArgB pointer or a S pointer
	int APointer = 0;
	int QPointer = 0;

	// Set up the lengths
	// Len A and B already set above
	int LenQ = 0;
	int LenS = 0;
	int LenAW = 0;

	// Now load initial values into the Registers and set the pointers and lengths
	// Constructor shouls have set all values to zero, so only need to load AW now.  
	// Q, S & R are all zero to start with 
	APointer = LenA - LenB;
	LenAW = LenB;
	AWorking = ReturnPart(ArgA, APointer, LenAW);
	// PrintLongNumberLR(AWorking);
	QPointer = APointer;

	// Start the main loop that steps through A
	for (APointer; APointer >= 0; APointer--)
	{
		// Test to see if B goes into AW and if so, how many times
		if (AWorking >= ArgB)
		{
			// Calculate the number of times B goes into AW into the quotient and store this in the quotient
			for (int QM = 1; QM <= 10; QM++)
			{
				Sum = ArgB * QM;
				if (Sum > AWorking)
				{
					QM--;										// we always go one step too far
					Quotient.SetLongNumber(QM, QPointer);		// store in Quotient
					Sum = ArgB * QM;							// recalc Sum at lower level
					break;										// quit the loop
				}
			}

			// Calculate the remainder
			AWorking = AWorking - Sum;

			// PrintLongNumberLR(Sum);
			// PrintLongNumberLR(Quotient);
			// PrintLongNumberLR(AWorking);

		}

		// Reset the registers and lengths for the next iteration of the loop
		if (APointer > 0)				// no need to do this if reached end of A
		{
			NextDigit = ReturnPart(ArgA, APointer - 1, 1);
			AWorking = TrimLongNumber(Concatenate(AWorking, NextDigit));
			// PrintLongNumberLR(AWorking);
			QPointer--;
		}

	}

	// Return the Quotient and Remainder 
	Result.SetLongNumberDivisionQuotient(TrimLongNumber(Quotient));
	// PrintLongNumberLR(AWorking);
	Result.SetLongNumberDivisionRemainder(AWorking);
	return Result;
}



LongNumberDivision LongNumberDivideBase(LongNumber ArgA, LongNumber ArgB)
{
	// Long Number Division for other than base 10

	// Get length of Arguments to function 
	int LenA = ArgA.GetLongNumberLength();
	int LenB = ArgB.GetLongNumberLength();
	int SignA = ArgA.GetLongNumberSign();
	int SignB = ArgB.GetLongNumberSign();
	int BaseA = ArgA.GetLongNumberBase();
	int BaseB = ArgB.GetLongNumberBase();

	// calculate sign of result
	int SignResult = SignA / SignB;

	// Base of both numbers needs to be the same
	// no error checking here
	int BaseResult = BaseA;

	// Check that A is greater than B - if not exit
	if (ArgB > ArgA)
	{
		// Set remainder to be ArgA, quotient is zero
		LongNumber Quotient(1);
		Quotient.SetLongNumberSign(SignResult);					// Quotient picks up sign, remainder is always positive
		Quotient.SetLongNumber(0, 0);

		LongNumberDivision Result(1, LenB);
		Result.SetLongNumberDivisionQuotient(Quotient);
		Result.SetLongNumberDivisionRemainder(ArgA);
		return Result;

	}

	// Set up the Long Number Registers that will hold the working 
	// ArgA and ArgB are used directly from function arguments
	// LenA is the max length that these can be
	LongNumber Quotient(LenA + 1);
	LongNumber AWorking(LenA + 1);
	LongNumber Sum(LenA + 1);					// Sum needs to be larger to cope with Q = 10 
	LongNumber NextDigit(1);
	LongNumberDivision Result(LenA + 1, LenA + 1);

	// As QM can must be a long number - set up LN QM and One here
	LongNumber LNQM(LenA + 1);
	LNQM.SetLongNumberSign(1);
	LNQM.SetLongNumberBase(BaseA);
	// One is set to 1 in the base 
	LongNumber One(1);
	One.SetLongNumber(1, 0);
	One.SetLongNumberSign(1);
	One.SetLongNumberBase(BaseA);

	// Set up the pointers
	// No need for a ArgB pointer or a S pointer
	int APointer = 0;
	int QPointer = 0;

	// Set up the lengths
	// Len A and B already set above
	int LenQ = 0;
	int LenS = 0;
	int LenAW = 0;

	// Now load initial values into the Registers and set the pointers and lengths
	// Constructor shouls have set all values to zero, so only need to load AW now.  
	// Q, S & R are all zero to start with 
	APointer = LenA - LenB;
	LenAW = LenB;
	AWorking = ReturnPart(ArgA, APointer, LenAW);
	// PrintLongNumberLR(AWorking);
	QPointer = APointer;

	// Start the main loop that steps through A
	for (APointer; APointer >= 0; APointer--)
	{
		// Test to see if B goes into AW and if so, how many times
		if (AWorking >= ArgB)
		{
			// Calculate the number of times B goes into AW into the quotient and store this in the quotient
			for (int QM = 1; QM <= BaseResult; QM++)
			{
				// Was Sum = ArgB * QM;
				LNQM = LongNumberMultiplyInt(One, QM);
				LNQM.SetLongNumberBase(BaseResult);
				PrintLongNumberLR(LNQM);
				Sum = LongNumberMultiplyBase(ArgB, LNQM);
				PrintLongNumberLR(Sum);

				if (Sum > AWorking)
				{
					QM--;										// we always go one step too far
					Quotient.SetLongNumber(QM, QPointer);		// store in Quotient					
																// Was Sum = ArgB * QM;
					LNQM = LongNumberMultiplyInt(One, QM);						// recalc Sum at lower level
					Sum = LongNumberMultiplyBase(ArgB, LNQM);
					break;										// quit the loop
				}
			}

			// Calculate the remainder
			// Needs to be worked in BaseA
			// Was AWorking = AWorking - Sum;
			AWorking.SetLongNumberBase(BaseResult);
			AWorking = LongNumberSubtractBase(AWorking, Sum);


			// PrintLongNumberLR(Sum);
			// PrintLongNumberLR(Quotient);
			// PrintLongNumberLR(AWorking);

		}

		// Reset the registers and lengths for the next iteration of the loop
		if (APointer > 0)				// no need to do this if reached end of A
		{
			NextDigit = ReturnPart(ArgA, APointer - 1, 1);
			AWorking = TrimLongNumber(Concatenate(AWorking, NextDigit));
			// PrintLongNumberLR(AWorking);
			QPointer--;
		}

	}

	// Return the Quotient and Remainder 
	Result.SetLongNumberDivisionQuotient(TrimLongNumber(Quotient));
	// PrintLongNumberLR(AWorking);
	Result.SetLongNumberDivisionRemainder(AWorking);
	return Result;
}


LongNumberDivision operator/ (LongNumber ArgA, LongNumber ArgB)
{

	return LongNumberDivide(ArgA, ArgB);
}

