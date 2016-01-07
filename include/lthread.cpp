#include "lthread.h"

//lthread::lthread(logconf & conf):Basethread(), _conf(conf), renameflag(false),breakflag(true)
lthread::lthread(logconf & conf):Basethread(), renameflag(false),breakflag(true)
{
	_conf = conf; 
	cout << "log thread is coming..." << endl;
	_logfmutex = new lmutex();
	_filedata = new filedata(_conf);
}
lthread::CGarbo lthread::garbo;
lthread *lthread::_linstance = NULL;
lthread *lthread::getlthread(logconf & conf)
{
//	static lthread *_linstance;
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
	_filedata->init_files();
	while (breakflag)
	{
		_logfmutex->setlock();
		//checkffull();
		if (_filedata->checkfname())
			_filedata->rmflag = false;
		_logfmutex->setunlock();
	}
	return 0;
}

// check the log file's size
bool lthread::checkffull()
{
	float fsize = getfsize(_conf.FSUNIT);
	if (renameflag == false && fsize >= _conf.LOGFSIZE)
	{
		renameflag = true;
	}
	else
	{
		cout << "log file is not full! come on baby!" << endl;
		renameflag = false;
	}
	return renameflag;
}
//free data
void lthread::freedata()
{
	if(_logfmutex)
	{
		delete _logfmutex;
		_logfmutex = NULL;
	}
	if(_filedata)
	{
		delete _filedata;
		_filedata = NULL;
	}
}

bool lthread::addnewf(lsfile_t& newlogf)
{
	if(& newlogf)
	{
		_filedata->addnewfile(newlogf);
		return true;
	}
	else
		return false;
}
// get the size of log file
float lthread::getfsize(FSU& fsu)
{
	const char *filename = _conf.FULLPATH.c_str();
	struct stat finfo;
	memset(&finfo, 0, sizeof(finfo));
	stat(filename, &finfo);
	float fsize = (float)finfo.st_size;
	switch (fsu)
	{
		case BYTE:
			cout << "log file size: " << fsize << " Byte" << endl;
			break;
		case KB:
			fsize /= 1024;
			cout << "log file size: " << fsize << " Kb" << endl;
			break;
		case MB:
			fsize /= (1024 * 1024);
			cout << "log file size: " << fsize << " Mb" << endl;
			break;
		default://KB
			fsize /= 1024;
			cout << "log file size: " << fsize << " Kb" << endl;
			break;
	}
	return fsize;
}
