#ifndef _CONFDATA_H_
#define _CONFDATA_H_
#include "Mdef.h"
#include <string>
using namespace std;
class logconf
{
	private:
		INT DEFAULT_LEVEL;
		INT MAX_LINE_LOG;
		LONG LOGFSIZE;
		string LOGPATH;
		string LOGFNAME;
	public:
		logconf& operator=(const logconf& conf);
		friend ostream& operator<<(ostream& out,const logconf& conf);
		friend class parseconf;
		friend class logT;
};
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

#endif
//_CONFDATA_H_
