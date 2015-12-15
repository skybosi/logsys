#ifndef _CONFDATA_H_
#define _CONFDATA_H_
#include "Mdef.h"
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

#endif
//_CONFDATA_H_
