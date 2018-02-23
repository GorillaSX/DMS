//declare store thread class
#ifndef _STORETHREAD_H
#define _STORETHREAD_H
#include "logthread.h"
#include "logdao.h"
//store thread class
class StoreThread: public LogThread
{
	public:
		StoreThread(LogDao& dao); //data access object
		//thread process
		void run(void);
	private:
	 	LogDao& m_dao;  //data access object
};
#endif //_STORETHREAD_H
