/*
 * ThreadPool.h
 *
 *  Created on: 2013年8月24日
 *      Author: shura
 */

#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include <pthread.h>
#include <vector>
#include <list>
#include "Task.h"

class ThreadPool
{
public:
	static ThreadPool* getInstance();

private:
	ThreadPool();
	ThreadPool(const ThreadPool&);

	static ThreadPool* s_pThreadPool_;

public:
	virtual ~ThreadPool(){};
	void init(int maxThreadCount);

public:
	void addTask(Task* task);

private:
	int maxThreadCount_;
};


#endif /* THREADPOOL_H_ */
