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

#endif
// Basethread.h
