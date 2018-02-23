//implement server socket class
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
using namespace std;
#include "clientthread.h"
#include "serversocket.h"

//constructor
ServerSocket::ServerSocket(short port,            //binded port
					 string const& ip/* = ""*/ //binded ip address
					)throw(SocketException)
{
	cout << "initializing server beginning..." << endl;
	if((m_sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
		throw SocketException("create socket failure");
	//set port reuse,to deal with the delay
	int on = 1;
	if(setsockopt(m_sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)) == -1)
		throw SocketException("set port reuse failure");
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(port);
	addr.sin_addr.s_addr = ip.empty() ? INADDR_ANY:inet_addr(ip.c_str());
	if(bind(m_sockfd,(sockaddr*)&addr,sizeof(addr)) == -1)
			throw SocketException("bind socket failure");
	if(listen(m_sockfd,1024) == -1)
		throw SocketException("listing socket failure");

	cout << "initializing server end... " << endl;
}
//waiting for client connect
void ServerSocket::acceptClient(void)throw(SocketException)
{
	cout << "waiting for client connect..." << endl;
	//loop block
	for(;;)
	{
		sockaddr_in addrcli;
		socklen_t   addrlen = sizeof(addrcli);
		int connfd = accept(m_sockfd,(sockaddr*)&addrcli,&addrlen);
		if(connfd == -1)
		{
			close(m_sockfd);
			throw SocketException("accept client failure");
		}
		(new ClientThread(connfd))->start();
	}
}

