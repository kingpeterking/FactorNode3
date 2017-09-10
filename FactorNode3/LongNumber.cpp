#include "stdafx.h"
#include "LongNumber.h"
#include "LongNumberDivision.h"
#include "iostream"
#include "cmath"
#include "string"
using namespace std;

LongNumber::LongNumber()
{
}

LongNumber::LongNumber(int LongNumberLengthReq)
{
	// cout << "LN Constructor" << endl;
	// cout << "Length : " << LongNumberLengthReq << endl;
	// cout << "New Array" << endl;
	LongNumberValue = new __int8[LongNumberLengthReq]();
	// cout << "Length" << endl;
	LongNumberLength = LongNumberLengthReq;
	// cout << "Sign" << endl;
	LongNumberSign = 1;										// Defaults to positive
															// cout << "Base" << endl;
	LongNumberBase = 10;									// Defaults to base 10

}

LongNumber::LongNumber(char * NoA)
{
	int Sign = 1;  // assume positive if no sign indicator
	int HasSign = 0;
	int NumStart = 0;

	LongNumberSign = 1; // Defaults to positive

						// Work out if NoA has a sign indicator
	if (NoA[0] == '-')
	{
		//cout << "Neg sign found" << endl;
		Sign = -1;
		HasSign = 1;
		LongNumberSign = -1;
	}
	else if (NoA[0] == '+')
	{
		//cout << "Pos sign found" << endl;
		Sign = 1;
		HasSign = 1;
		LongNumberSign = 1;
	}

	// Constructor from char array pointer
	int NoALen = 0;
	while (NoA[NoALen] != '\0')
	{
		NoALen++;
		//cout << NoALen;
	}

	if (HasSign == 1)
	{
		// Reduce length by one if sign present
		NoALen--;
		NumStart = 1;
		//cout << "Has sign, new len NoALen " << NoALen << " num start " << NumStart << endl;
	}

	LongNumberValue = new __int8[NoALen]();


	for (int iCount = 0; iCount < NoALen; iCount++)
	{
		LongNumberValue[iCount] = NoA[(NoALen)-(iCount + 1) + HasSign] - 48;
		//cout << iCount << " : " << (NoALen) - (iCount + 1) + HasSign <<  " : " << NoA[(NoALen)-(iCount + 1) + HasSign] - 48 << endl;
	}
	LongNumberLength = NoALen;

	// cout << "Base" << endl;
	LongNumberBase = 10;									// Defaults to base 10

															//cout << endl;
}


LongNumber::LongNumber(const char * NoA)
{
	int Sign = 1;  // assume positive if no sign indicator
	int HasSign = 0;
	int NumStart = 0;

	LongNumberSign = 1; // Defaults to positive

						// Work out if NoA has a sign indicator
	if (NoA[0] == '-')
	{
		//cout << "Neg sign found" << endl;
		Sign = -1;
		HasSign = 1;
		LongNumberSign = -1;
	}
	else if (NoA[0] == '+')
	{
		//cout << "Pos sign found" << endl;
		Sign = 1;
		HasSign = 1;
		LongNumberSign = 1;
	}

	// Constructor from char array pointer
	int NoALen = 0;
	while (NoA[NoALen] != '\0')
	{
		NoALen++;
		//cout << NoALen;
	}

	if (HasSign == 1)
	{
		// Reduce length by one if sign present
		NoALen--;
		NumStart = 1;
		//cout << "Has sign, new len NoALen " << NoALen << " num start " << NumStart << endl;
	}

	LongNumberValue = new __int8[NoALen]();


	for (int iCount = 0; iCount < NoALen; iCount++)
	{
		LongNumberValue[iCount] = NoA[(NoALen)-(iCount + 1) + HasSign] - 48;
		//cout << iCount << " : " << (NoALen) - (iCount + 1) + HasSign <<  " : " << NoA[(NoALen)-(iCount + 1) + HasSign] - 48 << endl;
	}
	LongNumberLength = NoALen;

	// cout << "Base" << endl;
	LongNumberBase = 10;									// Defaults to base 10

															//cout << endl;
}

LongNumber::~LongNumber()
{
	// delete[] LongNumberValue;
}

void LongNumber::SetLongNumber(int AValue, int APos)
{
	LongNumberValue[APos] = AValue;
}

void LongNumber::SetLongNumberSign(int Sign)
{
	LongNumberSign = Sign;

}

void LongNumber::SetLongNumberBase(int Base)
{
	LongNumberBase = Base;
}


int LongNumber::operator[](int i)
{
	return LongNumberValue[i];
}


int LongNumber::GetLongNumberLength()
{
	return LongNumberLength;
}

int LongNumber::GetLongNumberSign()
{
	return LongNumberSign;
}

int LongNumber::GetLongNumberBase()
{
	return LongNumberBase;
}

LongNumber ConvertDectoBin(LongNumber ArgA)
{
	// Converts ArgA to binary through repeated division by 2
	// Assumes the number is positive, left to calling routine to sort out the sign

	// Get length of ArgA and calculate length of binary result
	int LenA = ArgA.GetLongNumberLength();
	// calculates the length of Result by the formula log b X = log a X / log a b
	double basefrom = 10;
	double baseto = 2;
	double logbase2 = log10(baseto);
	int LenResult = (int)(LenA / logbase2) + 2;						// add a couple to make sure have room

																	// construct the result and a temp 
	LongNumber Result(LenResult);
	LongNumberDivision TempResult(LenA, LenA);
	LongNumber Remainder(1);

	// Create 2 as a Long Number
	LongNumber Two(1);
	Two.SetLongNumber(2, 0);
	// Create 0 as a Long Number
	LongNumber Zero(1);
	Zero.SetLongNumber(0, 0);

	// cout << "Conversion Loop" << endl;

	for (int iCount = 0; iCount < LenResult; iCount++)
	{
		// cout << "Dividing : ";
		// PrintLongNumberLR(ArgA);
		// cout << " by ";
		// PrintLongNumberLR(Two);
		TempResult = ArgA / Two;											// Divide the Argument by 2

																			// cout << "Temp Result : "; 
																			// PrintLongNumberDivision(TempResult);

		ArgA = TempResult.GetQuotient();									// Put the quotient back in ArgA for next loop	
		if (ArgA <= Zero) {													// Check for ArgA =0 here	
																			// Got to zero - so store remainder then quit loop
			Remainder = TempResult.GetRemainder();								// Get the remainder
																				// cout << "Last Remainder";
																				// PrintLongNumberLR(Remainder);
			Result.SetLongNumber(Remainder[0], iCount); 						// Store remainder in Result
			break;
		}

		Remainder = TempResult.GetRemainder();								// Get the remainder
		Result.SetLongNumber(Remainder[0], iCount); 						// Store remainder in Result
																			// cout << "Result : "; 
																			// PrintLongNumberLR(Result); 

	}

	// PrintLongNumberLR(Result);
	Result = TrimLongNumber(Result);

	return Result;
}

