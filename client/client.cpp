//implement client class
#include "client.h"
#include <iostream>
using namespace std;
		//constructor
Client::Client(LogReader& reader,      //log reader
	   LogSender& sender):             //log sender
		m_reader(reader),m_sender(sender){}     
//data mining
void Client::dataMine(void)throw(ClientException)
{
	cout << "data mining begin..." << endl;
	m_sender.sendlog(m_reader.readLog());
	cout << "data mining end" << endl;
}
