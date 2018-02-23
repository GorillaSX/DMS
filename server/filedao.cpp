//implement file data access class
#include "filedao.h"
//constructor
FileDao::FileDao(string const& path)throw(DBException) //file path
{
	cout << "open database start...." << endl;
	m_ofs.open(path.c_str(),ios::app);
	if(!m_ofs)
		throw DBException("database file cannot open");
	cout << "open database end" << endl;
}
//destructor
FileDao::~FileDao(void)
{
	cout << "close database start..." << endl;
	m_ofs.close();
	cout << "close database end" << endl;
}
//insert data
void FileDao::insert(MLogRec const& log) throw(DBException)
{
	cout << "insert databse start..." << endl;
	m_ofs << log << endl;
	cout << "insert database stop" << endl;
}
