#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>
#include <vector>
#include <algorithm>
#define DEFAULT_LNUM 5
using namespace std;
typedef struct lsfile
{
	string paths;
	string purefname_t;
	string fullfname_t;
	time_t lmodify_t;
	time_t laccess_t;
	time_t lstatus_t;
}lsfile_t;

void getlflist(const char *dir,const char *ptfname,vector < lsfile_t > &files)
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
			getlflist(entry->d_name,ptfname,files);
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
//				cout << "file: " << filelist.purefname_t << "\t";
//				printf("modify: %d\n",filelist.lmodify_t);
				files.push_back(filelist);
			}
		}
	}
	chdir("..");
	closedir(dp);
}

string & delsuffix(string & filepath)
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

bool sortbypurefname_t( const lsfile_t &v1, const lsfile_t &v2)  
{  
	    return v1.purefname_t > v2.purefname_t; //up sort  
}  
bool sortbyaccess( const lsfile_t &v1, const lsfile_t &v2)  
{  
	    return v1.laccess_t > v2.laccess_t; //up sort  
}  
bool sortbymodify( const lsfile_t &v1, const lsfile_t &v2)  
{  
	    return v1.lmodify_t > v2.lmodify_t; //up sort  
}  
bool sortbystatus( const lsfile_t &v1, const lsfile_t &v2)  
{  
	    return v1.lstatus_t > v2.lstatus_t; //up sort  
}  
void showalll(vector < lsfile_t > files)
{
	int size = files.size();
	for(int i =0;i < size; i++)
	{
		cout << "purefname_t : " << files[i].purefname_t  << endl;
		cout << "lmodify_t: " << files[i].lmodify_t << endl;
		cout << "laccess_t: " << files[i].laccess_t << endl;
		cout << "lstatus_t: " << files[i].lstatus_t << endl;
	}
}

int checkfname(string logfpath)
{
	string purefname;
	size_t pos = logfpath.rfind("/");
	if (pos != logfpath.npos)
		purefname = logfpath.substr(pos + 1);
	purefname = delsuffix(purefname);
	string dir = logfpath.erase(pos+1);
	cout << "dir: " << dir << endl;
	vector < lsfile_t > files;
	getlflist(dir.c_str(),purefname.c_str(),files);
	lsfile_t tmp;
	int size = files.size();
	int delfnum = size - DEFAULT_LNUM;
	if(delfnum)
	{
		cout << "size: " << size << endl;
		std::sort(files.begin(),files.end(),sortbymodify); 
		while(delfnum--)
		{
			tmp = files.at(size-1);
			if (remove(tmp.fullfname_t.c_str()) == 0)
			{
				printf("%s will be delete\n",tmp.fullfname_t.c_str());
			}
			else
				perror("Remove");
			files.pop_back();
			size--;
		}
	}
	cout << "sort by modify time: " << endl;
	showalll(files);
	return size;
}

int main()
{
	string path = "../log/first.log";
	int lognum = 0;
	lognum = checkfname(path);
	cout << "======================" << endl;
	cout << "lognum: " << lognum << endl;
	return 0;
}
