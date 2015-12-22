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
#include "confdata.h"
#include "lmutex.h"
#include "filedata.h"
using namespace std;
void getlflist(const char *dir, vector < string > &files);
int checkfname(string logfpath);
class lthread:public Basethread
{

	private:
		bool renameflag;
		logconf _conf;
		lmutex* _logfmutex;
		filedata* _filedata;
	public:
		friend class logT;
		lthread(logconf& conf);
		~lthread()
		{
			cout << "log thread will deading " << endl;
			delete _logfmutex;
		}
		int run();
		long getfsize();		
		bool checkffull();
		bool checklogfnum(string logpath);
};

#endif
// lthread.h
