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
#define BLK "\t"
#define STR(T) #T
//write log's macro
#define wlog(lev,clas,lformat,...)			{ log->writeL((lev),#clas,lformat, ##__VA_ARGS__);} 
#define wlog2(clas,lev,lformat,args...)		{ clas temp; temp.writeL((lev),lformat, ##args);} 
typedef std::vector<std::string> strv;
typedef std::map <std::string, std::string> strm;
#define INT int
#define LONG long
#define DOBL double
#define CLOGFMT(_C, _X) #_C "\t[T%08X] " _X, (uint32)(100)

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
#define LDEBUG		( (__LINE__) << 3 | ( LOG_DEBUG ) )
#define LINFO			( (__LINE__) << 3 | ( LOG_INFO ) )
#define LNOTICE		( (__LINE__) << 3 | ( LOG_NOTICE ) )
#define LWARNING	( (__LINE__) << 3 | ( LOG_WARNING ) )
#define LERROR		( (__LINE__) << 3 | ( LOG_ERROR ) )
#define LBAD			( (__LINE__) << 3 | ( LOG_BAD ) )
#define LCORE			( (__LINE__) << 3 | ( LOG_CORE ) )

#endif // _MDEF_H_ mdef.h header file
