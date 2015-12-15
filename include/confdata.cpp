#include "confdata.h"
#include <iostream>
using namespace std;

logconf& logconf::operator=(const logconf& conf)
{
	DEFAULT_LEVEL = conf.DEFAULT_LEVEL;
	MAX_LINE_LOG = conf.MAX_LINE_LOG;
	LOGFSIZE = conf.MAX_LINE_LOG;
	LOGPATH = conf.LOGPATH;
	LOGFNAME = conf.LOGFNAME;
	return *this;
}
ostream& operator<<(ostream& out,const logconf& conf)
{
	return out 
	 << "DEFAULT_LEVEL : " << conf.DEFAULT_LEVEL << endl
	 << "MAX_LINE_LOG  : " << conf.MAX_LINE_LOG << endl
	 << "LOGPATH       : " << conf.LOGPATH << endl
	 << "LOGFNAME      : " << conf.LOGFNAME << endl
	 << "LOGFSIZE      : " << conf.LOGFSIZE << endl;
}

