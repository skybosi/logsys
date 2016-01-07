#include "confdata.h"
#include <iostream>
using namespace std;
logconf::logconf()
{
	DEFAULT_LEVEL = 7;
	MAX_LINE_LOG = 1024;
	DEFAULT_LNUM = 10;
	LOGFSIZE = 10;
	FSUNIT = MB;
	LOGPATH = "./";
	LOGFNAME = "Tlog";
	FULLPATH = LOGPATH + LOGFNAME + LSUFFIX ;
	_default_conf 
		<< "# Welcome to use the log system!(2015.12 v0.2)\n"
		<< "# This the logs system's configure file\n"
		<< "# if you are not set one of the the will set default value\n"
		<< "# There are default value here:\n\n"
		<< "##    //  LOGPATH       = \".\";   \\\\\n"
		<< "##   //   LOGFNAME      = \"Tlog\"; \\\\\n"
		<< "##  //    LOGFSIZE      = 10m;     \\\\\n"
		<< "##  \\\\    MAX_LINE_LOG  = 1024;    //\n"
		<< "##   \\\\   DEFAULT_LNUM  = 10;     //\n"
		<< "##    \\\\  DEFAULT_LEVEL = 7;     //\n\n"
		<< "# This log system Now have set those default important variable\n"
		<< "# This is there means here:\n\n"
		<< "#   LOGFNAME      : the log filename\n"
		<< "#   LOGPATH       : the log save path\n"
		<< "#   MAX_LINE_LOG  : the log message max size\n"
		<< "#   DEFAULT_LEVEL : the log system default level\n"
		<< "#   DEFAULT_LNUM  : the log file's default numbers\n"
		<< "#   LOGFSIZE      : the log file default size(you can chose those unit [b/B(byte),k/K(kb),m/M(M)])\n\n"
		<< "# Contact Me    : skybosi_fxc@163.com / feixinchenOK@gmail.com"
		<< endl;
}

logconf& logconf::operator=(const logconf& conf)
{
	if(this == &conf)
		return *this;
	FSUNIT = conf.FSUNIT;
	LOGFSIZE = conf.LOGFSIZE;
	LOGPATH = conf.LOGPATH;
	LOGFNAME = conf.LOGFNAME;
	FULLPATH = conf.FULLPATH;
	MAX_LINE_LOG = conf.MAX_LINE_LOG;
	DEFAULT_LNUM = conf.DEFAULT_LNUM;
	DEFAULT_LEVEL = conf.DEFAULT_LEVEL;
	return *this;
}
ostream& operator<<(ostream& out,const logconf& conf)
{
	return out 
	 << "FSUNIT        = " << conf.FSUNIT << endl
	 << "LOGFNAME      = " << conf.LOGFNAME << endl
	 << "LOGPATH       = " << conf.LOGPATH << endl
	 << "LOGFSIZE      = " << conf.LOGFSIZE << endl
	 << "FULLPATH      = " << conf.FULLPATH << endl
	 << "MAX_LINE_LOG  = " << conf.MAX_LINE_LOG << endl
	 << "DEFAULT_LNUM  = " << conf.DEFAULT_LNUM << endl
	 << "DEFAULT_LEVEL = " << conf.DEFAULT_LEVEL << endl;
}
