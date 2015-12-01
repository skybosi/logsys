#ifndef _LOG_T_H_
#define _LOG_T_H_

#include <iostream>
#include <string>
#include <ctime>
#include <typeinfo>
#include <stdarg.h>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "Mdef.h"
using namespace std;
static string getime();
static string lfmt(va_list st,const char *lformat,...);
template < class T > class logT
{
	private:
		int _loglevel;		//log 的显示最低级别
		int _lognum;		// 当前设置log级别
		ofstream _logfile;
		string _classname;
		string _strlog;
	public:
		logT();
		~logT()
		{
			cout << "logT 去世了" << endl;
			_logfile.close();
		};
		void writeL(int logtype, const char* lformat,...);
		void help();
	private:
		string llev2str();
		// oftream help();
};

template < class T > logT < T >::logT():_loglevel(3)
{
	cout << "logT 出世了" << endl;
	string log_filename;
	log_filename = typeid(T).name();
	log_filename = "./tmp/" + log_filename.substr(1)+".log_1";
	_logfile.open(log_filename.c_str(), ios::out | ios::app | ios::binary);
	if (!_logfile)
	{
		cerr << "open log file error!" << endl;
		exit(1);
	}
	_classname = typeid(T).name();
	_classname = _classname.substr(1);	//去掉类名长度
};

template < class T > void logT < T >::writeL(int logtype, const char* lformat,...)
{
	//T clas;
	_lognum = logtype;
	if (_lognum >= _loglevel)
	{
		_logfile << getime() << BLK;
		_logfile << "[ " << _classname << " ]" << BLK;
		_logfile << llev2str()  << BLK;
		/*	
			char strlog[2048];
			memset(&strlog, 0, sizeof(strlog));
			va_list st;
			va_start(st, lformat);
			vsprintf(strlog, lformat, st);
			va_end(st);
			cout << strlog << endl;
			*/
		va_list st;
		va_start(st, lformat);
		_strlog = lfmt(st,lformat);
		cout << _strlog << endl;
		_logfile << _strlog << endl;
	}

}
template < class T > string logT<T>::llev2str()
{
	string Sloglev;
	switch (_lognum)
	{
		case 0:
			Sloglev = "[ LOG_CORE ]: ";
			break;
		case 1:
			Sloglev = "[ LOG_BAD ]: ";
			break;
		case 2:
			Sloglev = "[ LOG_ERROR ]: ";
			break;
		case 3:
			Sloglev = "[ LOG_WARNING ]: ";
			break;
		case 4:
			Sloglev = "[ LOG_NOTICE ]: ";
			break;
		case 5:
			Sloglev = "[ LOG_INFO ]: ";
			break;
		case 6:
			Sloglev = "[ LOG_DEBUG ]: ";
			break;
		default:
			Sloglev = "[ Unkown loglevel ]: ";
			break;
	}
	return Sloglev;
}

template < class T > void logT < T >::help()
{
	string helpdoc;
	helpdoc = "help of logT!";
	cout << helpdoc << endl;
}

static string getime()
{
	time_t now_time = time(NULL);;
	char curtime[64];
	memset(&curtime, 0, sizeof(curtime));
	strftime(curtime, sizeof(curtime), "%Y-%m-%d %X %a %z", localtime(&now_time));
	return curtime;
}
static string lfmt(va_list st,const char *lformat,...)
{
	char strlog[MAX_LINE_LOG];
	memset(&strlog, 0, sizeof(strlog));
	vsnprintf(strlog,sizeof(strlog)-1, lformat, st);
	va_end(st);
	return strlog;
}


#endif
// _LOG_T_H_ class logT header file
