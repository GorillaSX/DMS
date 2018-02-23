//implement client thread class
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
using namespace std;
#include "clientthread.h"
#include "logqueue.h"

//client thread class
//constructor
ClientThread::ClientThread(int connfd):m_connfd(connfd){} //communication socket
//thread process
void ClientThread::run(void)
{
	MLogRec log;
	unsigned long long logs;
	for(logs = 0;;++logs)
	{
		ssize_t rlen;
		for(size_t len = sizeof(log);len;len -= rlen)
		{
			if((rlen = recv(m_connfd,((char*)&log) + (sizeof(log) - len),len,0)) <= 0)
				goto escape;
		}
			
		log.pid = ntohl(log.pid);
		log.logintime = ntohl(log.logintime);
		log.logouttime = ntohl(log.logouttime);
		log.durations = ntohl(log.durations);
		g_logQueue << log;
	}
escape:
	cout << "received" << logs << "matched log record" << endl;
	close(m_connfd);
	delete this;       // when thread end, thread object kill itself
}
