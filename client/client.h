//declare client class
#ifndef _CLIENT_H
#define _CLIENT_H
#include "logreader.h"
#include "logsender.h"
class Client
{
	public:
		//constructor
		Client(LogReader& reader,      //log reader
			   LogSender& sender);     //log sender
		//data mining
		void dataMine(void)throw(ClientException);
	private:
		LogReader& m_reader; //log reader 
		LogSender& m_sender; //log sender
};
#endif //_CLIENT_H
