#include "log_T.h"
using namespace std;
class test
{
    public:
	void show()
	{
	    cout << "test show";
	}
};
int main(int argc,char** argv)
{
   logT<test> b;
   b.writeL(LOG_DEBUG,"info info ... %s %d","format",LOG_DEBUG);
  cout << "Ok !" << endl;
    return 0;
}
