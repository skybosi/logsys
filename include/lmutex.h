#ifndef _LMUTEX_H_
#define _LMUTEX_H_

#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <signal.h>
using namespace std;
class lmutex
{
  private:
	static int lock;
	static int unlock;
	int symbol_synx;
  public:
	  lmutex();
	 ~lmutex()
	{
		cout << "delete a array!" << endl;
	}
	void setlock();
	void setunlock();
};

int lmutex::lock = 0;
int lmutex::unlock = 1;
lmutex::lmutex()
{
	symbol_synx = 0;
}  

void lmutex::setlock()
{
	cout << "lmutex is locking ..." << endl;
	while (!(__sync_bool_compare_and_swap(&symbol_synx, lock, 1)));	// 上锁
}

void lmutex::setunlock()
{
	cout << "lmutex is will unlock ..." << endl;
	__sync_bool_compare_and_swap(&symbol_synx, unlock, 0);	// 解锁
}
#endif
	// lmutex.h
