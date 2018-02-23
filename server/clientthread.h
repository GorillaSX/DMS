//declare client thread class
#ifndef _CLIENTTHREAD_H
#define _CLIENTTHREAD_H
#include "logthread.h"
#include "logqueue.h"
//client thread class
class ClientThread: public LogThread
{
public:
	//constructor
	ClientThread(int connfd); //communication socket
	//thread process
	void run(void);
private:
	int m_connfd;
};
#endif //_CLIENTTHREAD_H
