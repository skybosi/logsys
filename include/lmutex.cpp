#include "lmutex.h"

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

