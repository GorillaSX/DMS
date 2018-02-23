//exception class
#ifndef _EXCEPT_H
#define _EXCEPT_H
#include <string>
using namespace std;
//server exception base class
class ServerException: public exception
{
	public:
		ServerException(void):m_msg("Server Exception!"){}
		ServerException(string const& msg):m_msg("Server Exception:")
		{
			m_msg += msg;
			m_msg += "!";
		}
		~ServerException(void)throw(){}
		char const *what(void) const throw()
		{
			return m_msg.c_str();
		}
	private:
		string m_msg; //exception description message

};
//DataBase exception
class DBException: public ServerException
{
	public:
			DBException(void):ServerException("database error"){}
			DBException(string const& msg):ServerException(msg){}
};
//Network exceptiop
class SocketException:public ServerException
{
	public:
		SocketException(void):ServerException("newtork error"){}
		SocketException(string const & msg):ServerException(msg){}
};
//thread exception
class ThreadException:public ServerException
{
	public:
		ThreadException(void):ServerException("thread error"){}
		ThreadException(string const& msg):ServerException(msg){}
};
#endif //_EXCEPT_H

