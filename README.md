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
 - log_main.cpp -- ***test the log system program***
 - log_thread.cpp -- ***test the log system program with multi-threads***
- test -- ***some test program when write the system, is not the part of this project***
 - format.c getlist.cpp getpath.cpp lthread.cpp parconf.c parseconf.cpp 
 - tm.c, 逗号表达式.txt, 可变参数.cpp, 可变参数函数的多级调用.cpp
 - thread
    - Basethread.cpp Basethread.h
    - lmutex.cpp lmutex.h
    - test.cpp


6 directories, 36 files
