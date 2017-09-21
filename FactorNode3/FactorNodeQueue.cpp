#include "stdafx.h"
#include "FactorNodeQueue.h"
#include "Queue"
#include "thread"
#include "mutex"
#include "condition_variable"
#include "FactorClass.h"
#include "iostream"
#include "fstream"

using namespace std;

const int MaxQueueLen = 5000; 
int FileNodeCount;

// Constructor = default
FactorNodeQueue::FactorNodeQueue() = default;

// Destructor = none
FactorNodeQueue::~FactorNodeQueue()
{
}


FactorNode FactorNodeQueue::Pop()
{
	FactorNode FNReturn;
	unique_lock<mutex> mlock(mutex_);
	while (queue_.empty()) 
	{
		cond_.wait(mlock);
	}
	if (FileNodeCount > 0)
	{
		FNReturn = ReadNodeFromFile();
	}
	else
	{
		FNReturn = queue_.front();
		queue_.pop();
	}

	// Was FactorNode FNReturn = queue_.front();

	return FNReturn;
}

void FactorNodeQueue::Pop(FactorNode & Node)
{
	unique_lock<mutex> mlock(mutex_);
	while (queue_.empty())
	{
		cond_.wait(mlock);
	}
	Node = queue_.front();
	queue_.pop();

}

void FactorNodeQueue::Push(const FactorNode & Node)
{
	const char * FileName = "QueueNode.txt";
	unique_lock<mutex> mlock(mutex_);
	int QS = queue_.size();
	if (QS < MaxQueueLen)
	{
		queue_.push(Node);
	}
	else
	{
		WriteNodeToFile(Node, FileName);
	}
	mlock.unlock();
	cond_.notify_one();

}

void FactorNodeQueue::Push(FactorNode && Node)
{
	unique_lock<mutex> mlock(mutex_);
	queue_.push(move(Node));
	mlock.unlock();
	cond_.notify_one();

}

int FactorNodeQueue::ReturnQueueSize()
{
	return queue_.size();
}

void FactorNodeQueue::WriteNodeToFile(FactorNode Node, const char * FileName)
{
	filebuf QF;
	QF.open(FileName, ios::app);
	ostream QueueFile(&QF);
	LongNumber AValue = Node.GetAValue();
	LongNumber BValue = Node.GetBValue();
	int Level = Node.GetLevel();
	QueueFile << AValue << endl; 
	QueueFile << BValue << endl;
	QueueFile << Level << endl;
	FileNodeCount++;
	QF.close();

}

FactorNode FactorNodeQueue::ReadNodeFromFile()
{
	const char * FileName = "QueueNode.txt";
	const char * FileNameTemp = "QueueNodeTemp.txt";

	ifstream QueueFile(FileName, ios::in);

	// read first value into the return value 
	char InChar[1000];
	QueueFile >> InChar;
	LongNumber AValue(InChar);
	QueueFile >> InChar;
	LongNumber BValue(InChar);
	QueueFile >> InChar;
	int Level = atoi(InChar) ;

	FactorNode FNReturn(Level, AValue, BValue,	false);
	FileNodeCount--;

	// copy the rest into a new file
	ofstream QueueFileTemp(FileNameTemp, ios::app);
	
	int iCountRead = 0;
	while (!QueueFile.eof())
	{
		QueueFile >> InChar;
		QueueFileTemp << InChar << endl;
		// if (iCountRead >= FileNodeCount) { break; }
	}

	QueueFile.close();
	QueueFileTemp.close();
	remove(FileName);
	rename(FileNameTemp, FileName);

	return FNReturn;
}



