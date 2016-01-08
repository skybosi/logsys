#include "Basethread.h"
#include <unistd.h>
#include <iostream>
using namespace std;

class TestThread : public Basethread
{
	public:
		TestThread(int count) :Basethread(), count_(count)
	{
		cout<<"TestThread ..."<<endl;
	}

		~TestThread()
		{
			cout<<"~TestThread ..."<<endl;
		}

	private:
		int run()
		{
			int i = 0;
			while (count_)
			{
				cout<<"this is a test ..."<<endl;
				i++;
				if(i>5)
					break;
			}
			return 0 ;
		}

		int count_;
};

int main(void)
{
	/*
	 * 	TestThread t(5);
	 * 		t.Start();
	 *
	 * 			t.Join();
	 * 				*/

	TestThread* t2 = new TestThread(5);
//	t2->SetAutoDelete(true);
	t2->start();
	if(t2->getdetachstate())
		sleep(1);
	else
		t2->join();
	delete t2;
	return 0;
}


