#include <stdio.h>
//#include<unistd.h>
#include <dirent.h>
#include <iostream>
using namespace std;
int main()
{
	string curpath = "./test/thread";
	char bakbuf[80];
	char absbuf[80];
	int i = 0;
	if(curpath.find(".") >= 0)
		printf("%d 相对路径\n",i);
	else
	printf("绝对路径\n");
	getcwd(bakbuf,sizeof(bakbuf));
	chdir(curpath.c_str());
	getcwd(absbuf,sizeof(absbuf));
	printf("old: %s\nnew: %s\n",bakbuf,absbuf);
}
