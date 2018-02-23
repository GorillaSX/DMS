//implement server class
//server class
#include "server.h"
//constructor
Server::Server(LogDao& dao,            //data access object
	   short port,             //bind port
	   string const& ip /*= "" */  //bind ip address
	  )throw(ServerException):m_store(dao),m_socket(port,ip){}
//mining data
void Server::dataMine(void)throw(ServerException)
{
	//start store thread
	m_store.start();
	//waiting for client connect
	m_socket.acceptClient();
}

