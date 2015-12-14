#include <time.h>
#include <sys/time.h>
#include <stdio.h>

int main()
{
	struct timeval tv;
	char strTime[32];
	char curtime[32];
	gettimeofday(&tv, NULL);
	struct tm *ptm = localtime(&tv.tv_sec);  //将秒转换成struct tm的形式
	strftime(strTime, 32, "%F %z %a %T", ptm);
	strftime(curtime, sizeof(curtime), "_%y%m%d%H%M%S", ptm);
	printf("%s.%03ld\n",strTime, (long)tv.tv_usec); //输出微秒
	printf("%s\n",curtime);
	return 0;
}
