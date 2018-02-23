//declare thread class
#ifndef _LOGTHREAD_H
#define _LOGTHREAD_H
#include <pthread.h>
#include "except.h"
class LogThread
{
	public:	
		virtual ~LogThread(void){}
		//start thread
		void start(void)throw(ThreadException);
		//thread process
		virtual void run (void) = 0;
	private:
		static void * run ( void* arg); 
};


#endif //_LOGTHREAD_H