LongNumber ConvertBintoDec(LongNumber ArgA)
{

	// Convert ArgA to decimal by the doubling method 
	int LenA = ArgA.GetLongNumberLength();
	int SignA = ArgA.GetLongNumberSign();
	int BaseA = ArgA.GetLongNumberBase();

	// Create 0 as a Long Number
	LongNumber Zero(1);
	Zero.SetLongNumber(0, 0);
	Zero.SetLongNumberBase(10);
	Zero.SetLongNumberSign(0);
	// Create One as a Long Number
	LongNumber One(1);
	One.SetLongNumber(1, 0);
	One.SetLongNumberBase(10);
	One.SetLongNumberSign(0);
	// Create Two as a Long Number
	LongNumber Two(1);
	Two.SetLongNumber(2, 0);
	Two.SetLongNumberBase(10);
	Two.SetLongNumberSign(0);

	if (BaseA != 2)
	{

		return Zero;
	}

	// Calculate the length of the return
	int ResultLen = (int)(LenA * log10(2)) + 2;

	// Construct LN result 
	LongNumber LNResult(ResultLen);
	LNResult.SetLongNumberBase(10);
	LNResult.SetLongNumberSign(SignA);

	// Doubling loop
	for (int iCount = 0; iCount <= LenA; iCount++)
	{
		LNResult = LongNumberMultiply(LNResult, Two);
		if (ArgA[LenA - iCount] == 1)
		{
			LNResult = LongNumberAdd(LNResult, One);
		}
		// PrintLongNumberLR(LNResult);

	}

	return LNResult;

}

LongNumber ConvertBases(LongNumber ArgA, int BaseTo)
{
	// Converts ArgA to new base through repeated division by Base
	// Assumes the number is positive, left to calling routine to sort out the sign
	// cout << "Convert Base to : " << BaseTo << endl;

	// Get length of ArgA and calculate length of result
	int LenA = ArgA.GetLongNumberLength();
	int BaseFrom = ArgA.GetLongNumberBase();
	// cout << "Len A : " << LenA << " Base From : " << BaseFrom << endl;

	// calculates the length of Result by the formula log b X = log a X / log a b
	// becomes LenA x (log10 BaseFrom / Log10 BaseTo)
	double BaseFromL10 = log10(BaseFrom);
	double BaseTo10 = log10(BaseTo);
	int LenResult = (int)(LenA * (BaseFromL10 / BaseTo10)) + 2;						// add a couple to make sure have room
																					// cout << "Len Result : " << LenResult << endl; 

																					// construct the result and a temp 
	LongNumber Result(LenResult);
	LongNumberDivision TempResult(LenResult, LenResult);
	int LenBaseTo = (int)(log10(BaseTo) + 1);
	LongNumber Remainder(LenBaseTo);

	// Create One as a Long Number
	LongNumber One(1);
	One.SetLongNumber(1, 0);
	// Create 0 as a Long Number
	LongNumber Zero(1);
	Zero.SetLongNumber(0, 0);

	// Create BaseTo as a Long Number
	LongNumber BaseToDivider(LenBaseTo);
	BaseToDivider = LongNumberMultiplyInt(One, BaseTo);
	BaseToDivider.SetLongNumberBase(BaseTo);
	// PrintLongNumberLR(BaseToDivider);

	// cout << "Conversion Loop" << endl;

	for (int iCount = 0; iCount < LenResult; iCount++)
	{
		// cout << "Dividing : ";
		// PrintLongNumberLR(ArgA);
		// cout << " by ";
		// PrintLongNumberLR(BaseToDivider);
		TempResult = LongNumberDivideBase(ArgA, BaseToDivider);			// Divide the Argument by BaseTo
																		// PrintLongNumberDivision(TempResult);
																		// cout << "Temp Result : "; 
																		// PrintLongNumberDivision(TempResult);

		ArgA = TempResult.GetQuotient();									// Put the quotient back in ArgA for next loop	
		if (ArgA <= Zero) {													// Check for ArgA =0 here	
																			// Got to zero - so store remainder then quit loop
			Remainder = TempResult.GetRemainder();								// Get the remainder
																				// cout << "Last Remainder";
																				// PrintLongNumberLR(Remainder);
			Result.SetLongNumber(Remainder[0], iCount); 						// Store remainder in Result
			break;
		}

		Remainder = TempResult.GetRemainder();								// Get the remainder
		Result.SetLongNumber(Remainder[0], iCount); 						// Store remainder in Result
																			// cout << "Result : "; 
																			// PrintLongNumberLR(Result); 

	}

	// PrintLongNumberLR(Result);
	Result = TrimLongNumber(Result);
	Result.SetLongNumberBase(BaseTo);

	return Result;


}

