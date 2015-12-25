#include "confdata.h"
#include <iostream>
using namespace std;
logconf::logconf()
{
	DEFAULT_LEVEL = 7;
	MAX_LINE_LOG = 1024;
	DEFAULT_LNUM = 10;
	LOGFSIZE = 8;
	FSUNIT = KB;
	LOGPATH = "./";
	LOGFNAME = "test";
	FULLPATH = LOGPATH + LOGFNAME;
}

logconf& logconf::operator=(const logconf& conf)
{
	if(this == &conf)
		return *this;
	FSUNIT = conf.FSUNIT;
	LOGFSIZE = conf.LOGFSIZE;
	LOGPATH = conf.LOGPATH;
	LOGFNAME = conf.LOGFNAME;
	FULLPATH = conf.FULLPATH;
	MAX_LINE_LOG = conf.MAX_LINE_LOG;
	DEFAULT_LNUM = conf.DEFAULT_LNUM;
	DEFAULT_LEVEL = conf.DEFAULT_LEVEL;
	return *this;
}
ostream& operator<<(ostream& out,const logconf& conf)
{
	return out 
	 << "FSUNIT        : " << conf.FSUNIT << endl
	 << "LOGFNAME      : " << conf.LOGFNAME << endl
	 << "LOGPATH       : " << conf.LOGPATH << endl
	 << "LOGFSIZE      : " << conf.LOGFSIZE << endl
	 << "FULLPATH      : " << conf.FULLPATH << endl
	 << "MAX_LINE_LOG  : " << conf.MAX_LINE_LOG << endl
	 << "DEFAULT_LNUM  : " << conf.DEFAULT_LNUM << endl
	 << "DEFAULT_LEVEL : " << conf.DEFAULT_LEVEL << endl;
}
