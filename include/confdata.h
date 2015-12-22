#ifndef _CONFDATA_H_
#define _CONFDATA_H_
#include "Mdef.h"
using namespace std;
class logconf
{
	private:
		INT DEFAULT_LEVEL;
		INT MAX_LINE_LOG;
		INT DEFAULT_LNUM;
		LONG LOGFSIZE;
		string LOGPATH;
		string LOGFNAME;
		string FULLPATH;
	public:
		logconf();
		logconf& operator=(const logconf& conf);
		friend ostream& operator<<(ostream& out,const logconf& conf);
		friend class parseconf;
		friend class logT;
		friend class filedata;
		friend class lthread;
};

#endif
//_CONFDATA_H_
