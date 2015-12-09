#include "log_T.h"
#include <string>
using namespace std;

class test:public logT < test >
{
  public:
	void show()
	{
		cout << "test show";
	}
};
class temp:public logT < temp >
{
  public:
	void show()
	{
		cout << "temp show";
	}
};
int main(int argc, char **argv)
{
	while(1)
	{
	test a;

	a.writeL(LERROR, "ERROR ERROR ...\t%20s %9d", "format", LOG_ERROR);

	a.writeL(LDEBUG, "debug debug ...\t%20s %9d", "format", LOG_DEBUG);
	
	a.writeL(LERROR, "ERROR ERROR ...\t%20s %9d", "format", LOG_ERROR);

	a.writeL(LWARNING, "WARNING WARNING ...\t%20s %9d", "format", LOG_WARNING);
	
	a.writeL(LDEBUG, "debug debug ...\t%20s %9d", "format", LOG_DEBUG);
	
	a.writeL(LDEBUG, "debug debug ..\t%20s %9d", "format", LOG_DEBUG);
	
	a.writeL(LINFO, "INFO INFO ...\t%20s %9d", "format", LOG_INFO);
	// cout << a.help();
	

	cout << "======================================================" << endl;
	temp b;

	b.writeL(LERROR, "ERROR ERROR ...\t%20s %9d", "format", LOG_ERROR);

	b.writeL(LDEBUG, "debug debug ...\t%20s %9d", "format", LOG_DEBUG);
	
	b.writeL(LERROR, "ERROR ERROR ...\t%20s %9d", "format", LOG_ERROR);

	b.writeL(LWARNING, "WARNING WARNING ...\t%20s %9d", "format", LOG_WARNING);
	
	b.writeL(LDEBUG, "debug debug ...\t%20s %9d", "format", LOG_DEBUG);
	
	b.writeL(LDEBUG, "debug debug ..\t%20s %9d", "format", LOG_DEBUG);
	
	b.writeL(LINFO, "INFO INFO ...\t%20s %9d", "format", LOG_INFO);
	}
	// cout << a.getdoc();
/*
	wlog(test,LERROR, "ERROR ERROR ...\t%20s %9d", "format", LOG_ERROR);

	wlog(test,LDEBUG, "debug debug ...\t%20s %9d", "format", LOG_DEBUG);
	
	wlog(test,LERROR, "ERROR ERROR ...\t%20s %9d", "format", LOG_ERROR);

	wlog(test,LWARNING, "WARNING WARNING ...\t%20s %9d", "format", LOG_WARNING);
	
	wlog(test,LDEBUG, "debug debug ...\t%20s %9d", "format", LOG_DEBUG);
	
	wlog(test,LDEBUG, "debug debug ..\t%20s %9d", "format", LOG_DEBUG);
	
	wlog(test,LINFO, "INFO INFO ...\t%20s %9d", "format", LOG_INFO);

	wlog(temp,LERROR, "ERROR ERROR ...\t%20s %9d", "format", LOG_ERROR);

	wlog(temp,LDEBUG, "debug debug ...\t%20s %9d", "format", LOG_DEBUG);
	
	wlog(temp,LERROR, "ERROR ERROR ...\t%20s %9d", "format", LOG_ERROR);

	wlog(temp,LWARNING, "WARNING WARNING ...\t%20s %9d", "format", LOG_WARNING);
	
	wlog(temp,LDEBUG, "debug debug ...\t%20s %9d", "format", LOG_DEBUG);
	
	wlog(temp,LDEBUG, "debug debug ..\t%20s %9d", "format", LOG_DEBUG);
	
	wlog(temp,LINFO, "INFO INFO ...\t%20s %9d", "format", LOG_INFO);
	// cout << a.getdoc();
	*/
	cout << "Ok !" << endl;
	return 0;
}