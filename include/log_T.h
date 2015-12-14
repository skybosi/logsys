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
static string getime(bool chose);
// true :for the log ;false: for logfile'name
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
	private:
		logconf _conf;
		parseconf _pconf;
		lmutex* _logmutex;
		lthread* _checklthread;
	private:
		string lfmt(va_list st, const char *lformat, ...);
		void setlconf();				// set logsys's conf
		string llev2str();
		// oftream help();
	public:
		logT();
		~logT()
		{
			//cout << "logT will dead" << endl;
			//if(_logmutex)
			delete _logmutex;
			if(_logfile)
				_logfile.close();
		};
		void writeL(int logtype,string classname,const char *lformat, ...);
		string help() const;
		void showall() const;
		string getdoc() const
		{
			return _logdoc;
		}
};
void logT::setlconf()
{
	parseconf _pconf("./etc/logsys.conf");
	_pconf.parse_conf();
	_conf = _pconf._lconf;		//get configuration 
	string lastpos = _conf.LOGPATH.substr(_conf.LOGPATH.size() - 1);
	if (lastpos != "/")
		_conf.LOGPATH.append("/");
}

logT::logT()
{
	_logmutex = new lmutex(); 
	_logdoc = help();
	setlconf();
	_curlfname = _conf.LOGPATH + _conf.LOGFNAME + ".log";
	showall();
//	cout << "logT come on" << endl;
	_checklthread = new lthread(_curlfname,_conf.LOGFSIZE);
	_checklthread->run();
	_logfile.open(_curlfname.c_str(), ios::out | ios::app | ios::binary);
	if (!_logfile)
	{
		cerr << "open log file error!" << endl;
		exit(1);
	}
}

void logT::writeL(int loghere,string classname,const char *lformat, ...)
{
	_classname = classname;
	_logmutex->setlock();
	_lognum = loghere & 7;		// get logtype
	_line = loghere >> 3;		// get log line
	if (_lognum <= _conf.DEFAULT_LEVEL)
	{
		va_list st;
		va_start(st,lformat);
		_logfile << getime(true) << BLK;
		_logfile << "[ " << _classname << " ]" << BLK;
		_logfile << llev2str() << BLK;
		_logfile << _line << BLK;
		//cout << "line:" << _line << BLK;
		_strlog = lfmt(st, lformat);
		//cout << _strlog << endl;
		_logfile << _strlog << endl;
	}
	_logmutex->setunlock();

}

string logT::llev2str()
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

string logT::help()
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
	struct timeval tv;
	gettimeofday(&tv, NULL);
	struct tm *ptm = localtime(&tv.tv_sec);  //将秒转换成struct tm的形式
	char curtime[64];
	memset(&curtime, 0, sizeof(curtime));
	if (chose)
	{
		strftime(curtime, sizeof(curtime), "%Y-%m-%d %a %z %T", ptm);
		sprintf(curtime, "%s.%03ld", curtime, tv.tv_usec/1000);
	}
	else
		strftime(curtime, sizeof(curtime), "_%y%m%d%H%M%S", ptm);
	return curtime;
}

string logT::lfmt(va_list st, const char *lformat,...)
{
	char strlog[_conf.MAX_LINE_LOG];
	memset(&strlog, 0, sizeof(strlog));
	vsnprintf(strlog, sizeof(strlog) - 1, lformat, st);
	va_end(st);
	return strlog;
}
void logT::showall() const
{
	cout << _conf;
	cout << "_curlfname    : " << _curlfname << endl;
}

#endif
// _LOG_T_H_ class logT header file
