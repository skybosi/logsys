#include <iostream>
#include <stdarg.h>
using namespace std;

string my_vsprintf(const char *format, ...);

int main()
{
   cout << my_vsprintf("%My name is %s and I am %d years old.", "Ben", 24);
  //  cout << buf << endl;
    return 0;
}
string my_vsprintf(const char *format, ...)
{
	 char buf[256];
    va_list st;
    va_start(st, format);
    vsprintf(buf, format, st);
    va_end(st);
   // cout << buf << endl;
    return buf;
}