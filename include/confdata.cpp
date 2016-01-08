#include "confdata.h"
#include <iostream>
using namespace std;
string get_unit(FSU funit);
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
		<< "# About the log's format type: \n"
		<< "#   log of format (F:file M:method L:line T:thread) \n"
		<< "#   like xxxFMT type,there are here: \n"
    << "#    ALLFMT(_C, _X)	:show all msg in the log tip;\n"
		<< "#    MLTFMT(_C, _X) :show methed's name,log's lines and thread id msg;\n"
		<< "#    MLFMT(_C, _X)  :show methed's name,log's lines msg;\n"
		<< "#    LTFMT(_C, _X)  :show log's lines and thread id msg;\n"
		<< "#    LFMT(_C, _X)   :show log's lines msg only;\n"
		<< "#    TFMT(_C, _X)   :show thread id msg omly.\n"
		<< "#  NOTEs :\n"
		<< "#    _C : Is the class name that you print logs;\n"
		<< "#    _X : You want print massage ,just like printf funtion's format !\n"
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
	 << "LOGFSIZE      = " << conf.LOGFSIZE << get_unit(conf.FSUNIT) << endl
	 << "FULLPATH      = " << conf.FULLPATH << endl
	 << "MAX_LINE_LOG  = " << conf.MAX_LINE_LOG << endl
	 << "DEFAULT_LNUM  = " << conf.DEFAULT_LNUM << endl
	 << "DEFAULT_LEVEL = " << conf.DEFAULT_LEVEL << endl;
}
string get_unit(FSU funit)
{
	string sunit;
	switch(funit)
	{
	case BYTE:
		sunit = " BYTE";
		break;
	case KB:
		sunit = " KB";
		break;
	case MB:
		sunit = " MB";
		break;
	default:
		sunit = " MB";
		break;
	}
	return sunit;
}
