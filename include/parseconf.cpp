#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <ctype.h>
using namespace std;

typedef	vector<std::string> strv;
typedef		map<std::string,std::string> strm;
bool isblank(const char *str);//是否可见字符
class parseconf
{
	private:
		string 		_path;		//configuration file's path
		ifstream 	_confile;	//configuration file's file stream	
		strv		_kwtab;		//key-value with vector
		strm		_kws;		//key-value with map
	public:
		parseconf(string path);
		parseconf(){}
		~parseconf()
		{
			// cout << "confile will close..." << endl;
			_confile.close();
		}
		string 	del_coment(string soustr,string head, string tail = "",bool way = 1);
		bool 	getfkwtab();
		string 	getkwtab();
		strm 	getkw();
		bool 	parse_conf();
};

parseconf::parseconf(string path):_path(path)
{
	//cout << "confile will open..." << endl;
	_confile.open(_path.c_str());
}

//delete the comment (while way is true)
string parseconf::del_coment(string soustr,string head, string tail,bool way)
{
	//	cout << "test: " << soustr << endl;
	size_t hpos = soustr.find(head);
	//	cout << "hpos: " << hpos << endl;
	if (hpos == soustr.npos)
	{
		if(way)
			return soustr;
		return "";
	}
	size_t tpos = 0;
	if (tail.empty())
		tpos = soustr.size();
	else
		tpos = soustr.find(tail);
	//	cout << "tpos: " << tpos << endl;
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
//parse the configuration file
bool parseconf::parse_conf()
{
	if(!(this->getfkwtab()))
		return false;
//	cout << this->getkwtab();
	if(this->getkw().empty())
		return false;
	return true;
}
//set key-value into strm(map) from strv(vector)
strm parseconf::getkw()
{
	string each;
	strm kw;
	string key,value;
	size_t len = _kwtab.size();
	for(size_t i =0; i < len; i++) 
	{
		 each = _kwtab[i];
		 size_t pos = each.find("=");
		 key = each.substr(0,pos);
		 value = each.substr(pos+1);
		 if(!isblank(key.c_str()))
		 {
			 cout << "key  :" << key << "\t";
			 cout << "value:" << value << endl;
			 kw.insert(pair<string,string>(key,value)); 
		 }
	}
	_kws = kw;
	return kw;	
}
//get key-value table from configuration file
bool parseconf::getfkwtab()
{
	if(!_confile)
		return false;
	string line;
	while(getline(_confile,line))
	{
		line = del_coment(line,"#");	
		if(!isblank(line.c_str()))
		{
			_kwtab.push_back(line);
		}
	}
	return true;
}
//get the kwtab from kwtab vector (_kwtab)
string parseconf::getkwtab()
{
	string each;
	ostringstream kwtab;  
	size_t len = _kwtab.size();
	for(size_t i =0; i < len; i++) 
	{
		 each = _kwtab[i];
		 kwtab << each << endl;
	}
	return kwtab.str();
}
//a line that has not visible characters
bool isblank(const char *str)
{
	while (*str)
		if (!isspace(*str++))
			return false;
	return true;
}
int main()
{
	parseconf test2("../etc/sample.conf");
	test2.parse_conf();
	return 0;
}
