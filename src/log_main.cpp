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
int main(int argc, char **argv)
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
	// cout << a.getdoc();
	cout << "Ok !" << endl;
	return 0;
}
