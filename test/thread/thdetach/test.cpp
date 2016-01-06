#include "Thread.h"
#include <iostream>
using namespace std;
class MultiThread : public Thread
{
	public:

		Thread *th1;
		Thread *th2;

		void Test()
		{
			th1 = new Thread(this);
			th1->setThreadPriority(99);
			th2 = new Thread(this);
			start();
			th1->start();
			th2->start();
			th1->join();
			th2->join();
		}

		void run()
		{
			//Thread->isEquals(th1)
				if (Thread::isEquals(th1))
				{
					int number = 100;
					for (int i = 0; i < 1; i++)
					{
						cout << "this is thread1 number is " << number++;
						cout << " \tpid is " << getpid() << " tid is " << getCurrentThreadID() << " Priority:" << th1->getThreadPriority() << endl;
						sleep(1);
					}
				}else if (Thread::isEquals(th2))
				{
					int number = 200;
					for (int i = 0; i < 1; i++)
					{
						cout << "this is thread2 number is " << number++;
						cout << " \tpid is " << getpid() << " tid is " << getCurrentThreadID() << " Priority:" << th2->getThreadPriority() << endl;
						sleep(1);
					}
				}else if (Thread::isEquals(this))
				{
					int number = 300;
					for (int i = 0; i < 1; i++)
					{
						cout << "this is thread0 number is " << number++;
						cout << " \tpid is " << getpid() << " tid is " << getCurrentThreadID() << " Priority:" << this->getThreadPriority() << endl;
						sleep(1);
					}
				}

		}
};

/*
 * * 
 * */
int main(int argc, char** argv)
{
	bool ret;
	MultiThread *mt;
	mt = new MultiThread();
	mt->Test();
	return (0);
}
