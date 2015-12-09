#include "../include/lthread.h"
#include <string>
using namespace std;
int main(int argc, char **argv)
{
	lthread test("../log/first.log",4000);
	int i = 10;
	while (i--)
	{
	  //  cout << "!aaaaaass" <<endl;
	}
	test.run();
	return 0;
}
