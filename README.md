# logsys
A log system
The logT class'instance as a member variables of another class
**The problem about the log:**
##log system
Log file is a text document that recording the log you want print everytime or everywhere; so you can know the program how to work or while the program core down or other problem, you find the position easy!
The log system is a oriented class system ,As a base template class ,as the class's father-class you want set log! But the log file is not oriented class ,it means the log file is several class's home,maybe a namespace or a module!
##log file
The log file is update or recreate when the file's size is bigger than the DEFAULT_LFSIZE(=default log file size ,you set in etc/logsys.conf). The filename is module+time-tip+suffix(.log) ,the time-tip is create time.
##log system DS(directory structure)
- etc
 - logsys.conf -- ***The configuration file of the  log system***
 - sample.conf -- ***The test configuration file of the parseconf ***
- include
 - Basethread.cpp/h -- ***Base of thread***
 - confdata.cpp/h -- ***The data of configuration of log system***
 - filedata.cpp/h -- ***The log file list dealwith***
 - lmutex.cpp/h -- ***The log system mutex to make r/w safely***
 - log_T.cpp/h -- ***The log system write here***
 - lthread.cpp/h -- ***The check(log file's size and numbers) thread***
 - parseconf.cpp/h -- ***parse the log configuration***
 - Mdef.h -- ***some important marco***
- log
- makefile -- ***makefile get logsys.so or logsys.a***
- README.md
- src
 - log.cpp -- ***only test the log system program***
 - log_main.cpp -- ***test the log system program***
 - log_thread.cpp -- ***test the log system program with multi-threads***
- test -- ***some test program when write the system, is not the part of this project***
##log system using
 About the log's format type:
 log of format (***F:file M:method L:line T:thread***) 
###like xxxFMT type,there are here: 
- ALLFMT(_C, _X)    :show all msg in the log tip;
- MLTFMT(_C, _X) :show methed's name,log's lines and thread id msg;
- MLFMT(_C, _X)  :show methed's name,log's lines msg;
- LTFMT(_C, _X)  :show log's lines and thread id msg;
- LFMT(_C, _X)   :show log's lines msg only;
- TFMT(_C, _X)   :show thread id msg omly.
- NOTEs :
 - _C : Is the class name that you print logs;
 - _X : You want print massage ,just like printf funtion's format !
- For example:
```c
    #include "log_T.h"  //logsys header file
    #include <iostream>
    using namespace std;
    int main()
    {
        logT log("./etc/logsys.cong");
        (log)(ALLFMT(logT,"This is a log format ALLFMT hahahhahaha!"));
        (log)(MLTFMT(logT,"This is a log format MLTFMT hahahhahaha!"));
        (log)(MLFMT(logT," This is a log format MLFMT hahahhahaha!"));
        (log)(LTFMT(logT," This is a log format LTFMT hahahhahaha!"));
        (log)(LFMT(logT,"  This is a log format LFMT hahahhahaha!"));
        return 0;
    }
```

```c
	#include "log_T.h"
	#include <string>
	using namespace std;
	class test
	{
		public:
			test()
			{
				log = new logT("./etc/logsys.conf");
			}
			~test()
			{
				if(log)
					delete log;
			}
			void show()
			{
				(*log)(LDEBUG,ALLFMT(test,"debug debug ...%20s %9d"),"format",LOG_DEBUG);
				cout << "Ok !" << endl;
			}
		public:
			logT* log;
	};
	int main(int argc,char** argv)
	{
		test a;
		while(times--)
		{
			a.show();
		}
		return 0;
	}
```
