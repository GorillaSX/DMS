//implement log queue class
#include "logqueue.h"
#include <iostream>
using namespace std;
//log queue class
LogQueue g_logQueue;
//constructor
LogQueue::LogQueue(void)
{
	//create a sync mutex	
	pthread_mutex_init(&m_mutex,0);
	//create a syn condition variable
	pthread_cond_init(&m_cond,0);
}
//destructor
LogQueue::~LogQueue(void)
{
	//destroy condition variable
	pthread_cond_destroy(&m_cond);
	//destroy sync mutex
	pthread_mutex_destroy(&m_mutex);
}
//push log record
LogQueue& LogQueue::operator << (MLogRec const& log)
{
	cout << "push log record begin..." << endl;
	pthread_mutex_lock(&m_mutex);
	m_logs.push_back(log);
	pthread_cond_signal(&m_cond);
	pthread_mutex_unlock(&m_mutex);
	return *this;
	cout << "push log record end" << endl;
}
//pop log record	
LogQueue& LogQueue::operator >> (MLogRec & log)
{
	cout << "pop log record begin..." << endl;
	pthread_mutex_lock(&m_mutex);
	while(m_logs.empty())        //while is useful when there are two consumer
	{
		pthread_cond_wait(&m_cond,&m_mutex);
	}
	log = m_logs.front();
	m_logs.pop_front();
	pthread_mutex_unlock(&m_mutex);
	return *this;
	cout << "pop log record end " << endl;
}

