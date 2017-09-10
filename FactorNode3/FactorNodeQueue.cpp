#include "stdafx.h"
#include "FactorNodeQueue.h"
#include "Queue"
#include "thread"
#include "mutex"
#include "condition_variable"
#include "FactorClass.h"
using namespace std;

// Constructor = default
FactorNodeQueue::FactorNodeQueue() = default;

// Destructor = none
FactorNodeQueue::~FactorNodeQueue()
{
}


FactorNode FactorNodeQueue::Pop()
{
	unique_lock<mutex> mlock(mutex_);
	while (queue_.empty()) 
	{
		cond_.wait(mlock);
	}
	FactorNode FNReturn = queue_.front();
	queue_.pop();

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
	unique_lock<mutex> mlock(mutex_);
	queue_.push(Node);
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