LongNumber TwosComplement(LongNumber ArgA, int BitLen)
{
	// Returns the twos complement of ArgA
	// picks up the sign of A
	// BitLen is the length of the required result - needed when subtracting two numbers as they need the same bit length 
	// Binary number so Base is set to 2
	// Should check that number passed is binary, but not implemented

	int SignA = ArgA.GetLongNumberSign();
	int LenA = ArgA.GetLongNumberLength();

	int PadRequired = BitLen - LenA;					// need to pad A with leading zeros
	int ReturnLen = BitLen;								// obvious but included to aid clarity of code

	LongNumber LNReturn(ReturnLen);
	LNReturn.SetLongNumberSign(SignA);
	LNReturn.SetLongNumberBase(2);

	// PrintLongNumberLR(ArgA);
	// invert the bits in ArgA
	for (int iCount = 0; iCount < ReturnLen; iCount++)
	{
		if (iCount < LenA)
		{	// ArgA has values to be inverted
			if (ArgA[iCount] == 0)
			{
				LNReturn.SetLongNumber(1, iCount);
			}
			else
			{
				LNReturn.SetLongNumber(0, iCount);
			}
		}
		else
		{	// ArgA is used up, so these are padding - assumed to be zero
			LNReturn.SetLongNumber(1, iCount);
		}
	}
	// cout << "Ones complement";
	// PrintLongNumberLR(LNReturn);

	// Now add one determined by the sign
	if (SignA == -1)
	{
		LongNumber OneB2(1);
		OneB2.SetLongNumber(1, 0);
		OneB2.SetLongNumberBase(2);
		OneB2.SetLongNumberSign(1);
		LNReturn = LongNumberAddBase(LNReturn, OneB2);
		LNReturn.SetLongNumberSign(SignA);
		LNReturn.SetLongNumberBase(2);
	}
	// cout << "Twos complement"; 
	// PrintLongNumberLR(LNReturn);

	// drop the MSB from LNReturn
	LNReturn = ReturnPart(LNReturn, 0, ReturnLen - 1);

	// PrintLongNumberLR(LNReturn);
	return LNReturn;
}

/*
void LongNumber::assign(LongNumber ArgB)
{
// makes this = to ArgB
// constructor will have already been called that sets the length
// this function sets the sign and copies the digits
int ArgBLen = ArgB.GetLongNumberLength();
int SignB = ArgB.GetLongNumberSign();

LongNumberSign = SignB;
LongNumberLength = ArgBLen;

for (int iCount = 0; iCount < ArgBLen - 1; iCount++)
{
LongNumberValue[iCount] = ArgB[iCount];
}

}


void LongNumber::operator=(LongNumber ArgB)
{
assign(ArgB);
}
*/


LongNumber TrimLongNumber(LongNumber ArgA)
{
	// Returns a new Long Number with leading zeros removed
	// if all zeros returns a long number with a single zero
	int Sign = ArgA.GetLongNumberSign();
	int BaseA = ArgA.GetLongNumberBase();

	//cout << "Trimming \n";
	int LenA = ArgA.GetLongNumberLength();
	//cout << "Len A : " << LenA << endl; 
	int iCount = LenA - 1;
	//cout << "iCount : " << iCount << endl;

	while (ArgA[iCount] == 0) { iCount--; }
	// cout << "iCount after while: " << iCount << endl;

	if (iCount >= 0)
	{
		LongNumber ReturnLN(iCount + 1);
		ReturnLN.SetLongNumberSign(Sign);
		ReturnLN.SetLongNumberBase(BaseA);

		for (int iAddtoRet = 0; iAddtoRet <= iCount; iAddtoRet++)
		{
			//cout << "iAddtoRet : " << iAddtoRet << endl;
			ReturnLN.SetLongNumber(ArgA[iAddtoRet], iAddtoRet);
		}
		// PrintLongNumberLR(ReturnLN);
		return ReturnLN;
	}
	else
	{
		// returning 0
		LongNumber ReturnLN(1);
		ReturnLN.SetLongNumberSign(1);
		ReturnLN.SetLongNumberBase(BaseA);
		ReturnLN.SetLongNumber(0, 0);
		return ReturnLN;
	}


}

LongNumber Concatenate(LongNumber ArgA, LongNumber ArgB)
{
	// Concatenate two long numbers
	// Take the sign from ArgA, ignore the sign from ArgB
	int ArgALen = ArgA.GetLongNumberLength();
	int ArgBLen = ArgB.GetLongNumberLength();
	int SignA = ArgA.GetLongNumberSign();
	int iResultLen = ArgALen + ArgBLen;

	// construct holder for return 
	LongNumber Result(iResultLen);

	// Put ArgB in by simple assignment
	// Result = ArgB;
	for (int iCount = 0; iCount < ArgBLen; iCount++)
	{
		Result.SetLongNumber(ArgB[iCount], iCount);
	}

	// Add digits from ArgA
	for (int iCount = ArgBLen; iCount < iResultLen; iCount++)
	{
		Result.SetLongNumber(ArgA[iCount - ArgBLen], iCount);
	}

	Result.SetLongNumberSign(SignA);
	return Result;
}

LongNumber Pad(LongNumber ArgA, int PadLen)
{
	// Pads ArgA with leading zeros 
	int LenA = ArgA.GetLongNumberLength();
	int SignA = ArgA.GetLongNumberSign();
	int BaseA = ArgA.GetLongNumberBase();
	int ReturnLen = LenA + PadLen;

	// Build the return Long Number
	LongNumber LNReturn(ReturnLen);
	LNReturn.SetLongNumberSign(SignA);
	LNReturn.SetLongNumberBase(BaseA);

	// Copy ArgA into Return
	for (int iCount = 0; iCount < LenA; iCount++)
	{
		LNReturn.SetLongNumber(ArgA[iCount], iCount);
	}

	// Add zeros to Return
	for (int iCount = LenA; iCount < PadLen; iCount++)
	{
		LNReturn.SetLongNumber(0, iCount);
	}

	// PrintLongNumberLR(LNReturn);

	return LNReturn;

}

