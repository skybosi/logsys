#include "log_T.h"
#include <string>

void *plog(void *arg);
class test
{
	public:
		test();
		void show()
		{
			(*log)(LDEBUG,LOGFMT(test,"debug debug ..."));
			cout << "test show";
		}
	public:
		logT* log;
};
test::test()
{
	log = new logT();
}

int main(int argc,char** argv)
{
	if(argc < 2)
	{
		cout << "usage: " << argv[0] << " thread count (eg: 1)" << endl;
		return 0;
	}
	test a;
	int nums = 0;
	int threads = atoi(argv[1]);
	pthread_t pth[threads];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);//线程分离属性
	while(nums < threads)
	{
		if(pthread_create(&pth[nums++],&attr,plog,(void*)&a)!=0)		//创建一个线程
		{
			perror("pthread_create error");
			exit(1);
		}
	}
//	int i = 10000;
	while(1)
	{
		a.show(); 
	}
	return 0;
}
void *plog(void *arg)
{
	test* a = (test*)arg;
//	int i = 10000;
	while(1)
	{
		(*(a->log))(LERROR,LOGFMT(test,"aaaaaaaaa"));
	}
	return (void*)0;
}


