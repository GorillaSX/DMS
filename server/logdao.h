//data access interface class
#ifndef _LOGDAO_H
#define _LOGDAO_H
#include "except.h"
#include "data.h"
//data access interface class
class LogDao
{
	public:
		virtual ~LogDao(void){}
		//insert data
		virtual void insert(MLogRec const& log) throw(DBException) = 0;
};
#endif //_LOGDAO_H
