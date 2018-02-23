//declare server class
#ifndef _SERVER_H
#define _SERVER_H
#include <string>
using namespace std;
#include "serversocket.h"
#include "storethread.h"
//server class
class Server
{
	public:
		//constructor
		Server(LogDao& dao,            //data access object
			   short port,             //bind port
			   string const& ip = ""   //bind ip address
			  )throw(ServerException);
		//mining data
		void dataMine(void)throw(ServerException);
	private:
		StoreThread m_store;	//store thread
		ServerSocket m_socket;  //server socket
};
#endif //_SERVER_H
