#ifndef _BASETHREAD_H_
#define _BASETHREAD_H_
#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#define MAXTHREAD 10
using namespace std;
class Basethread
{
  private:
	int _threadnum;
	int _curthreadnum;
	pthread_t pth[MAXTHREAD];
	pthread_attr_t attr;
	static void *runhere(void *args);
  public:
	  Basethread(int threadnum);
	  Basethread()
	{
		_threadnum = 1;
	}
	 ~Basethread()
	{
	  //cout << "Basethread will dead!" << endl;
		pthread_attr_destroy(&attr);
	}
	bool create();
	virtual int run() = 0;
};

Basethread::Basethread(int threadnum):_threadnum(threadnum)
{
	if (_threadnum > MAXTHREAD)
	{
		perror("pthread_create is heavy");
		exit(1);
	}
	//cout << "Basethread is coming" << endl;
	_curthreadnum = 0;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);	// 线程分离属性
	if(!create())
		exit(1);
		
}

bool Basethread::create()
{
	while (_curthreadnum < _threadnum)
	{
		if (pthread_create(&pth[_curthreadnum++], &attr, runhere, (void *)(this)) != 0)	// 创建一个线程
		{
			perror("pthread_create error");
			return false;
		}
	}
	return true;
}

inline void *Basethread::runhere(void *args)
{
	Basethread *th = (Basethread *) args;
	th->run();
	return (void *)0;
}
#endif
// Basethread.h
