//============================================================================
// Name        : helloworld.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "ThreadPool.h"
#include "Task.h"

using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	ThreadPool* pool = ThreadPool::getInstance();
	pool->init(5);
	while(1)
	{
		pool->addTask(new TestTask());
	}

	return 0;
}
