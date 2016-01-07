#include <algorithm>
#include "filedata.h"
//filedata::filedata(logconf& conf):_conf(conf),rmflag(false)
filedata::filedata(logconf& conf):rmflag(false)
{
	_conf = conf;
	cout << "filedata is comming!" << endl;
}
filedata::~filedata()
{
	cout << "filedata is will dead!" << endl;
}
int filedata::getlflist(const char *dir,const char *ptfname)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if ((dp = opendir(dir)) == NULL)
	{
		fprintf(stderr, "cannot open directory: %s\n", dir);
		return -1; //is a file
	}
	chdir(dir);
	lsfile_t filelist;
	while ((entry = readdir(dp)) != NULL)
	{
		lstat(entry->d_name, &statbuf);
		if (S_ISDIR(statbuf.st_mode))
		{
			if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
				continue;
			getlflist(entry->d_name,ptfname);
		}
		else
		{
			filelist.paths = dir;
			filelist.purefname_t = entry->d_name;
			filelist.fullfname_t = filelist.paths + 
				filelist.purefname_t;
			if ( 0 == filelist.purefname_t.find(ptfname) )
			{
				_files.push_back(filelist);
			}
		}
	}
	chdir("..");
	closedir(dp);
	return _files.size();
}
//init the deque of a log file list
bool filedata::init_files()
{
	cout << "enter init flies list: " << endl;
	string dir = _conf.LOGPATH;
	string patfile = _conf.LOGFNAME + "_";
	int size = getlflist(dir.c_str(),patfile.c_str()); // 不包含 _conf.LOGFNAME的log文件
	showalll(_files);
	std::sort(_files.begin(),_files.end(),sortbyfilename);//保证初始化file队列的文件名是有序的（升序）
	showalll(_files);
	int delfnum = size - _conf.DEFAULT_LNUM;
	if( delfnum > 0 )
	{
		while(delfnum--)
			_files.pop_front();
	}
	cout << "leave init flies list: " << endl;
}
bool filedata::checkfname()
{
	cout << "enter check file numbers: " << endl;
	int delfnum = _files.size() - _conf.DEFAULT_LNUM;
	cout << "list size: " << _files.size() <<" delfnum: "  << delfnum << endl;
	showalll(_files);
	if( delfnum > 0 )
	{
		while(delfnum--)
		{
			lsfile_t tmp = _files.front();
			if (remove(tmp.fullfname_t.c_str()) == 0)
			{
				printf("%s will be delete\n",tmp.fullfname_t.c_str());
			}
			else
			{
				perror("Remove");
			}
			_files.pop_front();
		}
		rmflag = true;
	}
	else
		rmflag = false;
	cout << "leave check file numbers: " << endl;
	return rmflag;
}
bool filedata::addnewfile(lsfile_t& newlogf)
{
	if(& newlogf)
	{
		_files.push_back(newlogf);
		cout << newlogf.fullfname_t << "enter the list!" << endl;
		return true;
	}
	else
	{
		return false;
	}
}
void filedata::showalll(deque < lsfile_t > files) const
{
	int size = files.size();
	cout << "showalll size: " << size << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "path        : " << files[i].paths << endl;
		cout << "purefname_t : " << files[i].purefname_t  << endl;
		cout << "fullfname_t : " << files[i].fullfname_t  << endl;
	}
}

string & filedata::delsuffix(string & filepath)
{
	if (filepath.empty())
		return filepath;
	size_t pos = filepath.rfind(".");
	if (pos != filepath.npos)
	{
		// cout << "last point pos: " << pos << endl;
		filepath.erase(pos);
	}
	return filepath;
}

bool filedata::sortbyfilename( const lsfile_t &v1, const lsfile_t &v2)  
{  
	return v1.purefname_t < v2.purefname_t; //up sort
}  
/*
	 int main()
	 {
	 string path = "./log/first.log";
	 int lognum = 0;
	 lognum = checkfname(path);
	 cout << "======================" << endl;
	 cout << "lognum: " << lognum << endl;
	 return 0;
	 }
	 */
