#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>
#include <vector>
using namespace std;
void getlflist(const char * dir, vector<string>& files )
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if((dp = opendir(dir)) == NULL) 
	{
		fprintf(stderr,"cannot open directory: %s\n", dir);
		return;
	}
	chdir(dir);
	char filename[1024];
	while((entry = readdir(dp)) != NULL) 
	{
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)) 
		{

			if(strcmp(".",entry->d_name) == 0 ||
					strcmp("..",entry->d_name) == 0)
				continue;
			getlflist(entry->d_name,files);
		}
		else
		{
			sprintf(filename,"%s",entry->d_name);
			files.push_back(filename);	
		}
	}
	chdir("..");
	closedir(dp);
}
int checkfname(string logfpath)
{
	string purefname;
	size_t pos = logfpath.rfind("/");
	if(pos != logfpath.npos)
		purefname = logfpath.substr(pos+1);
	size_t len = purefname.size();   
	cout << "purefname:" << purefname.erase(len-4) << endl;
	string dir = logfpath.erase(pos,len + 1);
	cout << "dir:" << dir << endl;
	vector<string> files;
	getlflist(dir.c_str(),files);
	int logfnum = 0;
	int size = files.size();
	for(int i =0;i < size;i++)
	{
		//printf("llll:%s \n",files[i].c_str());
		if(files[i].find(purefname) != files[i].npos)
		{
			printf("%s\n",files[i].c_str());
			logfnum++;
		}
	}
	return logfnum;
}

int main()
{
	checkfname("../log/first.log");	
	return 0;
}
