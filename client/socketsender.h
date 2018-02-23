//declare socket log sender  class
#ifndef _SOCKETSENDER_H
#define _SOCKETSENDER_H
#include "logsender.h"
//socket log sender class
class SocketSender : public LogSender
{
	public:
		//constructor
		SocketSender(string const& failFile,    //the fail file need to send
					short port,                 //server port
					string const& ip = "127.0.0.1"); //server ip address
		//send log
		void sendlog(list<MLogRec>& logs) throw (ClientException);
	private:
		//read fail file 
		void readFailFile(list<MLogRec>& logs)throw(ReadException);
		//connect server
		void connectServer(void)throw(SocketException);
		//send data
		void sendData(list<MLogRec>& logs)throw(SendException);
		//saveFailFile
		void saveFailFile(list<MLogRec>& logs)throw(SaveException);
		string m_failFile; //send fail file 
		short  m_port;     //server port
		string m_ip;       //server ip address
		int    m_sockfd;   //socket descriptor

};
#endif //_SOCKETSENDER_H

