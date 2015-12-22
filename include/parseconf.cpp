#include "parseconf.h"

parseconf::parseconf(string path):_path(path)
{
	cout << "confile will open..." << endl;
	_confile.open(_path.c_str());
	if (!_confile)
	{
		cerr << "parseconf open log file error!" << endl;
		exit(1);
	}
}
// parse the configuration file
bool parseconf::parse_conf()
{
	if (!(this->getfkwtab()))
		return false;
	setconf();
	return true;
}

void parseconf::setconf()
{
	set(_lconf.DEFAULT_LEVEL, STR(DEFAULT_LEVEL));
	set(_lconf.MAX_LINE_LOG, STR(MAX_LINE_LOG));
	set(_lconf.DEFAULT_LNUM, STR(DEFAULT_LNUM));
	set(_lconf.LOGPATH, STR(LOGPATH));
	string lastpos = _lconf.LOGPATH.substr(_lconf.LOGPATH.size() - 1);
	if (lastpos != "/")
		_lconf.LOGPATH.append("/");
	set(_lconf.LOGFNAME, STR(LOGFNAME));
	set(_lconf.LOGFSIZE, STR(LOGFSIZE));
	_lconf.FULLPATH = _lconf.LOGPATH + _lconf.LOGFNAME + ".log";
//	cout << _lconf;
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
/*
	 int main()
	 {
	 parseconf test2("./etc/logsys.conf");
	 test2.parse_conf();
	 return 0;
	 }
	 */
