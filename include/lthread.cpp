#include "lthread.h" 

lthread::lthread(string logpath, long maxfsize):Basethread(1), _flogpath(logpath),
	_maxfsize(maxfsize)
{
	// cout << "log thread is coming..." << endl;
	 _logfmutex = new lmutex();
}

int lthread::run()
{
	_logfmutex->setlock();
	checkffull();

	// checklogfnum(_flogpath);
	 _logfmutex->setunlock();
	return 0;
}


// check the log file's size
bool lthread::checkffull()
{
	long fsize = getfsize();
	int len = _flogpath.size();
	//cout << "old parh:" << _flogpath << endl;
	string oldpath = _flogpath;
	if (fsize > _maxfsize)
	{
		cout << "我来了" << endl;
		string newfname = oldpath.erase(len - 4) + getime() + ".log";
		//cout << "new path:" << newfname << endl;
		rename(_flogpath.c_str(), newfname.c_str());
		cout << "rename ok!" << endl;
		ofstream newlfile;
		newlfile.open(_flogpath.c_str());
		if (!newlfile)
		{
			cerr << "open log file error!" << endl;
			exit(1);
		}
		newlfile.close();
		return true;
	}
	else
	{
		cout << "log file is not full! come on baby!" << endl;
	/*
		ofstream newlfile;
		newlfile.open(_flogpath.c_str());
		if (!newlfile)
		{
			cerr << "open log file error!" << endl;
			exit(1);
		}
		newlfile.close();
		*/
		return false;
	}
}
//get the size of log file
long lthread::getfsize()
{
	const char *filename = _flogpath.c_str();
	struct stat finfo;
	memset(&finfo, 0, sizeof(finfo));
	stat(filename, &finfo);
	long fsize = finfo.st_size;
	cout << "log file size: " << fsize << endl;
	return fsize;
}

// check the log file's numbers
bool lthread::checklogfnum(string logpath)
{
	int logfnum = checkfname(logpath);
	if (logfnum > 10)
		return false;
	return true;
}
//get the log file's list at the directory 
void getlflist(const char *dir, vector < string > &files)
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
	char filename[1024];
	while ((entry = readdir(dp)) != NULL)
	{
		lstat(entry->d_name, &statbuf);
		if (S_ISDIR(statbuf.st_mode))
		{

			if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
				continue;
			getlflist(entry->d_name, files);
		}
		else
		{
			sprintf(filename, "%s", entry->d_name);
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
	if (pos != logfpath.npos)
		purefname = logfpath.substr(pos + 1);
	size_t len = purefname.size();
	cout << "purefname:" << purefname.erase(len - 4) << endl;
	string dir = logfpath.erase(pos, len + 1);
	cout << "log's path: " << dir << endl;
	cout << "======================" << endl;
	vector < string > files;
	getlflist(dir.c_str(), files);
	int logfnum = 0;
	int size = files.size();
	for (int i = 0; i < size; i++)
	{
		// printf("llll:%s \n",files[i].c_str());
		if (files[i].find(purefname) != files[i].npos)
		{
			printf("%s\n", files[i].c_str());
			logfnum++;
		}
	}
	return logfnum;
}

static string getime()
{
	time_t now_time = time(NULL);;
	char curtime[64];
	memset(&curtime, 0, sizeof(curtime));
	strftime(curtime, sizeof(curtime), "_%y%m%d%H%M%S", localtime(&now_time));
	return curtime;
}

