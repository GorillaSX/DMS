//declare log queue class
#ifndef _LOGQUEUE_H
#define _LOGQUEUE_H
#include <pthread.h>
#include <list>
using namespace std;
#include "data.h"
//log queue class
class LogQueue
{
	public:
		//constructor
		LogQueue(void);
		//destructor
		~LogQueue(void);
		//push log record
		LogQueue& operator << (MLogRec const& log);
		//pop log record	
		LogQueue& operator >> (MLogRec & log);

	private:
		pthread_mutex_t m_mutex;//sync mutual exclusion
		pthread_cond_t m_cond;  //sync condition variable
		list<MLogRec> m_logs;   //log records queue
};
extern LogQueue g_logQueue;
#endif //_LOGQUEUE_H
