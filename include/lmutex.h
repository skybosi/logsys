#ifndef _LMUTEX_H_
#define _LMUTEX_H_

#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <signal.h>
enum lockway
{
	ATOMIC,
	MUTEXS,
};
using namespace std;
class lmutex
{
	private:
		static int lock;
		static int unlock;
		int symbol_synx;
		pthread_mutex_t     mutex;
		pthread_mutexattr_t     mutexattr;
	public:
		lmutex();
		~lmutex()
		{
			//cout << "delete the lock" << endl;
		//	if(mutex != NULL && mutexattr != NULL)
			{
				pthread_mutexattr_destroy(&mutexattr);
				pthread_mutex_destroy(&mutex);
			}
		}
		void setlock(lockway chose = ATOMIC);
		void setunlock(lockway chose = ATOMIC);
};

#endif
// lmutex.h