LongNumber ReturnPart(LongNumber ArgA, int start, int length)
{
	// Returns part of the long number
	// starts at position Start for length numbers
	// works like mid
	// works from right to left - so position 0 is the units column

	//cout << "Returning Part" << endl;
	//cout << "Start : " << start << endl;
	//cout << "Length : " << length << endl;
	//PrintLongNumberLR(ArgA);

	// create holder for result
	// should check that length of this is greater than length, but haven't implemented error handling yet!

	LongNumber LNReturn(length);
	int SignA = ArgA.GetLongNumberSign();
	int BaseA = ArgA.GetLongNumberBase();

	// Check length of ArgA vs start and length 
	LongNumber MinusOne(1);
	MinusOne.SetLongNumber(1, 0);
	MinusOne.SetLongNumberBase(10);
	MinusOne.SetLongNumberSign(-1);

	int LenA = ArgA.GetLongNumberLength();
	if (LenA <= start)  { return MinusOne; }
	if (LenA < length) { return MinusOne; }

	// PrintLongNumberLR(ArgA);

	// build the new number character by character
	for (int iCount = 0; iCount < length; iCount++)
	{
		LNReturn.SetLongNumber(ArgA[start + iCount], iCount);
	}

	// set sign to match
	LNReturn.SetLongNumberSign(SignA);
	LNReturn.SetLongNumberBase(BaseA);

	// PrintLongNumberLR(LNReturn);
	return LNReturn;
}

void PrintLongNumber(LongNumber ArgA)
{
	if (ArgA.GetLongNumberSign() == -1)
	{
		//cout << "-" << endl;
	}

	for (int iCount = 0; iCount < ArgA.GetLongNumberLength(); iCount++)
	{
		// cout << "Long Number Value : Pos : " << iCount << " : " << ArgA.GetLongNumber()[iCount] << "\n";
		cout << "Long Number Value : Pos : " << iCount << " : " << ArgA[iCount] << "\n";

	}

}

void PrintLongNumberLR(LongNumber ArgA)
{
	if (ArgA.GetLongNumberSign() == -1)
	{
		cout << "-";
	}
	for (int iCount = ArgA.GetLongNumberLength() - 1; iCount >= 0; iCount--)
	{
		// cout <<  ArgA.GetLongNumber()[iCount] ;
		cout << ArgA[iCount];
	}
	cout << "\n";

}

void PrintLongNumberLRNOENDL(LongNumber ArgA)
{
	if (ArgA.GetLongNumberSign() == -1)
	{
		cout << "-";
	}
	for (int iCount = ArgA.GetLongNumberLength() - 1; iCount >= 0; iCount--)
	{
		// cout <<  ArgA.GetLongNumber()[iCount] ;
		cout << ArgA[iCount];
	}

}



LongNumber LongNumberAdd(LongNumber ArgA, LongNumber ArgB)
{
	// Adds two long numbers
	//cout << "Adding Numbers \n";

	// get the length of both numbers 
	int iCount;
	int ArgALen = ArgA.GetLongNumberLength();
	int ArgBLen = ArgB.GetLongNumberLength();
	int SignA = ArgA.GetLongNumberSign();
	int SignB = ArgB.GetLongNumberSign();
	int iResultLen = ArgALen;
	//cout << "Length Arg A : " << ArgALen << " : Length Arg B : " << ArgBLen << endl;

	if (ArgBLen > ArgALen)
	{
		//cout << "Len B greater than A\n";
		iResultLen = ArgBLen;
	}
	// no need to test for them being both the same length 

	// Add the two numbers
	int iCarry = 0;
	int iSumUnit = 0;
	int iSum = 0;
	int SignRes = 1; // holder until implement subtraction 

	LongNumber LNResult(iResultLen + 1);
	LNResult.SetLongNumberSign(SignRes);
	//cout << "Result Len : " << iResultLen << '\n';

	//cout << "Adding Loop \n";
	for (iCount = 0; iCount < iResultLen; iCount++)
	{
		int AVal;
		int BVal;
		if (iCount < ArgALen)
		{
			AVal = ArgA[iCount];
		}
		else
		{
			AVal = 0;
		}

		if (iCount < ArgBLen)
		{
			BVal = ArgB[iCount];
		}
		else
		{
			BVal = 0;
		}

		iSum = AVal + BVal + iCarry;
		iSumUnit = iSum % 10;
		iCarry = (iSum - iSumUnit) / 10;
		LNResult.SetLongNumber(iSumUnit, iCount);
		//cout << "iSum : " << iSum << endl; 
		//cout << "iSumUnit : " << iSumUnit << endl;
		//cout << "iCarry : " << iCarry << endl;
	}
	if (iCarry > 0)
	{
		LNResult.SetLongNumber(iCarry, iResultLen);
	}

	// PrintLongNumberLR(LNResult);
	LNResult = TrimLongNumber(LNResult);
	// PrintLongNumberLR(LNResult);

	return LNResult;

}

LongNumber LongNumberAddBase(LongNumber ArgA, LongNumber ArgB)
{

	// Adds two long numbers
	//cout << "Adding Numbers \n";

	// get the length of both numbers 
	int iCount;
	int ArgALen = ArgA.GetLongNumberLength();
	int ArgBLen = ArgB.GetLongNumberLength();
	int SignA = ArgA.GetLongNumberSign();
	int SignB = ArgB.GetLongNumberSign();
	int BaseA = ArgA.GetLongNumberBase();
	int BaseB = ArgB.GetLongNumberBase();
	int iResultLen = ArgALen;
	//cout << "Length Arg A : " << ArgALen << " : Length Arg B : " << ArgBLen << endl;

	if (ArgBLen > ArgALen)
	{
		//cout << "Len B greater than A\n";
		iResultLen = ArgBLen;
	}
	// no need to test for them being both the same length 

	// Add the two numbers
	int iCarry = 0;
	int iSumUnit = 0;
	int iSum = 0;
	int SignRes = 1; // holder until implement subtraction 

	LongNumber LNResult(iResultLen + 1);
	LNResult.SetLongNumberSign(SignRes);
	//cout << "Result Len : " << iResultLen << '\n';

	//cout << "Adding Loop \n";
	for (iCount = 0; iCount < iResultLen; iCount++)
	{
		int AVal;
		int BVal;
		if (iCount < ArgALen)
		{
			AVal = ArgA[iCount];
		}
		else
		{
			AVal = 0;
		}

		if (iCount < ArgBLen)
		{
			BVal = ArgB[iCount];
		}
		else
		{
			BVal = 0;
		}

		iSum = AVal + BVal + iCarry;
		iSumUnit = iSum % BaseA;
		iCarry = (iSum - iSumUnit) / BaseA;
		LNResult.SetLongNumber(iSumUnit, iCount);
		//cout << "iSum : " << iSum << endl; 
		//cout << "iSumUnit : " << iSumUnit << endl;
		//cout << "iCarry : " << iCarry << endl;
	}
	if (iCarry > 0)
	{
		LNResult.SetLongNumber(iCarry, iResultLen);
	}

	// PrintLongNumberLR(LNResult);
	// LNResult = TrimLongNumber(LNResult);
	// PrintLongNumberLR(LNResult);

	return LNResult;


}


