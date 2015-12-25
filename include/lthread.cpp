#include "lthread.h"

// lthread::lthread(string& logpath, long
// maxfsize):Basethread(1),_flogpath(logpath),
// _maxfsize(maxfsize),renameflag(false)
lthread::lthread(logconf & conf):Basethread(1), _conf(conf), renameflag(false)
{
	cout << "log thread is coming..." << endl;
	_logfmutex = new lmutex();
	_filedata = new filedata(_conf);
}

//lthread *lthread::_linstance = NULL;
lthread *lthread::getlthread(logconf & conf)
{
	static lthread *_linstance;
	if (_linstance == NULL)		// 判断是否第一次调用
	{
		_linstance = new lthread(conf);
	}
	return _linstance;
}
/*
lthread::~lthread
{
	if(_linstance)
	{
		_linstance = NULL;
		delete _linstance;
	}
	delete _logfmutex;
	cout << "log thread will deading " << endl;
}
*/
int lthread::run()
{
	while (1)
	{
		_logfmutex->setlock();
		//checkffull();
		if (_filedata->rmflag == false && _filedata->checkfname())
			_filedata->deloldfile();
		_logfmutex->setunlock();
	}
	return 0;
}


// check the log file's size
bool lthread::checkffull()
{
	cout << "我来了" << endl;
	long fsize = getfsize(_conf.FSUNIT);
	if (renameflag == false && fsize >= _conf.LOGFSIZE)
	{
		renameflag = true;
	}
	else
	{
		cout << "log file is not full! come on baby!" << endl;
		// renameflag = false;
	}
	return renameflag;
}

// get the size of log file
long lthread::getfsize(FSU& fsu)
{
	const char *filename = _conf.FULLPATH.c_str();
	struct stat finfo;
	memset(&finfo, 0, sizeof(finfo));
	stat(filename, &finfo);
	long fsize = finfo.st_size;
	switch (fsu)
	{
	case BYTE:
		cout << "log file size: " << fsize << " Byte" << endl;
		return fsize;
		break;
	case KB:
		cout << "log file size: " << fsize << " Kb" << endl;
		return fsize / 1024;
		break;
	case MB:
		cout << "log file size: " << fsize << " Mb" << endl;
		return fsize / (1024 * 1024);
		break;
	default:
		cout << "log file size: " << fsize << " Kb" << endl;
		return fsize;
		break;
	}
}
