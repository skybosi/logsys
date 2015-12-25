#include "log_T.h"
#include "Mdef.h"
#include <string>
using namespace std;
class test
{
	public:
		test();
		~test()
		{
			if(log)
				delete log;
		}
		void show()
		{
			(*log)(LDEBUG,ALLFMT(test,"debug debug ...%20s %9d"),"format",LOG_DEBUG);
			cout << "Ok !" << endl;
		}
	public:
		logT* log;
};
test::test()
{
	log = new logT("/home/dejian.fei/myspace/git/logsys/etc/logsys.conf");
}
int main(int argc,char** argv)
{
	test a;
	cout << a.log->help();
	int times= 10;
	while(times--)
//	while(1)
	{
		a.show();
	}
	return 0;
}
