#include "lthread.h" 

static string getime();

lthread::lthread(string& logpath, long maxfsize):Basethread(1),_flogpath(logpath), _maxfsize(maxfsize),renameflag(false)
{
	 cout << "log thread is coming..." << endl;
	 _logfmutex = new lmutex();
	 _filedata = new filedata(logpath);
}

int lthread::run()
{
	while(1)
	{
		_logfmutex->setlock();
		checkffull();
		_filedata->checkfname();
		// checklogfnum(_flogpath);
		_logfmutex->setunlock();
//		sleep(1);
	}
	return 0;
}


// check the log file's size
bool lthread::checkffull()
{
	long fsize = getfsize();
	if (renameflag == false && fsize > _maxfsize)
	{
		cout << "我来了" << endl;
		renameflag = true;
	}
	else
	{
		cout << "log file is not full! come on baby!" << endl;
		renameflag = false;
	}
	return renameflag;
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
static string getime()
{
	time_t now_time = time(NULL);;
	char curtime[64];
	memset(&curtime, 0, sizeof(curtime));
	strftime(curtime, sizeof(curtime), "_%y%m%d%H%M%S", localtime(&now_time));
	return curtime;
}
