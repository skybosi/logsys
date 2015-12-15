#include "log_T.h"
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
			//tmp->writeL(LDEBUG,"debug debug ...%20s %9d","format",LOG_DEBUG);
			wlog(LDEBUG,test,"debug debug ...%20s %9d","format",LOG_DEBUG);
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
	test a;
//	a.tmp->writeL(LDEBUG,test,"debug debug ...%20s %9d","format",LOG_DEBUG);
	a.show();
	cout << "Ok !" << endl;
	return 0;
}
