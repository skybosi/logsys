#ifndef _LTHREAD_H_
#define _LTHREAD_H_
#include "Basethread.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>

using namespace std;
void getlflist(const char *dir, vector < string > &files);
static string getime(bool chose);
int checkfname(string logfpath);
class lthread:public Basethread
{
  private:
	string _logpath;
	long _maxfsize;
  public:
	  lthread(string logpath, long maxfsize);
	 ~lthread()
	{
		// cout << "log thread will deading " << endl;
	}
	int run();
	long checkfsize();
	bool checklogfnum(string logpath);

};

lthread::lthread(string logpath, long maxfsize):Basethread(1), _logpath(logpath),
_maxfsize(maxfsize)
{
	// cout << "log thread is coming..." << endl;
}

int lthread::run()
{
	long fsize = checkfsize();
	int len = _logpath.size();
	cout << "old parh:" << _logpath << endl;
	string oldpath = _logpath;
	if (fsize > _maxfsize)
	{
		cout << "我来了" << endl;
		string newfname = oldpath.erase(len - 4) + getime(false) + ".log";
		cout << "new path:" << newfname << endl;
		rename(_logpath.c_str(), newfname.c_str());
		cout << "rename ok!" << endl;
		ofstream newlfile;
		newlfile.open(_logpath.c_str());
		if (!newlfile)
		{
			cerr << "open log file error!" << endl;
			exit(1);
		}
		newlfile.close();
	}
	else
	{
		ofstream newlfile;
		newlfile.open(_logpath.c_str());
		if (!newlfile)
		{
			cerr << "open log file error!" << endl;
			exit(1);
		}
		newlfile.close();
	}
	// checklogfnum(_logpath);
	return 0;
}


	// check the log file's size
long lthread::checkfsize()
{
	const char *filename = _logpath.c_str();
	struct stat finfo;
	memset(&finfo, 0, sizeof(finfo));
	stat(filename, &finfo);
	long fsize = finfo.st_size;
	cout << " file size: " << fsize << endl;
	return fsize;
}

// check the log file's numbers
bool lthread::checklogfnum(string logpath)
{
	int logfnum = checkfname(logpath);
	if (logfnum > 10)
		return false;
	return true;
}

void getlflist(const char *dir, vector < string > &files)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if ((dp = opendir(dir)) == NULL)
	{
		fprintf(stderr, "cannot open directory: %s\n", dir);
		return;
	}
	chdir(dir);
	char filename[1024];
	while ((entry = readdir(dp)) != NULL)
	{
		lstat(entry->d_name, &statbuf);
		if (S_ISDIR(statbuf.st_mode))
		{

			if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
				continue;
			getlflist(entry->d_name, files);
		}
		else
		{
			sprintf(filename, "%s", entry->d_name);
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
	if (pos != logfpath.npos)
		purefname = logfpath.substr(pos + 1);
	size_t len = purefname.size();
	cout << "purefname:" << purefname.erase(len - 4) << endl;
	string dir = logfpath.erase(pos, len + 1);
	cout << "log's path: " << dir << endl;
	cout << "======================" << endl;
	vector < string > files;
	getlflist(dir.c_str(), files);
	int logfnum = 0;
	int size = files.size();
	for (int i = 0; i < size; i++)
	{
		// printf("llll:%s \n",files[i].c_str());
		if (files[i].find(purefname) != files[i].npos)
		{
			printf("%s\n", files[i].c_str());
			logfnum++;
		}
	}
	return logfnum;
}

static string getime(bool chose)
{
	time_t now_time = time(NULL);;
	char curtime[64];
	memset(&curtime, 0, sizeof(curtime));
	if (chose)
		strftime(curtime, sizeof(curtime), "%Y-%m-%d %X %a %z", localtime(&now_time));
	else
		strftime(curtime, sizeof(curtime), "_%y%m%d%H%M%S", localtime(&now_time));
	return curtime;
}

#endif
// lthread.h