LongNumber LongNumberMultiply(LongNumber ArgA, LongNumber ArgB)
{

	// Multiplies two long numbers
	// cout << "Multiplying Numbers \n";

	// get the length of both numbers 
	int ArgALen = ArgA.GetLongNumberLength();
	int ArgBLen = ArgB.GetLongNumberLength();
	int SignA = ArgA.GetLongNumberSign();
	int SignB = ArgB.GetLongNumberSign();

	// PrintLongNumberLR(ArgA);
	// PrintLongNumberLR(ArgB);

	// cout << "Length Arg A : " << ArgALen << " : Length Arg B : " << ArgBLen << endl;
	// cout << " Sign A : " << SignA << " Sign B : " << SignB << endl;

	// Set length of result
	int iResultLen = ArgALen;
	if (ArgBLen > ArgALen)
	{
		// cout << "Len B greater than A\n";
		iResultLen = ArgBLen;
	}
	// no need to test for them being both the same length 


	// Multiply the two numbers
	int iCarry = 0;
	int iSumUnit = 0;
	int iSum = 0;
	int iCountA = 0;
	int iCountB = 0;
	int iAVal = 0;
	int iBVal = 0;
	int SignRes = SignA * SignB; // Calculate sign of result 
								 // cout << "Sign Res " << SignRes << endl;

	LongNumber LNResult(iResultLen * 2);		// this is the returned value that is built by repeatedly adding the LNResultTemp on each cycle
	LNResult.SetLongNumberSign(SignRes);

	// cout << "Multiplying Loop \n";
	for (iCountA = 0; iCountA < iResultLen; iCountA++)
	{

		for (iCountB = 0; iCountB < iResultLen; iCountB++)
		{
			// cout << "Start B loop" << endl;
			int ConstructLen = iResultLen * 2;
			// cout << "Pre LN Constructor" << endl;
			LongNumber LNResultTemp(ConstructLen);
			// cout << "Pre LN Sign" << endl; 
			LNResult.SetLongNumberSign(SignRes);
			// cout << endl;
			// cout << "iResultLen : " << iResultLen << endl;
			//cout << "iCountA : " << iCountA << endl;
			//cout << "iCountB : " << iCountB << endl;
			if (iCountA < ArgALen)
			{
				iAVal = ArgA[iCountA];
			}
			else
			{
				iAVal = 0;
			}
			if (iCountB < ArgBLen)
			{
				iBVal = ArgB[iCountB];
			}
			else
			{
				iBVal = 0;
			}
			//cout << "AVal : " << iAVal << endl;
			//cout << "BVal : " << iBVal << endl;
			iSum = (iAVal * iBVal);
			//cout << "iSum : " << iSum << endl;
			iSumUnit = iSum % 10;
			//cout << "iSumUnit : " << iSumUnit << endl;
			iCarry = (iSum - iSumUnit) / 10;
			//cout << "iCarry : " << iCarry << endl;
			LNResultTemp.SetLongNumber(iSumUnit, iCountB + iCountA);
			LNResultTemp.SetLongNumber(iCarry, iCountB + iCountA + 1);
			//PrintLongNumberLR(LNResultTemp);
			LNResult = LongNumberAdd(LNResult, LNResultTemp);		// sign not yet implemented for adding
																	// PrintLongNumberLR(LNResult);
			LNResult = TrimLongNumber(LNResult);
			// PrintLongNumberLR(LNResult);
		}

	}

	LNResult.SetLongNumberSign(SignRes);		// sign not yet implemented for adding

												//LNResult.SetLongNumber(iCarry, iResultLen);

												//PrintLongNumber(LNResult);

	return LNResult;


}

LongNumber LongNumberMultiplyInt(LongNumber ArgA, int mult)
{
	// Create a Long Number based on mult (using the char constructor
	// Then use the standard multiply function 
	string sMultChar = to_string(mult);
	char const *MultCharPointer = sMultChar.c_str();

	LongNumber LNMult(MultCharPointer);			// constructor to hold Long Number based on int

												//PrintLongNumberLR(LNMult);

	LongNumber Result = ArgA * LNMult;
	return Result;
}

