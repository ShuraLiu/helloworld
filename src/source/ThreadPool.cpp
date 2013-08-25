/*
 * ThreadPool.cpp
 *
 *  Created on: 2013年8月24日
 *      Author: shura
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "ThreadPool.h"
#include "Config.h"
#include <assert.h>

typedef std::vector<pthread_t> Pool;
static pthread_mutex_t taskListMutex_;
static pthread_cond_t not_empty_;
static Pool pool_;
static std::list<Task*> taskList_;

static void* workThread(void* arg)
{
	pthread_t* pid =  (pthread_t* )(arg);
	while(1)
	{
		pthread_mutex_lock(&taskListMutex_);
		while(taskList_.empty())
		{
			pthread_cond_wait(&not_empty_, &taskListMutex_);
		}
		Task* task = taskList_.front();
		taskList_.pop_front();
		std::cout << *pid << " get task" << std::endl;
		pthread_mutex_unlock(&taskListMutex_);
		task->doTask();
	}
	return 0;
}

ThreadPool::ThreadPool()
: maxThreadCount_(0)
{

}

ThreadPool* ThreadPool::s_pThreadPool_ = NULL;
ThreadPool* ThreadPool::getInstance()
{
	if(!s_pThreadPool_)
	{
		s_pThreadPool_ = new ThreadPool();
	}
	return s_pThreadPool_;
}

void ThreadPool::init(int maxThreadCount)
{
	maxThreadCount_ = maxThreadCount;
	pool_.resize(maxThreadCount_);
	Pool::iterator begin = pool_.begin();
	Pool::iterator end = pool_.end();
	Pool::iterator it;
	pthread_mutex_init(&taskListMutex_, NULL);
	pthread_cond_init(&not_empty_, NULL);

	for(it = begin; it !=end; ++it)
	{
		int rec = pthread_create(&(*it), NULL, workThread, &(*it));
		if(0 == rec)
		{
			pthread_detach(*it);
		}
	}
}

void ThreadPool::addTask(Task* task)
{
	pthread_mutex_lock(&taskListMutex_);
	if(taskList_.empty())
	{
		taskList_.push_back(task);
		pthread_mutex_unlock(&taskListMutex_);
		pthread_cond_signal(&not_empty_);
	}
	else
	{
		taskList_.push_back(task);
		pthread_mutex_unlock(&taskListMutex_);
	}
}
