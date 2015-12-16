#ifndef _LTHREAD_H_
#define _LTHREAD_H_
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>
#include "Basethread.h"
#include "lmutex.h"

using namespace std;
void getlflist(const char *dir, vector < string > &files);
//static string getime();
int checkfname(string logfpath);
class lthread:public Basethread
{
	private:
		ofstream _logfile;
		string _flogpath;		//full of the file's path with name
		long _maxfsize;			//max of the each log file's size
		lmutex* _logfmutex;
	public:
		lthread(string logpath, long maxfsize);
		~lthread()
		{
		//	cout << "log thread will deading " << endl;
			delete _logfmutex;
		}
		int run();
		long getfsize();		
		bool checkffull();
		bool checklogfnum(string logpath);
};

#endif
// lthread.h
