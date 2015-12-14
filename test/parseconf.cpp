#ifndef _PARSECONF_H_
#define _PARSECONF_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <ctype.h>
#include <cstdlib>
#include <typeinfo>
#include "Mdef.h"
#include "confdata.h"
using namespace std;
string del_coment(string & soustr, string head, string tail = "", bool way = 1);
bool isblank(const char *str);	// 是否可见字符
string & trim(string & s);
class parseconf
{
  private:
	string _path;				// configuration file's path
	ifstream _confile;			// configuration file's file stream
	strm _kws;					// key-value with map
	logconf _lconf;
	bool set(INT & key, string keyname);
	bool set(LONG & key, string keyname);
	bool set(DOBL & key, string keyname);
	bool set(string & key, string keyname);
  public:
	  parseconf(string path);
	  parseconf()
	{
		_path = "../etc/logsys.conf";
	}
	 ~parseconf()
	{
		cout << "confile will close..." << endl;
		_confile.close();
	}
	bool getfkwtab();
	bool parse_conf();
	int setconf();
};

parseconf::parseconf(string path):_path(path)
{
	cout << "confile will open..." << endl;
	_confile.open(_path.c_str());
	if (!_confile)
	{
		cerr << "open log file error!" << endl;
		exit(1);
	}
}
// parse the configuration file
bool parseconf::parse_conf()
{
	if (!(this->getfkwtab()))
		return false;
	if (this->setconf() <= 0)
		return false;
	return true;
}

int parseconf::setconf()
{
	int flag = 0;
	if (set(_lconf.DEFAULT_LEVEL, STR(DEFAULT_LEVEL)))
		flag |= 1;
	if (set(_lconf.MAX_LINE_LOG, STR(MAX_LINE_LOG)))
		flag |= 2;
	if (set(_lconf.LOGPATH, STR(LOGPATH)))
		flag |= 4;
	if (set(_lconf.LOGFNAME, STR(LOGFNAME)))
		flag |= 8;
	if (set(_lconf.LOGFSIZE, STR(LOGFSIZE)))
		flag |= 16;
	cout << _lconf << endl;
	return flag;
}

// a series of set function for set the configuration 
bool parseconf::set(int &key, string keyname)
{
	strm::iterator pos;
	pos = _kws.find(keyname);
	if (pos != _kws.end())
	{
		key = atol((pos->second).c_str());
		return true;
	}
	else
		return false;
}

bool parseconf::set(long &key, string keyname)
{
	strm::iterator pos;
	pos = _kws.find(keyname);
	if (pos != _kws.end())
	{
		key = atol((pos->second).c_str());
		return true;
	}
	else
		return false;
}

bool parseconf::set(double &key, string keyname)
{
	strm::iterator pos;
	pos = _kws.find(keyname);
	if (pos != _kws.end())
	{
		key = atof((pos->second).c_str());
		return true;
	}
	else
		return false;
}

bool parseconf::set(string & key, string keyname)
{
	strm::iterator pos;
	pos = _kws.find(keyname);
	if (pos != _kws.end())
	{
		key = (pos->second).c_str();
		return true;
	}
	else
		return false;
}


// get key-value table from configuration file
bool parseconf::getfkwtab()
{
	if (!_confile)
		return false;
	string line;
	string key, value;
	while (getline(_confile, line))
	{
		line = del_coment(line, "#");
		if (!isblank(line.c_str()))
		{
			size_t pos = line.find("=");
			key = line.substr(0, pos);
			value = line.substr(pos + 1);
			if (!isblank(key.c_str()))
			{
				_kws.insert(pair < string, string > (trim(key), trim(value)));
	//	 	cout << "key :" << key << "\t\t";
	//		cout << "value:" << value << endl;
			}
		}
	}
	return true;
}



// delete the comment (while way is true)
string del_coment(string & soustr, string head, string tail, bool way)
{
	// cout << "test: " << soustr << endl;
	size_t hpos = soustr.find(head);
	// cout << "hpos: " << hpos << endl;
	if (hpos == soustr.npos)
	{
		if (way)
			return soustr;
		return "";
	}
	size_t tpos = 0;
	if (tail.empty())
		tpos = soustr.size();
	else
		tpos = soustr.find(tail);
	// cout << "tpos: " << tpos << endl;
	size_t len = tpos - hpos + tail.size();
	if (tpos > hpos)
	{
		if (way)				// 去除注释(分段的部分做分行处理)
			soustr.erase(hpos, len);
		else					// 获取注释(包括注释符号)
			soustr = soustr.substr(hpos, len);
	}
	return soustr;
}

// a line that has not visible characters
bool isblank(const char *str)
{
	while (*str)
		if (!isspace(*str++))
			return false;
	return true;
}

string & trim(string & s)
{
	if (s.empty())
		return s;
	string::iterator c;
	// Erase whitespace before the string
	for (c = s.begin(); c != s.end() && iswspace(*c++););
	s.erase(s.begin(), --c);
	// Erase whitespace after the string
	for (c = s.end(); c != s.begin() && iswspace(*--c););
	s.erase(++c, s.end());
	return s;
}

int main()
{
	parseconf test2("./etc/logsys.conf");
	test2.parse_conf();
	return 0;
}
#endif
// parseconf.h _PARSECONF_H_
