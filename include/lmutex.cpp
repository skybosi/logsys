#include "lmutex.h"

int lmutex::lock = 0;
int lmutex::unlock = 1;

lmutex::lmutex()
{
#ifdef _LUNIX
	symbol_synx = 0;
#else
	m_lock = 0;
#endif
	pthread_mutex_init(&mutex, NULL);
	pthread_mutexattr_init(&mutexattr);
}

void lmutex::setlock(lockway chose)
{
	//cout << "lmutex is locking ..." << endl;
	switch (chose)
	{
		case ATOMIC:
#ifdef _LUNIX
			while (!(__sync_bool_compare_and_swap(&symbol_synx, lock, 1)));	// 上锁
#else
			while( InterlockedCompareExchange( &m_lock, 1 , 0) != 0 );
#endif
			break;
		case MUTEXS:
#ifdef _LUNIX
			if(pthread_mutex_lock(&mutex) != 0)
				cout << "lock failure" << endl;
			else
				cout << "lock success" << endl;
#else
			::EnterCriticalSection((LPCRITICAL_SECTION)&mutex);
#endif
			break;
		default:
#ifdef _LUNIX
			while (!(__sync_bool_compare_and_swap(&symbol_synx, lock, 1)));	// 上锁
#else
			while( InterlockedCompareExchange( &m_lock, 1 , 0) != 0 );
#endif
			break;
	}
}

void lmutex::setunlock(lockway chose)
{
	//cout << "lmutex is will unlock ..." << endl;
	switch (chose)
	{
		case ATOMIC:
#ifdef _LUNIX
			__sync_bool_compare_and_swap(&symbol_synx, unlock, 0);	// 解锁
#else
			InterlockedExchange(&m_lock, 0);
#endif
			break;
		case MUTEXS:
#ifdef _LUNIX
			if(pthread_mutex_unlock(&mutex)!= 0)
				cout << "unlock failure" << endl;
			else
				cout << "unlock success" << endl;;
#else
			::LeaveCriticalSection((LPCRITICAL_SECTION)&mutex);
#endif
			break;
		default:
#ifdef _LUNIX
			__sync_bool_compare_and_swap(&symbol_synx, unlock, 0);	// 解锁
#else
			InterlockedExchange(&m_lock, 0);
#endif
			break;
	}
}