LongNumber LongNumberMultiplyBase(LongNumber ArgA, LongNumber ArgB)
{
	// Multiplies two long numbers 
	// includes their base and works in the shared base - must have the same base
	// cout << "Multiplying Numbers \n";

	// get the length of both numbers 
	int ArgALen = ArgA.GetLongNumberLength();
	int ArgBLen = ArgB.GetLongNumberLength();
	int SignA = ArgA.GetLongNumberSign();
	int SignB = ArgB.GetLongNumberSign();
	int BaseA = ArgA.GetLongNumberBase();
	int BaseB = ArgB.GetLongNumberBase();

	// check the bases are the same
	if (BaseA != BaseB)
	{
		// Return zero
		LongNumber Zero(1);
		Zero.SetLongNumber(0, 0);
	}

	// PrintLongNumberLR(ArgA);
	// PrintLongNumberLR(ArgB);

	// cout << "Length Arg A : " << ArgALen << " : Length Arg B : " << ArgBLen << endl;
	// cout << " Sign A : " << SignA << " Sign B : " << SignB << endl;

	// Set length of result
	int iResultLen = ArgALen;
	if (ArgBLen > ArgALen)
	{
		// cout << "Len B greater than A\n";
		iResultLen = ArgBLen;
	}
	// no need to test for them being both the same length 


	// Multiply the two numbers
	int iCarry = 0;
	int iSumUnit = 0;
	int iSum = 0;
	int iCountA = 0;
	int iCountB = 0;
	int iAVal = 0;
	int iBVal = 0;
	int SignRes = SignA * SignB; // Calculate sign of result 
								 // Create One as a Long Number
	LongNumber One(1);
	One.SetLongNumber(1, 0);
	One.SetLongNumberBase(10);
	One.SetLongNumberSign(1);
	// cout << "Sign Res " << SignRes << endl;

	LongNumber LNResult(iResultLen * 2);		// this is the returned value that is built by repeatedly adding the LNResultTemp on each cycle
	LongNumber iSumConv(iResultLen * 2);
	LNResult.SetLongNumberSign(SignRes);
	LNResult.SetLongNumberBase(BaseA);

	// cout << "Multiplying Loop \n";
	for (iCountA = 0; iCountA < iResultLen; iCountA++)
	{

		for (iCountB = 0; iCountB < iResultLen; iCountB++)
		{
			// cout << "Start B loop" << endl;
			int ConstructLen = iResultLen * 2;
			// cout << "Pre LN Constructor" << endl;
			LongNumber LNResultTemp(ConstructLen);
			LNResultTemp.SetLongNumberBase(BaseA);
			// cout << "Pre LN Sign" << endl; 
			LNResult.SetLongNumberSign(SignRes);
			// cout << endl;
			// cout << "iResultLen : " << iResultLen << endl;
			//cout << "iCountA : " << iCountA << endl;
			//cout << "iCountB : " << iCountB << endl;
			if (iCountA < ArgALen)
			{
				iAVal = ArgA[iCountA];
			}
			else
			{
				iAVal = 0;
			}
			if (iCountB < ArgBLen)
			{
				iBVal = ArgB[iCountB];
			}
			else
			{
				iBVal = 0;
			}
			//cout << "AVal : " << iAVal << endl;
			//cout << "BVal : " << iBVal << endl;
			iSum = (iAVal * iBVal);
			iSumConv = LongNumberMultiplyInt(One, iSum);
			// PrintLongNumberLR(iSumConv);
			iSumConv = ConvertBases(iSumConv, BaseA);
			// PrintLongNumberLR(iSumConv);
			//cout << "iSum : " << iSum << endl;
			iSumUnit = iSum % BaseA;
			//cout << "iSumUnit : " << iSumUnit << endl;
			iCarry = (iSum - iSumUnit) / BaseA;
			//cout << "iCarry : " << iCarry << endl;
			LNResultTemp.SetLongNumber(iSumUnit, iCountB + iCountA);
			LNResultTemp.SetLongNumber(iCarry, iCountB + iCountA + 1);
			// PrintLongNumberLR(LNResultTemp);
			LNResult.SetLongNumberBase(BaseA);
			LNResultTemp.SetLongNumberBase(BaseA);
			LNResult = LongNumberAddBase(LNResult, LNResultTemp);		// sign not yet implemented for adding
																		// PrintLongNumberLR(LNResult);
			LNResult = TrimLongNumber(LNResult);
			// PrintLongNumberLR(LNResult);
		}

	}

	LNResult.SetLongNumberSign(SignRes);		// sign not yet implemented for adding

												//LNResult.SetLongNumber(iCarry, iResultLen);

												//PrintLongNumber(LNResult);

	return LNResult;



}

LongNumber operator-(LongNumber ArgA, LongNumber ArgB)
{
	return LongNumberSubtract(ArgA, ArgB);

}

ostream & operator<<(ostream & stream, const LongNumber& ArgA)
{
	PrintLongNumberLRNOENDL(ArgA);
	return stream;

}

int LongNumberCompare(LongNumber ArgA, LongNumber ArgB)
{
	// Compares two long numbers
	// Returns 
	// -1 if ArgA less than Arg B
	// 0 if they are the same
	// +1 if ArgA greater than Arg B

	// Firstly check the signs
	int SignA = ArgA.GetLongNumberSign();
	int SignB = ArgB.GetLongNumberSign();

	if (SignA > SignB)
	{
		// A positive, B negative
		// cout << "A pos, B neg" << endl;
		return 1;
	}

	if (SignA < SignB)
	{
		// A negative, B positive
		// cout << "A neg, B pos" << endl;
		return -1;
	}

	// got here so must have same sign 

	// Check lengths
	// firstly trim
	ArgA = TrimLongNumber(ArgA);
	// PrintLongNumberLR(ArgA);
	ArgB = TrimLongNumber(ArgB);
	int LenA = ArgA.GetLongNumberLength();
	int LenB = ArgB.GetLongNumberLength();

	if (LenA > LenB)
	{
		// A longer than B so must be greater (assumes trimmed) 
		// cout << "A longer than B" << endl;
		return 1;
	}
	if (LenA < LenB)
	{
		// A shorter than B so must be less (assumes trimmed) 
		// cout << "A shorter than B" << endl;
		return -1;
	}

	// got here so have same sign and same length 

	for (int iCount = LenA - 1; iCount >= 0; iCount--)
	{
		int AVal = ArgA[iCount];
		int BVal = ArgB[iCount];
		if (AVal > BVal)
		{
			// A higher than B
			// cout << "A : " << AVal << endl;
			// cout << "B : " << BVal << endl;
			// cout << "A in pos greater than B : iCount " << iCount << endl;
			return 1;
		}
		if (AVal < BVal)
		{
			// A less than B
			// cout << "A : " << AVal << endl;
			// cout << "B : " << BVal << endl;
			// cout << "A in pos less than B : iCount " << iCount << endl;
			return -1;
		}

	}

	// All of the numbers matched so must be the same
	// cout << "End of function so matched" << endl;
	return 0;

}

bool operator==(LongNumber ArgA, LongNumber ArgB)
{
	if (LongNumberCompare(ArgA, ArgB) == 0)
	{
		return true;
	}
	return false;
}

bool operator!=(LongNumber ArgA, LongNumber ArgB)
{
	if (LongNumberCompare(ArgA, ArgB) != 0)
	{
		return true;
	}
	return false;
}

bool operator>(LongNumber ArgA, LongNumber ArgB)
{
	if (LongNumberCompare(ArgA, ArgB) == 1)
	{
		return true;
	}
	return false;
}

