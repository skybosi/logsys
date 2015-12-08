#include "lthread.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>
#include <vector>

using namespace std;
class lthread : public Basethread
{
	private:
		string _logpath;
		int run();
		long checkfsize();
		bool checklogfnum()
};

lthread::lthread(string logpath):_logpath(logpath)
{

}

int lthread::run()
{

}
//check the log file's size
long checkfsize()
{
	struct stat finfo;
	memset(&finfo, 0, sizeof(finfo));
	stat(_logpath, &info);
	long fsize = info.st_size;
	cout << "log file size: " << fsize << endl;
	return fsize;
}
//check the log file's numbers
bool checklogfnum()
{
	int logfnum = checkfname(_logpath);
	if(logfnum > 10)
		return false;
	return true;
}
void getlflist(const char * dir, vector<string>& files )
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if((dp = opendir(dir)) == NULL) 
	{
		fprintf(stderr,"cannot open directory: %s\n", dir);
		return;
	}
	chdir(dir);
	char filename[1024];
	while((entry = readdir(dp)) != NULL) 
	{
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)) 
		{

			if(strcmp(".",entry->d_name) == 0 ||
					strcmp("..",entry->d_name) == 0)
				continue;
			getlflist(entry->d_name,files);
		}
		else
		{
			sprintf(filename,"%s",entry->d_name);
			files.push_back(filename);	
		}
	}
	chdir("..");
	closedir(dp);
}
int checkfname(string logfpath)
{
	string purefname;
	size_t pos = logfpath.rfind("/");
	if(pos != logfpath.npos)
		purefname = substr(pos + 1);
	size_t len = purefname.size();   
	string dir = logfpath.erase(pos,len+1);
	vector<string> files;
	getlflist(dir.c_str(),files);
	int logfnum = 0;
	int size = files.size();
	for(int i =0;i < size;i++)
	{
		if(files[i].find(purefname.erase(len-4)) != files[i].npos)
		{
			printf("%s \n",files[i].c_str());
			logfnum++;
		}
	}
	return logfnum;
}
#endif
// lthread.h
