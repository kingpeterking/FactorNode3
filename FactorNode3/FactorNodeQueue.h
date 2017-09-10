// copied from Juan Palacios

#pragma once
#include "Queue"
#include "thread"
#include "mutex"
#include "condition_variable"
#include "FactorClass.h"
using namespace std;

class FactorNodeQueue
{
public:
	// constructor and destructor
	FactorNodeQueue();
	~FactorNodeQueue();

	// Add and remove
	FactorNode Pop();
	void Pop(FactorNode & Node);
	void Push(const FactorNode & Node);
	void Push(FactorNode && Node);

	// Info about the queue
	int ReturnQueueSize();

private:

	queue<FactorNode> queue_;
	mutex mutex_;
	condition_variable cond_;

};

