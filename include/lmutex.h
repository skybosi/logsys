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
int lmutex::lock = 0;
int lmutex::unlock = 1;

lmutex::lmutex()
{
	symbol_synx = 0;
	pthread_mutex_init(&mutex, NULL);
	pthread_mutexattr_init(&mutexattr);
}

void lmutex::setlock(lockway chose)
{
	//cout << "lmutex is locking ..." << endl;
	switch (chose)
	{
		case ATOMIC:
			while (!(__sync_bool_compare_and_swap(&symbol_synx, lock, 1)));	// 上锁
			break;
		case MUTEXS:
			if(pthread_mutex_lock(&mutex) != 0)
				cout << "lock failure" << endl;
			else
				cout << "lock success" << endl;;
			break;
		default:
			while (!(__sync_bool_compare_and_swap(&symbol_synx, lock, 1)));	// 上锁
			break;
	}
}

void lmutex::setunlock(lockway chose)
{
	//cout << "lmutex is will unlock ..." << endl;
	switch (chose)
	{
		case ATOMIC:
			__sync_bool_compare_and_swap(&symbol_synx, unlock, 0);	// 解锁
			break;
		case MUTEXS:
			if(pthread_mutex_unlock(&mutex)!= 0)
				cout << "unlock failure" << endl;
			else
				cout << "unlock success" << endl;;
			break;
		default:
			__sync_bool_compare_and_swap(&symbol_synx, unlock, 0);	// 解锁
			break;
	}
}
#endif
// lmutex.h
