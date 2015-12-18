#include <algorithm>
#include "Mdef.h"
#include "filedata.h"
filedata::filedata(string logfpath):_logfpath(logfpath)
{
}
filedata::~filedata()
{
}
void filedata::getlflist(const char *dir,const char *ptfname)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if ((dp = opendir(dir)) == NULL)
	{
		fprintf(stderr, "cannot open directory: %s\n", dir);
		return;
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
			filelist.fullfname_t = filelist.paths + filelist.purefname_t;
			filelist.laccess_t = statbuf.st_atime; 
			filelist.lmodify_t = statbuf.st_mtime; 
			filelist.lstatus_t = statbuf.st_ctime; 
			if (filelist.purefname_t.find(ptfname) == 0)
			{
				_files.push_back(filelist);
			}
		}
	}
	chdir("..");
	closedir(dp);
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
	    return v1.purefname_t > v2.purefname_t; //up sort  
}  
bool filedata::sortbyaccess( const lsfile_t &v1, const lsfile_t &v2)  
{  
	    return v1.laccess_t > v2.laccess_t; //up sort  
}  
bool filedata::sortbymodify( const lsfile_t &v1, const lsfile_t &v2)  
{  
	    return v1.lmodify_t > v2.lmodify_t; //up sort  
}  
bool filedata::sortbystatus( const lsfile_t &v1, const lsfile_t &v2)  
{  
	    return v1.lstatus_t > v2.lstatus_t; //up sort  
}  

int filedata::checkfname()
{
	string purefname;
	size_t pos = _logfpath.rfind("/");
	if (pos != _logfpath.npos)
		purefname = _logfpath.substr(pos + 1);
	purefname = delsuffix(purefname);
	string dir = _logfpath.erase(pos+1);
	cout << "dir: " << dir << endl;
	getlflist(dir.c_str(),purefname.c_str());
	lsfile_t tmp;
	int size = _files.size();
	int delfnum = size - DEFAULT_LNUM;
	if(delfnum > 0)
	{
		cout << "size: " << size << endl;
		std::sort(_files.begin(),_files.end(),sortbymodify); 
		while(delfnum--)
		{
			tmp = _files.at(size-1);
			_delfiles.push_back(tmp);
			_files.pop_back();
			size--;
		}
		deloldfile();
	}
	//cout << "sort by modify time: " << endl;
//	showalll(_files);
	return size;
}

bool filedata::deloldfile()
{
	int delfnum = _delfiles.size();
	for(int i = 0; i < delfnum; i++)
	{
		if (remove(_delfiles[i].fullfname_t.c_str()) == 0)
		{
			printf("%s will be delete\n",_delfiles[i].fullfname_t.c_str());
			sleep(10);
		}
		else
		{
			perror("Remove");
			return false;
		}
	}
	return true;
}
void filedata::showalll(vector < lsfile_t > files) const
{
	int size = files.size();
	cout << "size: " << size << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "path        : " << files[i].paths << endl;
		cout << "purefname_t : " << files[i].purefname_t  << endl;
		cout << "fullfname_t : " << files[i].fullfname_t  << endl;
		cout << "lmodify_t   : " << files[i].lmodify_t << endl;
		cout << "laccess_t   : " << files[i].laccess_t << endl;
		cout << "lstatus_t   : " << files[i].lstatus_t << endl;
	}
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
