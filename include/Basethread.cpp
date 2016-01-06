#include "Basethread.h"

Basethread::Basethread(bool detach):_detach(detach),autoDelete_(false)
{
	cout << "Basethread is coming" << endl;
	if(_detach)
	{
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);	// 线程分离属性
	}
}
Basethread::Basethread():_detach(false),autoDelete_(false)
{
	cout << "Basethread is coming" << endl;
}

bool Basethread::start()
{
	int status = 0;
	if(_detach)
		status = pthread_create(&pth, &attr, runhere, (void *)(this));	// 创建一个线程
	else
		status = pthread_create(&pth, NULL, runhere, (void *)(this));	// 创建一个线程
	if(status != 0)
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
	cout << "come in join..." << endl;
	if(pth)
	{
		cout << "at in join..." << endl;
		pthread_join(pth,NULL);
	}
	cout << "leave in join..." << endl;
}

pthread_t Basethread::gethreadid()
{
	return pth;
}

void Basethread::SetAutoDelete(bool autoDelete)
{
	autoDelete_ = autoDelete;
}

