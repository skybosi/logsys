#ifndef _FILEDATA_H_
#define _FILEDATA_H_
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

using namespace std;
class filedata
{
	private:
		typedef struct lsfile
		{
			string paths;
			string purefname_t;
			string fullfname_t;
			time_t lmodify_t;
			time_t laccess_t;
			time_t lstatus_t;
		}lsfile_t;
		string _logfpath;
		vector < lsfile_t > _files;
		vector < lsfile_t > _delfiles;
	private:
		string & delsuffix(string & filepath);
		static bool sortbyfilename( const lsfile_t &v1, const lsfile_t &v2);
		static bool sortbyaccess( const lsfile_t &v1, const lsfile_t &v2);
		static bool sortbymodify( const lsfile_t &v1, const lsfile_t &v2);
		static bool sortbystatus( const lsfile_t &v1, const lsfile_t &v2);
		bool deloldfile();
	public:
		filedata(string logfpath);
		~filedata();
		void getlflist(const char *dir,const char *ptfname);
		int  checkfname();
		void showalll(vector < lsfile_t > files)const;
};

#endif
//filedata.h
