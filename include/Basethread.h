#ifndef _BASETHREAD_H_
#define _BASETHREAD_H_
#include <pthread.h>
#include <iostream>
class Basethread
{
	private:
		int _threadnum;
		int _curthreadnum;
		pthread_t pth[threads];
		pthread_attr_t attr;
		static void* runhere(void *args);

	public:
		Basethread();
		~Basethread()
		{
			pthread_attr_destroy(&attr);
		}
		bool create();
		virtual int run() = 0;
};

Basethread::Basethread(int threadnum):_threadnum(threadnum)
{
	_curthreadnum = 0;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);	// 线程分离属性
	create();
}

bool Basethread::create()
{
	while(_curthreadnum < _threadnum)
	{
		if(pthread_create(&pth[_curthreadnum++],&attr,runhere,(void*)this) != 0)		//创建一个线程
		{
			perror("pthread_create error");
			exit(1);
		}
	}
}
static void* Basethread::runhere(void* args)
{
	Basethread *th  = (Basethread*)args;
	th->run();
}
#endif
// Basethread.h
