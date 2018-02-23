//implement socket log sender  class
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "socketsender.h"
		//constructor
SocketSender::SocketSender(string const& failFile,    //the fail file need to send
					short port,                 //server port
					string const& ip/* = "127.0.0.1"*/): //server ip address
					m_failFile(failFile),
					m_port(port),
					m_ip(ip)
{
	
}
		//send log
void SocketSender::sendlog(list<MLogRec>& logs) throw (ClientException)
{
	cout << "send log begin..." << endl;
	try
	{
		try
		{
			readFailFile(logs);
		}
		catch(ReadException& ex)
		{
			cout << "not find send file!" << endl;
		}
		//connect server
		connectServer();
		//send data
		sendData(logs);
		
	}
	catch(SocketException& ex)
	{
		//save fail file
		saveFailFile(logs);
		throw;
	}
	catch(SendException& ex)
	{
		//send fail file
		saveFailFile(logs);
		throw;
	}
	cout << "send log end"      << endl;
}
		//read fail file 
void SocketSender::readFailFile(list<MLogRec>& logs)throw(ReadException)
{
	cout << "read file begin..." << endl;
	ifstream ifs(m_failFile.c_str(), ios::binary);
	if(!ifs)
	{
		throw ReadException("Read Fail File error");	
	}
	MLogRec log;
	while(ifs.read((char*)&log, sizeof(log)))
	{
		logs.push_front(log);
	}
	if(!ifs.eof())
		throw ReadException();
	ifs.close();
	unlink(m_failFile.c_str());
	cout << "read file end" << endl;
}

		//connect server
void SocketSender::connectServer(void)throw(SocketException)
{
	cout << "connect server begin..." << endl;
	if((m_sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
		throw SocketException();
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(m_port);
	addr.sin_addr.s_addr = inet_addr(m_ip.c_str());
	if(connect(m_sockfd,(sockaddr*)&addr,sizeof(addr)) == -1)
	{
		close(m_sockfd);
		throw SocketException();
	}
	cout << "connect server end" << endl;
}
		//send data
void SocketSender::sendData(list<MLogRec>& logs)throw(SendException)
{
	cout << "send data begin...." << endl;
	while(!logs.empty())
	{
		MLogRec log = logs.front();
		log.pid = htonl(log.pid);
		log.logintime = htonl(log.logintime);
		log.logouttime = htonl(log.logouttime);
		log.durations = htonl(log.durations);
		if(send(m_sockfd,&log,sizeof(log),0) == -1)
		{
			close(m_sockfd);
			throw SocketException();
		}		
		// delete send succeed  log records
		logs.pop_front();
	}
	close(m_sockfd);
	cout << "send data end" << endl;
}
		//saveFailFile
void SocketSender::saveFailFile(list<MLogRec>& logs)throw(SaveException)
{
	cout << "save fail file begin..." << endl;
	if(!logs.empty())
	{
		ofstream ofs(m_failFile.c_str(),ios::binary);
		if(!ofs)
		{
			throw SaveException();
		}
		while(!logs.empty())
		{
			ofs.write((const char*)&logs.front(),sizeof(MLogRec));
			logs.pop_front();
		}
		ofs.close();
	}
	cout << "save fail file end" << endl;
}


