//implement store thread class
#include <iostream>
#include "logqueue.h"
using namespace std;
#include "storethread.h"
//store thread class
//constructor
StoreThread::StoreThread(LogDao& dao):m_dao(dao) //data access object
{
}
//thread process
void StoreThread::run(void)
{
	for(;;)
	{
		MLogRec log;
		//pop one record
		g_logQueue >> log;
		//insert to database
		try
		{
			m_dao.insert(log);
		}
		catch(DBException& ex)
		{
			cout << ex.what() << endl;
		}
	}
}

