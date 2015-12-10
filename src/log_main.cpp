#include "log_T.h"
#include <string>
using namespace std;
class test
{
	public:
		test();
		~test()
		{
			if(tmp)
				delete tmp;
		}
		string log(int logtype, const char* lformat,...);
		void show()
		{
			cout << "hahahah:" << endl;
			log(LOG_DEBUG,"debug debug ...%20s %9d","format",LOG_DEBUG);
		}
	public:
		logT<test>* tmp;
};
test::test()
{
	tmp = new logT<test>;
}
string test::log(int logtype, const char* lformat,...)
{
	va_list st;
	va_start(st, lformat);
	tmp->writeL(logtype,st,lformat);
	return "OK";
}
int main(int argc,char** argv)
{
	test a;
	//a.log(LOG_DEBUG,"debug debug ...%20s %9d","format",LOG_DEBUG);
	a.show();
	cout << "Ok !" << endl;
	return 0;
}
