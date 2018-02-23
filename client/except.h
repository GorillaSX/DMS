//exception class
#ifndef _EXCEPT_H
#define _EXCEPT_H
#include <string>
using namespace std;
//client exception base class
class ClientException: public exception
{
	public:
		ClientException(void):m_msg("Client Exception!"){}
		ClientException(string const& msg):m_msg("Client Exception:")
		{
			m_msg += msg;
			m_msg += "!";
		}
		~ClientException(void)throw(){}
		char const *what(void) const throw()
		{
			return m_msg.c_str();
		}
	private:
		string m_msg; //exception description message

};
//back up exception
class BackupException: public ClientException
{
	public:
			BackupException(void):ClientException("backup error"){}
			BackupException(string const& msg):ClientException(msg){}
};
//read exception
class ReadException : public ClientException
{
	public:
		ReadException(void):ClientException("read error"){}
		ReadException(string const& msg):ClientException(msg){}
};
//save exception
class SaveException: public ClientException
{
	public:
			SaveException(void):ClientException("save error"){}
			SaveException(string const& msg):ClientException(msg){}
};
//Network exceptiop
class SocketException:public ClientException
{
	public:
		SocketException(void):ClientException("newtork error"){}
		SocketException(string const & msg):ClientException(msg){}
};
//send exception
class SendException:public ClientException
{
	public:
		SendException(void):ClientException("send error"){}
		SendException(string const& msg):ClientException(msg){}
};
#endif //_EXCEPT_H

