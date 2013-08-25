/*
 * Task.h
 *
 *  Created on: 2013年8月24日
 *      Author: shura
 */

#ifndef TASK_H_
#define TASK_H_

#include <iostream>

class Task
{
public:
	virtual ~Task(){};

	virtual void doTask() = 0;
};

class TestTask: public Task
{
public:
	virtual ~TestTask(){};
	virtual void doTask(){std::cout << "do test task" << std::endl;};
};

#endif /* TASK_H_ */
