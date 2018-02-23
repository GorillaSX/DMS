//declare file data access class
#ifndef _FILEDAO_H
#define _FILEDAO_H
#include "logdao.h"
#include <iostream>
#include <fstream>
using namespace std;
//file data access class
class FileDao:public LogDao
{
	public:
		//constructor
		FileDao(string const& path)throw(DBException); //file path
		//destructor
		~FileDao(void);
		//insert data
		void insert(MLogRec const& log) throw(DBException);
	private:
		ofstream m_ofs;//file output stream
};
#endif //_FILEDAO_H
