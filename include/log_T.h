#ifndef _LOG_T_H_
#define _LOG_T_H_

#include <iostream>
#include <string>
#include <sys/time.h>
#include <ctime>
#include <typeinfo>
#include <stdarg.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include "Mdef.h"
#include "parseconf.h"
#include "lmutex.h"
#include "lthread.h"
using namespace std;
class logT
{
	private:
		int _lognum;				// 当前log的级别
		ofstream _logfile;
		string _classname;
		string _strlog;				// 每次log的值
		string _logdoc;				// log的帮助文档，由help()返回
		int _line;					// 当前log所在文件的行号
		string _curlfname;			// current log's name with path
//		friend class lthread;
	private:
		logconf _conf;
		parseconf _pconf;
		lmutex* _logmutex;
		lthread* _checklthread;
	private:
		string lfmt(va_list st, const char *lformat, ...);
		void setlconf();				// set logsys's conf
		string llev2str();
		void relname();
		// oftream help();
	public:
		logT();
		~logT();
		void writeL(int logtype,string classname,const char *lformat, ...);
		string help() const;
		void showall() const;
		string getdoc() const { return _logdoc; }
};

#endif
// _LOG_T_H_ class logT header file