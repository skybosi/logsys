#include "Basethread.h"

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
}

bool Basethread::start()
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
