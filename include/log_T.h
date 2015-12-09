#ifndef _LOG_T_H_
#define _LOG_T_H_

#include <iostream>
#include <string>
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
static string getime(bool chose);
// true :for the log ;false: for logfile'name
template < class T > class logT
{
	private:
		int _loglevel;				// log的最低级别 
		int _lognum;				// 当前log的级别
		ofstream _logfile;
		string _classname;
		string _strlog;				// 每次log的值
		string _logdoc;				// log的帮助文档，由help()返回
		int _line;					// 当前log所在文件的行号
		int _bufsize;				// log line's size
		string _logpath;			// the log's path (a directory)
		string _logfname;			// log's name
		long _logfsize;				// log file's maxsize;
		string _curlfname;			// current log's name with
		// path
		long getfsize(const char *ffilename);
		string lfmt(va_list st, const char *lformat, ...);
		long setlconf();				// set logsys's conf
		lmutex* _logmutex;
		lthread* _checklthread;
	public:
		logT();
		~logT()
		{
			cout << "logT will dead" << endl;
	//		if(_logmutex)
				delete _logmutex;
			if(_logfile)
				_logfile.close();
		};
		void writeL(int logtype, const char *lformat, ...);
		string help() const;
		string getdoc() const
		{
			return _logdoc;
		}
		// void SETDEFLEV(int loglev){ return DEFAULT_LEVEL = loglev; }
	private:
		string llev2str();
		// oftream help();
};
template < class T > long logT < T >::setlconf()
{
	long flag = 0;
	parseconf test2("./etc/logsys.conf");
	test2.parse_conf();
	_loglevel = test2.DEFAULT_LEVEL;
	flag |= 1;
	_bufsize = test2.MAX_LINE_LOG;
	flag |= 2;
	_logpath = test2.LOGPATH;
	string lastpos = _logpath.substr(_logpath.size() - 1);
	if (lastpos != "/")
		_logpath.append("/");
	flag |= 4;
	_logfname = test2.LOGFNAME;
	flag |= 8;
	_logfsize = test2.LOGFSIZE;
	flag |= 16;
	return flag;
}

template < class T > long logT < T >::getfsize(const char *ffilename)
{
	struct stat info;
	memset(&info, 0, sizeof(info));
	stat(ffilename, &info);
	long fsize = info.st_size;
	cout << "log file size: " << fsize << endl;
	return fsize;
}

template < class T > logT < T >::logT()
{
	_logmutex = new lmutex(); 
	setlconf();
	_logdoc = help();
	cout << "logT come on" << endl;
	_curlfname = _logpath + _logfname + ".log";
	cout << "_curlfname:" << _curlfname << endl;
	_checklthread = new lthread(_curlfname,_logfsize);
	_checklthread->run();
	/*if (getfsize(_curlfname.c_str()) > _logfsize)
	{
		string newfname = _logpath + _logfname + getime(false) + ".log";
		rename(_curlfname.c_str(), newfname.c_str());
	}*/
	_logfile.open(_curlfname.c_str(), ios::out | ios::app | ios::binary);
	if (!_logfile)
	{
		cerr << "open log file error!" << endl;
		exit(1);
	}
	_classname = typeid(T).name();
	_classname = _classname.substr(1);	// 去掉类名长度
};

template < class T > void logT < T >::writeL(int loghere, const char *lformat, ...)
{
	// T clas;
	_logmutex->setlock();
	_lognum = loghere & 7;		// get logtype
	_line = loghere >> 3;		// get log line
	if (_lognum <= _loglevel)
	{
		_logfile << getime(true) << BLK;
		_logfile << "[ " << _classname << " ]" << BLK;
		_logfile << llev2str() << BLK;
		_logfile << _line << BLK;
		//cout << "line:" << _line << BLK;
		/* 
		   char strlog[2048]; memset(&strlog, 0, sizeof(strlog)); va_list st;
		   va_start(st, lformat); vsprintf(strlog, lformat, st); va_end(st);
		   cout << strlog << endl; */
		va_list st;
		va_start(st, lformat);
		_strlog = lfmt(st, lformat);
	//	cout << _strlog << endl;
		_logfile << _strlog << endl;
	}
	_logmutex->setunlock();

}

template < class T > string logT < T >::llev2str()
{
	string Sloglev;
	switch (_lognum)
	{
		case 0:
			Sloglev = "[   LOG_CORE  ]: ";
			break;
		case 1:
			Sloglev = "[   LOG_BAD   ]: ";
			break;
		case 2:
			Sloglev = "[  LOG_ERROR  ]: ";
			break;
		case 3:
			Sloglev = "[ LOG_WARNING ]: ";
			break;
		case 4:
			Sloglev = "[  LOG_NOTICE ]: ";
			break;
		case 5:
			Sloglev = "[   LOG_INFO  ]: ";
			break;
		case 6:
			Sloglev = "[  LOG_DEBUG  ]: ";
			break;
		default:
			Sloglev = "[   Unkown    ]: ";
			break;
	}
	return Sloglev;
}

template < class T > string logT < T >::help()
	const
{
	ostringstream helpdoc;
	helpdoc
		<< "Welcome to use the log system!(2015.12 v0.2)\n"
		<< "There are some methed(function) :\n"
		<< " ● writeL(int logtype,const char* lfmt,...):\n"
		<< "\t- logtype :The log'type that you want set\n"
		<< "\t- lfmt : A list of argv, just like printf()\n"
		<< " ● help() : You can get detail infomation of the log system\n"
		<< " ● help(string funs)\n"
		<< "\t- funs :The funtion(method) how to use of one that you want to know\n"
		<< "There are some variable(parameter) :\n"
		<< " - int _loglevel :\t The log lowest log level\n"
		<< " - int _lognum :\t The log level you printf at one time you set\n"
		<< " - ofstream _logfile :\t The logfile'path\n"
		<< " - string _strlog :\t The log you printf at one time you set\n"
		<< " - string _logdoc :\t The log system'help doc.\n" << endl;
	return helpdoc.str();
}

static string getime(bool chose)
{
	time_t now_time = time(NULL);;
	char curtime[64];
	memset(&curtime, 0, sizeof(curtime));
	if (chose)
		strftime(curtime, sizeof(curtime), "%Y-%m-%d %X %a %z", localtime(&now_time));
	else
		strftime(curtime, sizeof(curtime), "_%y%m%d%H%M%S", localtime(&now_time));
	return curtime;
}

template < class T > string logT < T >::lfmt(va_list st, const char *lformat,...)
{
	char strlog[_bufsize];
	memset(&strlog, 0, sizeof(strlog));
	vsnprintf(strlog, sizeof(strlog) - 1, lformat, st);
	va_end(st);
	return strlog;
}

#endif
// _LOG_T_H_ class logT header file