bool operator<(LongNumber ArgA, LongNumber ArgB)
{
	if (LongNumberCompare(ArgA, ArgB) == -1)
	{
		return true;
	}
	return false;
}

bool operator>=(LongNumber ArgA, LongNumber ArgB)
{
	if (LongNumberCompare(ArgA, ArgB) == 0)
	{
		return true;
	}
	if (LongNumberCompare(ArgA, ArgB) == 1)
	{
		return true;
	}
	return false;
}

bool operator<=(LongNumber ArgA, LongNumber ArgB)
{
	if (LongNumberCompare(ArgA, ArgB) == -1)
	{
		return true;
	}
	if (LongNumberCompare(ArgA, ArgB) == 0)
	{
		return true;
	}
	return false;

}


LongNumber LongNumberSubtract(LongNumber ArgA, LongNumber ArgB)
{
	// subtracts B from A
	// Assumes A greater than B - needs to be checked by calling routine before calling subtract 
	// Also assumes that both are positive - ie signs are ignored and result is always positive
	// cout << "Subtract"; 

	// get the length of both numbers 
	int iCount;
	int ArgALen = ArgA.GetLongNumberLength();
	int ArgBLen = ArgB.GetLongNumberLength();
	int SignA = ArgA.GetLongNumberSign();
	int SignB = ArgB.GetLongNumberSign();
	int iResultLen = ArgALen;
	// cout << "Length Arg A : " << ArgALen << " : Length Arg B : " << ArgBLen << endl;

	/* This shouldn't happen as A must be greater than or equal to B in length
	if (ArgBLen > ArgALen)
	{
	//cout << "Len B greater than A\n";
	iResultLen = ArgBLen;
	}
	*/
	// no need to test for them being both the same length 

	// Subtract the two numbers
	int iCarry = 0;
	int iSumUnit = 0;
	int iSum = 0;
	int SignRes = 1; // holder until implement subtraction 

	LongNumber LNResult(iResultLen + 1);
	LNResult.SetLongNumberSign(SignRes);
	// cout << "Result Len : " << iResultLen << '\n';

	// cout << "Subtraction Loop \n";
	for (iCount = 0; iCount < iResultLen; iCount++)
	{
		int AVal;
		int BVal;
		if (iCount < ArgALen)
		{
			AVal = ArgA[iCount];
		}
		else
		{
			AVal = 0;
		}

		if (iCount < ArgBLen)
		{
			BVal = ArgB[iCount];
		}
		else
		{
			BVal = 0;
		}

		iSum = (AVal - iCarry) - BVal;
		if (iSum < 0)
		{
			iSumUnit = 10 + iSum;
			iCarry = 1;
		}
		else
		{
			iSumUnit = iSum;
			iCarry = 0;
		}
		LNResult.SetLongNumber(iSumUnit, iCount);
		// cout << "iSum : " << iSum << endl; 
		// cout << "iSumUnit : " << iSumUnit << endl;
		// cout << "iCarry : " << iCarry << endl;
	}

	// Not needed for positive subtraction 
	//LNResult.SetLongNumber(iCarry, iResultLen);

	// PrintLongNumber(LNResult);
	LNResult = TrimLongNumber(LNResult);

	return LNResult;



}

LongNumber LongNumberSubtractBase(LongNumber ArgA, LongNumber ArgB)
{
	// subtracts B from A taking into account their base
	// Assumes A greater than B - needs to be checked by calling routine before calling subtract 
	// Also assumes that both are positive - ie signs are ignored and result is always positive
	// cout << "Subtract"; 

	// get the length of both numbers 
	int iCount;
	int ArgALen = ArgA.GetLongNumberLength();
	int ArgBLen = ArgB.GetLongNumberLength();
	int SignA = ArgA.GetLongNumberSign();
	int SignB = ArgB.GetLongNumberSign();
	int BaseA = ArgA.GetLongNumberBase();
	int BaseB = ArgB.GetLongNumberBase();
	int BaseResult = BaseA;
	int iResultLen = ArgALen;
	// cout << "Length Arg A : " << ArgALen << " : Length Arg B : " << ArgBLen << endl;

	/* This shouldn't happen as A must be greater than or equal to B in length
	if (ArgBLen > ArgALen)
	{
	//cout << "Len B greater than A\n";
	iResultLen = ArgBLen;
	}
	*/
	// no need to test for them being both the same length 

	// Subtract the two numbers
	int iCarry = 0;
	int iSumUnit = 0;
	int iSum = 0;
	int SignRes = 1; // holder until implement subtraction 

	LongNumber LNResult(iResultLen + 1);
	LNResult.SetLongNumberSign(SignRes);
	// cout << "Result Len : " << iResultLen << '\n';

	// cout << "Subtraction Loop \n";
	for (iCount = 0; iCount < iResultLen; iCount++)
	{
		int AVal;
		int BVal;
		if (iCount < ArgALen)
		{
			AVal = ArgA[iCount];
		}
		else
		{
			AVal = 0;
		}

		if (iCount < ArgBLen)
		{
			BVal = ArgB[iCount];
		}
		else
		{
			BVal = 0;
		}

		iSum = (AVal - iCarry) - BVal;
		if (iSum < 0)
		{
			iSumUnit = BaseResult + iSum;
			iCarry = 1;
		}
		else
		{
			iSumUnit = iSum;
			iCarry = 0;
		}
		LNResult.SetLongNumber(iSumUnit, iCount);
		// cout << "iSum : " << iSum << endl; 
		// cout << "iSumUnit : " << iSumUnit << endl;
		// cout << "iCarry : " << iCarry << endl;
	}

	// Not needed for positive subtraction 
	//LNResult.SetLongNumber(iCarry, iResultLen);

	// PrintLongNumberLR(LNResult);
	LNResult = TrimLongNumber(LNResult);

	return LNResult;


}

