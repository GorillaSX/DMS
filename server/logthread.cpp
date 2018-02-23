//implement thread class
#include <pthread.h>
#include <iostream>
#include "logthread.h"
#include "except.h"
using namespace std;
//start thread
void LogThread::start(void)throw(ThreadException)
{
	cout << "start thread begin..." << endl;
    pthread_t tid;	
	if(pthread_create(&tid,NULL,run,this))
		throw ThreadException("start thread failure");
	cout << "start thread end" << endl;
}
//thread process
void* LogThread::run( void* arg)
{
	pthread_detach(pthread_self());
	reinterpret_cast<LogThread*>(arg)->run();
	return NULL;
}



