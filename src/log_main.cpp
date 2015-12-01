#include "log_T.h"
#include <string>
using namespace std;
class test
{
    public:
		test();
	void show()
	{
	    cout << "test show";
	}
};
int main(int argc,char** argv)
{
   logT<test> b;
   b.writeL(LOG_DEBUG,"debug debug ...%20s %9d","format",LOG_DEBUG);
  cout << "Ok !" << endl;
    return 0;
}
