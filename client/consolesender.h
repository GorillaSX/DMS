//declare console log sender  class
#ifndef _CONSOLESENDER_H
#define _CONSOLESENDER_H
#include "logsender.h"
//console log sender class
class ConsoleSender : public LogSender
{
	public:
			//send log
			void sendlog(list<MLogRec>& logs) throw ();
};
#endif //_CONSOLESENDER_H

