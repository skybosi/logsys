#ifndef _MDEF_H_
#define _MDEF_H_
#include <vector>
#include <string>
#include <map>

enum log_level
{
	LOG_CORE = 0,
	LOG_BAD,
	LOG_ERROR,
	LOG_WARNING,
	LOG_NOTICE,
	LOG_INFO,
	LOG_DEBUG
};
#define BLK "  "
#define STR(T) #T
typedef std::vector<std::string> strv;
typedef std::map <std::string, std::string> strm;
#define INT  int
#define LONG long
#define DOBL double
//log of format (F:file M:method L:line T:thread)
#define __THREADID__  	pthread_self()
#define ALLFMT(_C, _X)	"[ "#_C" ]"BLK"[ F:%-08s M:%-04s L:%-03d T:%08X ]:>"BLK _X,__FILE__,__FUNCTION__,__LINE__,__THREADID__
#define MLTFMT(_C, _X) 	"[ "#_C" ]"BLK"[ M:%-04s L:%-03d T:%08X ]:>"BLK _X,__FUNCTION__,__LINE__,__THREADID__
#define MLFMT(_C, _X) 	"[ "#_C" ]"BLK"[ M:%-04s L:%-03d ]:>"BLK _X,__FUNCTION__,__LINE__
#define LTFMT(_C, _X)  	"[ "#_C" ]"BLK"[ L:%-03d T:%08X ]:>"BLK _X,__LINE__,__THREADID__
#define LFMT(_C, _X)   	"[ "#_C" ]"BLK"[ L:%-03d ]:>"BLK _X,__LINE__
#define TFMT(_C, _X)   	"[ "#_C" ]"BLK"[ L:%08d ]:>"BLK _X,__THREADID__
//set the each conf
#define SET(_C,_X)			set(_C,#_X)
//append the path,if need
/*
	 string lastpos = _lconf.LOGPATH.substr(_lconf.LOGPATH.size() - 1);
	 if (lastpos != "/")
	 _lconf.LOGPATH.append("/");
*/
#define APPEND(_C,_X) ( (_C).substr((_C).size()-1) != (_X) ) ? _C.append((_X)) : _C
/* 
bool logenv = true;
   #define DEBUG ((logenv)?(logenv=false,(__LINE__)<<3,LOG_DEBUG):
   (logenv=true,LOG_DEBUG,(__LINE__))) #define INFO
   ((logenv)?(logenv=false,(__LINE__),LOG_INFO):
   (logenv=true,LOG_INFO,(__LINE__))) #define NOTICE
   ((logenv)?(logenv=false,(__LINE__),LOG_NOTICE): (LOG_NOTICE,(__LINE__)))
   #define WARNING ((logenv)?(logenv=false,(__LINE__),LOG_WARNING):
   (LOG_WARNING,(__LINE__))) #define ERROR
   ((logenv)?(logenv=false,(__LINE__),LOG_ERROR):
   (logenv=true,LOG_ERROR,(__LINE__))) #define BAD
   ((logenv)?(logenv=false,(__LINE__),LOG_BAD): (LOG_BAD,(__LINE__))) #define CORE 
   ((logenv)?(logenv=false,(__LINE__),LOG_CORE): (LOG_CORE,(__LINE__))) 
*/
#define LDEBUG		( (__LINE__) << 3 | ( LOG_DEBUG   ) )
#define LINFO			( (__LINE__) << 3 | ( LOG_INFO    ) )
#define LNOTICE		( (__LINE__) << 3 | ( LOG_NOTICE 	) )
#define LWARNING	( (__LINE__) << 3 | ( LOG_WARNING ) )
#define LERROR		( (__LINE__) << 3 | ( LOG_ERROR   ) )
#define LBAD			( (__LINE__) << 3 | ( LOG_BAD     ) )
#define LCORE			( (__LINE__) << 3 | ( LOG_CORE    ) )

#endif // _MDEF_H_ mdef.h header file
