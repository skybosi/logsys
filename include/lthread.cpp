#include "lthread.h" 

//lthread::lthread(string& logpath, long maxfsize):Basethread(1),_flogpath(logpath), _maxfsize(maxfsize),renameflag(false)
lthread::lthread(logconf& conf):Basethread(1),_conf(conf),renameflag(false)
{
	 cout << "log thread is coming..." << endl;
	 _logfmutex = new lmutex();
	 _filedata = new filedata(_conf);
}

lthread* lthread::_linstance = NULL;
lthread* lthread::getlthread(logconf& conf)
{
	if(_linstance == NULL) //判断是否第一次调用
	{
		_linstance = new lthread(conf);
	}
	return _linstance;
}

int lthread::run()
{
	while(1)
	{
		_logfmutex->setlock();
		checkffull();
		if(_filedata->checkfname())
			_filedata->deloldfile();
		_logfmutex->setunlock();
	}
	return 0;
}


// check the log file's size
bool lthread::checkffull()
{
	long fsize = getfsize();
	if (renameflag == false && fsize >= _conf.LOGFSIZE)
	{
		cout << "我来了" << endl;
		renameflag = true;
	}
	else
	{
		cout << "log file is not full! come on baby!" << endl;
//		renameflag = false;
	}
	return renameflag;
}
//get the size of log file
long lthread::getfsize()
{
	const char *filename = _conf.FULLPATH.c_str();
	struct stat finfo;
	memset(&finfo, 0, sizeof(finfo));
	stat(filename, &finfo);
	long fsize = finfo.st_size;
	cout << "log file size: " << fsize << endl;
	return fsize;
}