LongNumber LongNumberSubtractTwosC(LongNumber ArgA, LongNumber ArgB)
{
	// Subtracts ArgB from ArgA using twos complement
	int SignA = ArgA.GetLongNumberSign();
	int SignB = ArgB.GetLongNumberSign();
	// work out what to do with the signs
	// options 
	//			A positive, B positive - take 2sC of B and add				: 10 - 6 = 4
	//			A negative, B positive - add A and B and negate result		: -10 - 6 = -16
	//			A positive, B negative - add A and B						: 10 - -6 = 16
	//			A negative, B positive - take 2sC of A and add				: -10 - -6 = -4

	// Convert A and B to binary 
	// Get length of Args and calculate length of result
	int BaseTo = 2;
	int LenA = ArgA.GetLongNumberLength();
	int LenB = ArgB.GetLongNumberLength();
	int BaseFromA = ArgA.GetLongNumberBase();
	int BaseFromB = ArgB.GetLongNumberBase();
	// cout << "Len A : " << LenA << " Base From : " << BaseFromA << endl;
	// cout << "Len B : " << LenB << " Base From : " << BaseFromB << endl;

	// calculates the length of Result by the formula log b X = log a X / log a b
	// becomes LenA x (log10 BaseFrom / Log10 BaseTo)
	double BaseFromL10A = log10(BaseFromA);
	double BaseFromL10B = log10(BaseFromB);
	double BaseTo10 = log10(BaseTo);
	int LenResultA = (int)(LenA * (BaseFromL10A / BaseTo10));
	int LenResultB = (int)(LenB * (BaseFromL10B / BaseTo10));
	int LenResultBin = 0;
	if (LenResultA > LenResultB)
	{
		LenResultBin = LenResultA;
	}
	else
	{
		LenResultBin = LenResultB;
	}
	LenResultBin += 2;							// add a couple to make sure have room
												// cout << "Len Result A : " << LenResultA << endl; 
												// cout << "Len Result B : " << LenResultB << endl;
												// cout << "Len Result : " << LenResult << endl;

												// construct the holders for the converted 
	LongNumber ArgABin(LenResultBin);
	ArgABin.SetLongNumberBase(2);
	LongNumber ArgBBin(LenResultBin);
	ArgABin.SetLongNumberBase(2);

	// Convert to binary
	ArgA.SetLongNumberSign(1);						// set as negative numbers mix up conversion routine
	ArgABin = ConvertDectoBin(ArgA);
	ArgABin.SetLongNumberBase(2);
	// cout << "A as Bin : ";
	// PrintLongNumberLR(ArgABin);

	// convert B to binary then work out what to do with it 
	ArgB.SetLongNumberSign(1);						// set as negative numbers mix up conversion routine
	ArgBBin = ConvertDectoBin(ArgB);
	ArgABin.SetLongNumberBase(2);
	// cout << "B as Bin : ";
	// PrintLongNumberLR(ArgBBin);

	//			A positive, B positive - take 2sC of B and add				: 10 - 6 = 4
	if ((SignA == 1) && (SignB == 1))
	{
		ArgBBin.SetLongNumberSign(-1);
		ArgBBin = TwosComplement(ArgBBin, LenResultBin);
	}

	//			A negative, B positive - take 2sC of A and B and add		: -10 - 6 = -16
	if ((SignA == -1) && (SignB == 1))
	{
		// A in 2sC
		ArgABin.SetLongNumberSign(-1);
		// PrintLongNumberLR(ArgABin);
		ArgABin = TwosComplement(ArgABin, LenResultBin);
		// cout << "A in 2sC : ";
		// PrintLongNumberLR(ArgABin);

		// B in 2sC
		ArgBBin.SetLongNumberSign(-1);
		// PrintLongNumberLR(ArgBBin);
		ArgBBin = TwosComplement(ArgBBin, LenResultBin);
		// cout << "B in 2sC : ";
		// PrintLongNumberLR(ArgBBin);



	}

	//			A positive, B negative - add A and B						: 10 - -6 = 16
	if ((SignA == 1) && (SignB == -1))
	{
		// no 2sC here 

	}

	//			A negative, B negative - take 2sC of A and add				: -10 - -6 = -4
	if ((SignA == -1) && (SignB == -1))
	{
		// A in 2sC
		ArgABin.SetLongNumberSign(-1);
		// PrintLongNumberLR(ArgABin);
		ArgABin = TwosComplement(ArgABin, LenResultBin);
		// cout << "A in 2sC : ";
		// PrintLongNumberLR(ArgABin);


	}

	// construct the result in binary
	LongNumber LNResultBin(LenResultBin);
	LNResultBin = LongNumberAddBase(ArgABin, ArgBBin);
	LNResultBin.SetLongNumberBase(2);
	// PrintLongNumberLR(LNResultBin);

	// need to drop the MSB
	LNResultBin = ReturnPart(LNResultBin, 0, LenResultBin - 1);
	// PrintLongNumberLR(LNResultBin);

	// calculate if answer is negative
	if (LNResultBin[LenResultBin - 2] == 1)
	{
		// negative
		LNResultBin.SetLongNumberSign(-1);
		LNResultBin = TwosComplement(LNResultBin, LenResultBin - 1);
		//cout << "Reverse 2sC : ";
		//PrintLongNumberLR(LNResultBin);

	}

	// construct the result in BaseA 
	// calculates the length of Result by the formula log b X = log a X / log a b
	// becomes LenResultBin x (log10 2 / Log10 BaseA)
	double LogBaseFromA = log10(BaseFromA);
	int LenResultBaseA = (int)(LenResultBin * (log10(2) / LogBaseFromA)) + 2;
	LongNumber LNResult(LenResultBaseA);

	LNResult = ConvertBintoDec(LNResultBin);
	LNResult.SetLongNumberBase(10);
	LNResult.SetLongNumberSign(LNResultBin.GetLongNumberSign());

	return LNResult;
}

LongNumber operator*(LongNumber ArgA, LongNumber ArgB)
{
	return LongNumberMultiply(ArgA, ArgB);
}

LongNumber operator*(LongNumber ArgA, int mult)
{
	return LongNumberMultiplyInt(ArgA, mult);
}



LongNumber operator+(LongNumber ArgA, LongNumber ArgB)
{
	return LongNumberAdd(ArgA, ArgB);
}


