#ifndef _BASETHREAD_H_
#define _BASETHREAD_H_
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include "Mdef.h"
#ifdef _LUNIX
	#include <pthread.h>
#else
	#include <process.h>
#endif
#define MAXTHREAD 10
using namespace std;
class Basethread
{
  private:
	int _threadnum;
	int _curthreadnum;
#ifdef _LUNIX
	pthread_t pth[MAXTHREAD];
	pthread_attr_t attr;
	static void *runhere(void *args);
#else
	unsigned pth[MAXTHREAD];
	//	static unsigned long __stdcall runhere(void *args);
	static unsigned __stdcall runhere(void *args);
	HANDLE	_hThread;
#endif
  public:
	  Basethread(int threadnum);
	  Basethread()
	{
		_threadnum = 1;
	}
	 ~Basethread()
	{
	  //cout << "Basethread will dead!" << endl;
#ifdef _LUNIX
		pthread_attr_destroy(&attr);
#else
		try
		{
			CloseHandle(_hThread);
		}
		catch(...){}
		_hThread = INVALID_HANDLE_VALUE;
#endif
	}
	bool start();
	virtual int run() = 0;
	pthread_t gethreadid();
};

#endif
// Basethread.h
