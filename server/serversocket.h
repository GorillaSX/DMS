//declare server socket class
#ifndef _SERVERSOCKET_H
#define _SERVERSOCKET_H
#include "except.h"
class ServerSocket
{
	public:
		//constructor
		ServerSocket(short port,            //binded port
					 string const& ip = "" //binded ip address
					)throw(SocketException);
		//waiting for client connect
		void acceptClient(void)throw(SocketException);
	private:
		int m_sockfd; //listening socket
};
#endif //_SERVERSOCKET_H
