#include "Basethread.h"

Basethread::Basethread():autoDelete_(false)
{
	cout << "Basethread is coming" << endl;
//	pthread_attr_init(&attr);
//	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);	// 线程分离属性
}

bool Basethread::start()
{
	//if (pthread_create(&pth, &attr, runhere, (void *)(this)) != 0)	// 创建一个线程
	if (pthread_create(&pth, NULL, runhere, (void *)(this)) != 0)	// 创建一个线程
	{
		perror("pthread_create error");
		return false;
	}
	return true;
}

inline void *Basethread::runhere(void *args)
{
	Basethread *th = (Basethread *) args;
	th->run();
	if(th->autoDelete_)
		delete th;
	return (void *)0;
}
void Basethread::join()
{
	if(pth)
		pthread_join(pth,NULL);
}

pthread_t Basethread::gethreadid()
{
	return pth;
}

void Basethread::SetAutoDelete(bool autoDelete)
{
	autoDelete_ = autoDelete;
}

