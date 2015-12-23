#include "log_T.h"

static string getime(bool chose);
// true :for the log ;false: for logfile'name

logT::logT()
{
	cout << "logT come on" << endl;
	_logdoc = help();
	//_logmutex = new lmutex();
	setlconf();
	_curlfname = _conf.FULLPATH;
	_checklthread = new lthread(_conf);
	_checklthread->start();
	//_logfile.open(_curlfname.c_str(), ios::out | ios::app | ios::binary);
	_logfile.open( _conf.FULLPATH.c_str(), ios::out | ios::app | ios::binary);
	if (!_logfile)
	{
		cerr << "logT: open log file error!" << endl;
		exit(1);
	}
	// showall();
}

logT::~logT()
{
	cout << "logT will dead" << endl;
	// if(_logmutex)
	//	delete _logmutex;
	delete _checklthread;
	if (_logfile)
	{
		cout << "log file will close...." << endl;
		_logfile.close();
	}
}

void logT::setlconf()
{
	// parseconf _pconf("/home/dejian/myspace/git/logsys/etc/logsys.conf");
	parseconf _pconf("/home/dejian.fei/myspace/git/logsys/etc/logsys.conf");
	//parseconf _pconf("../etc/logsys.conf");
	_pconf.parse_conf();
	_conf = _pconf._lconf;		// get configuration 
}

bool logT::relname()
{
	_logfile.close();
	int len = _curlfname.size();
	string oldpath = _curlfname;
	string newfname = oldpath.erase(len - 4) + getime(false) + ".log";
	if (rename(_curlfname.c_str(), newfname.c_str()) == 0)
	{
		printf("Renamed %s to %s\n",_curlfname.c_str(), newfname.c_str());
//		usleep(10);
		_logfile.open(_curlfname.c_str(), ios::out | ios::app | ios::binary);
		if (!_logfile)
		{
			cerr << "relname: open log file error!" << endl;
			exit(1);
		}
		return true;
	}
	else
	{
		perror("rename");
		return false;
	}
}

void logT::writeL(int loghere, string classname, const char *lformat, ...)
{
	//_logmutex->setlock();
	_checklthread->_logfmutex->setlock();
	if(_checklthread->renameflag == true)
	{
		if(relname())
		{
			_checklthread->renameflag = false;
		}
	}
	_classname = classname;
	_lognum = loghere & 7;		// get logtype
	_line = loghere >> 3;		// get log line
	if (_lognum <= _conf.DEFAULT_LEVEL)
	{
		va_list st;
		va_start(st, lformat);
		_logfile << getime(true) << BLK;
		_logfile << "[ " << _classname << " ]" << BLK;
		_logfile << llev2str() << BLK;
		_logfile << _line << BLK;
		_strlog = lfmt(st, lformat);
		_logfile << _strlog << endl;

		cout << "line:" << _line << BLK;
		cout << _strlog << endl;
	}
	//_logmutex->setunlock();
	_checklthread->_logfmutex->setunlock();

}
void logT::operator()(int loghere,const char *lformat,...)
{
	_checklthread->_logfmutex->setlock();
	if(_checklthread->renameflag == true)
	{
		if(relname())
		{
			_checklthread->renameflag = false;
		}
	}
	_lognum = loghere & 7;		// get logtype
	_line = loghere >> 3;		// get log line
	if (_lognum <= _conf.DEFAULT_LEVEL)
	{
		_logfile << getime(true) << BLK;
		_logfile << llev2str() << BLK;
	//	_logfile << _line << BLK;
		va_list st;
		va_start(st, lformat);
		_strlog = lfmt(st, lformat);
		_logfile << _strlog << endl;

		cout << "line:" << _line << BLK;
		cout << _strlog << endl;
	}
	//_logmutex->setunlock();
	_checklthread->_logfmutex->setunlock();
}

string logT::llev2str()
{
	string Sloglev;
	switch (_lognum)
	{
		case 0:
			Sloglev = "[   LOG_CORE  ]:!";//震惊 Shocked
			break;
		case 1:
			Sloglev = "[   LOG_BAD   ]:[";//严肃 seriously
			break;
		case 2:
			Sloglev = "[  LOG_ERROR  ]:(";//沮丧 depressed
			break;
		case 3:
			Sloglev = "[ LOG_WARNING ]:|";//无语 speechless
			break;
		case 4:
			Sloglev = "[  LOG_NOTICE ]:o";//了解 know
			break;
		case 5:
			Sloglev = "[   LOG_INFO  ]:)";//乐观 optimistic
			break;
		case 6:
			Sloglev = "[  LOG_DEBUG  ]:~";//无视 ignore
			break;
		default:
			Sloglev = "[   Unkown    ]:?";//疑问 questions
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
	struct tm *ptm = localtime(&tv.tv_sec);	// 将秒转换成struct
	// tm的形式
	char curtime[64];
	memset(&curtime, 0, sizeof(curtime));
	if (chose)
	{
		strftime(curtime, sizeof(curtime), "%y-%m-%d %a %z %T", ptm);
		sprintf(curtime, "%s.%03ld", curtime, tv.tv_usec / 1000);
	}
	else
	{
		strftime(curtime, sizeof(curtime), "_%y%m%d%H%M%S", ptm);
		sprintf(curtime, "%s%03ld", curtime, tv.tv_usec / 1000);
	}
	return curtime;
}

string logT::lfmt(va_list st, const char *lformat, ...)
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
