#include "log_T.h"
#include <string>
using namespace std;
class test :public logT<test>
{
	public:
		void show()
		{
			cout << "test show";
		}
};
int main(int argc,char** argv)
{
	test a;
	a.writeL(LOG_DEBUG,"debug debug ...%20s %9d","format",LOG_DEBUG);
	cout << a.help();
	cout << a.getdoc();
	cout << "Ok !" << endl;
	return 0;
}
