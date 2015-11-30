#include <iostream>
#include <stdarg.h>
#include <stdlib.h>
#include <cstdio>
#include <cstring>
using namespace std;
void mp(int tmp,const char *fmt, ...);
void mp2(const char *fmt,  va_list st);
int main()
{
	mp(5,"info info ... %s %d", "format", 5);
	cout << "Ok !" << endl;
}

void mp(int tmp,const char *fmt, ...)
{
//	printf("%d \n",tmp);
	char strlog[2048];
	memset(&strlog, 0, sizeof(strlog));
	va_list st;
	va_start(st,fmt);
	mp2(fmt,st);
	va_end(st);
	cout << strlog << endl;
}

void mp2(const char *fmt, va_list st)
{
//	va_list st;
	//vsprintf(strlog, fmt, st);
	arg = va_arg(fmt,st);
	
//	return strlog;
}
