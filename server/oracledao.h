//declare oracle data access class
#ifndef _ORACLEDAO_H
#define _ORACLEDAO_H
#include "logdao.h"
#include <iostream>
#include <fstream>
using namespace std;
//oracle data access class
class OracleDao:public LogDao
{
	public:
		//constructor
		OracleDao(string const& username,  // database user
				  string const& password)throw(DBException); // databse password
		//destructor
		~OracleDao(void);
		//insert data
		void insert(MLogRec const& log) throw(DBException);
};
#endif //_ORACLEDAO_H
