//log sender interface class
#ifndef _LOGSENDER_H
#define _LOGSENDER_H
#include <list>
using namespace std;
#include "data.h"
#include "except.h"
//log sender interface class
class LogSender
{
	public:
			//send log
			virtual void sendlog(list<MLogRec>& logs) throw (ClientException) = 0;
};
#endif //_LOGSENDER_H

