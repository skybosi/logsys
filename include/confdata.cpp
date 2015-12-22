#include "confdata.h"
#include <iostream>
using namespace std;
logconf::logconf()
{
	DEFAULT_LEVEL = 7;
	MAX_LINE_LOG = 1024;
	DEFAULT_LNUM = 10;
	LOGFSIZE = 83886080;
	LOGPATH = ".";
	LOGFNAME = "test";
	FULLPATH = LOGPATH + LOGFNAME;
}

logconf& logconf::operator=(const logconf& conf)
{
	if(this == &conf)
		return *this;
	DEFAULT_LEVEL = conf.DEFAULT_LEVEL;
	MAX_LINE_LOG = conf.MAX_LINE_LOG;
	DEFAULT_LNUM = conf.DEFAULT_LNUM;
	LOGFSIZE = conf.LOGFSIZE;
	LOGPATH = conf.LOGPATH;
	LOGFNAME = conf.LOGFNAME;
	FULLPATH = conf.FULLPATH;
	return *this;
}
ostream& operator<<(ostream& out,const logconf& conf)
{
	return out 
	 << "DEFAULT_LEVEL : " << conf.DEFAULT_LEVEL << endl
	 << "MAX_LINE_LOG  : " << conf.MAX_LINE_LOG << endl
	 << "DEFAULT_LNUM  : " << conf.DEFAULT_LNUM << endl
	 << "LOGPATH       : " << conf.LOGPATH << endl
	 << "LOGFNAME      : " << conf.LOGFNAME << endl
	 << "FULLPATH      : " << conf.FULLPATH << endl
	 << "LOGFSIZE      : " << conf.LOGFSIZE << endl;
}

