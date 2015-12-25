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
//#include "Mdef.h"
using namespace std;
class lthread:public Basethread
{

	private:
		bool renameflag;
		logconf _conf;
		lmutex* _logfmutex;
		filedata* _filedata;
	private:
		static lthread *_linstance;
		lthread(logconf& conf);
	public:
		static lthread* getlthread(logconf& conf);
		friend class logT;
		~lthread()
		{
			cout << "log thread will deading " << endl;
			if(_linstance)
				delete _linstance;
			delete _logfmutex;
		}
		int run();
		long getfsize(FSU& fsu);		
		bool checkffull();
		bool checklogfnum(string logpath);
};

#endif
// lthread.h
