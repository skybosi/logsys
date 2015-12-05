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
#include "Mdef.h"
#include "parseconf.h"
using namespace std;
static string getime();
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
	int _bufsize;
	string lfmt(va_list st, const char *lformat, ...);
  public:
	logT();
	~logT()
	{
		cout << "logT will dead" << endl;
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

template < class T > logT < T >::logT()
{
	parseconf test2("./etc/logsys.conf");
	test2.parse_conf();
	_loglevel = test2.DEFAULT_LEVEL;
	_bufsize = test2.MAX_LINE_LOG;
	_logdoc = help();
	cout << "logT come on" << endl;
	string log_filename;
	log_filename = typeid(T).name();
	log_filename = test2.LOGPATH + log_filename.substr(1) + ".log_1";
	_logfile.open(log_filename.c_str(), ios::out | ios::app | ios::binary);
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
	_lognum = loghere & 7;		// get logtype
	_line = loghere >> 3;		// get log line
	if (_lognum <= _loglevel)
	{
		_logfile << getime() << BLK;
		_logfile << "[ " << _classname << " ]" << BLK;
		_logfile << llev2str() << BLK;
		_logfile << _line << BLK;
		cout << "line:" << _line << BLK;
		/* 
		   char strlog[2048]; memset(&strlog, 0, sizeof(strlog)); va_list st;
		   va_start(st, lformat); vsprintf(strlog, lformat, st); va_end(st);
		   cout << strlog << endl; */
		va_list st;
		va_start(st, lformat);
		_strlog = lfmt(st, lformat);
		cout << _strlog << endl;
		_logfile << _strlog << endl;
	}

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

	 static string getime()
{
	time_t now_time = time(NULL);;
	char curtime[64];
	memset(&curtime, 0, sizeof(curtime));
	strftime(curtime, sizeof(curtime), "%Y-%m-%d %X %a %z", localtime(&now_time));
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