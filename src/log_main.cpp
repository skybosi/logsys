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
	private:
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
	a.log(LOG_DEBUG,"debug debug ...%20s %9d","format",LOG_DEBUG);
	cout << "Ok !" << endl;
	return 0;
}
