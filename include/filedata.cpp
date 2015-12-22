#include <algorithm>
#include "filedata.h"
filedata::filedata(logconf& conf):_conf(conf),rmflag(false)
{
}
filedata::~filedata()
{
}
int filedata::getlflist(const char *dir,const char *ptfname)
{
	cout << "hhhhhhhhhhhhhh: "<< dir << BLK << ptfname<< endl;
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
			filelist.laccess_t = statbuf.st_atime; 
			filelist.lmodify_t = statbuf.st_mtime; 
			filelist.lstatus_t = statbuf.st_ctime; 
			if ((filelist.purefname_t.find(ptfname) == 0) && 
					 findafile(filelist.purefname_t))
			{
					_files.push_back(filelist);
			}
		}
	}
	chdir("..");
	closedir(dp);
	return _files.size();
}
bool filedata::checkfname()
{
	cout << "enter check file numbers: " << endl;
	cout << _conf;
	string dir = _conf.LOGPATH;
	string patfile = _conf.LOGFNAME + "_";
	int size = getlflist(dir.c_str(),patfile.c_str());
	int delfnum = size - _conf.DEFAULT_LNUM;
	showalll(_files);
	cout << "filedata size: " << size << endl;
	cout << "哈哈哈: " << rmflag << " delfnum :"<< delfnum << endl;
	if(delfnum > 0)
	{
		std::sort(_files.begin(),_files.end(),sortbyfilename); 
		showalll(_files);
		lsfile_t tmp;
		if(rmflag == false)
		{
			while(delfnum--)
			{
				int fpos = _files.size()-1;
				tmp = _files.at(fpos);
				cout << "tmp file:" << tmp.purefname_t << endl;
				_delfiles.push_back(tmp);
				_files.pop_back();
			}
			rmflag = true;
		}
	}
	else
		rmflag = false;
	//std::vector<lsfile_t>().swap(_files);
	//_files.clear();
	return rmflag;
}

bool filedata::deloldfile()
{
	//showalll(_delfiles);
	//sleep(10);
	int delOk = 0;
	int delfnum = _delfiles.size();
	cout << "delfnum :" << delfnum << endl;
	for(int i = 0; i < delfnum; i++)
	{
		if (remove(_delfiles[i].fullfname_t.c_str()) == 0)
		{
			delOk++;
			printf("%s will be delete\n",_delfiles[i].fullfname_t.c_str());
		}
		else
		{
			perror("Remove");
		}
	}
	if(delOk != delfnum)
		rmflag = true;
	else
		rmflag = false;
	//std::vector<lsfile_t>().swap(_delfiles);
	//_delfiles.clear();
	return rmflag;
}

bool filedata::findafile(string& tfile)
{
	if(_files.empty())
	{
		cout << "_files list is 空"<< endl;
		return true;
	}
	cout << "new szie: " << _files.size() << endl;
	vector<lsfile_t>::iterator iter = _files.begin();
	for(;iter != _files.end(); iter++)
	{
//		cout << "_file list:"  << iter->purefname_t << endl;
		if(tfile == iter->purefname_t)
		{
			return false;
		}
	}
	if(iter == _files.end())
	{
		cout << "new tfile1:" <<"[" << tfile << "]"<< endl;
		return true;
	}
}

void filedata::showalll(vector < lsfile_t > files) const
{
	int size = files.size();
	cout << "showalll size: " << size << endl;
	for (int i = 0; i < size; i++)
	{
//		cout << "path        : " << files[i].paths << endl;
		cout << "purefname_t : " << files[i].purefname_t  << endl;
//		cout << "fullfname_t : " << files[i].fullfname_t  << endl;
//		cout << "lmodify_t   : " << files[i].lmodify_t << endl;
//		cout << "laccess_t   : " << files[i].laccess_t << endl;
//		cout << "lstatus_t   : " << files[i].lstatus_t << endl;
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
	return v1.purefname_t > v2.purefname_t; //up sort  
}  
bool filedata::sortbyaccess( const lsfile_t &v1, const lsfile_t &v2)  
{  
	return v1.laccess_t < v2.laccess_t; //up sort  
}  
bool filedata::sortbymodify( const lsfile_t &v1, const lsfile_t &v2)  
{  
	return v1.lmodify_t < v2.lmodify_t; //up sort  
}  
bool filedata::sortbystatus( const lsfile_t &v1, const lsfile_t &v2)  
{  
	return v1.lstatus_t < v2.lstatus_t; //up sort  
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
