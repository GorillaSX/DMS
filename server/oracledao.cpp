//implement oracle data access class
#include "oracledao.h"
#include <iostream>
using namespace std;
//oracle data access class
//constructor
OracleDao::OracleDao(string const& username,  // database user
		  string const& password)throw(DBException) // databse password
{
	cout << "open database start..." << endl;
	cout << "open database end" << endl;
}
//destructor
OracleDao::~OracleDao(void)
{
	cout << "close database connect start...." << endl;
	cout << "close database connect end" << endl;
}
//insert data
void OracleDao::insert(MLogRec const& log) throw(DBException)
{
	cout << "insert database start... " << endl;
	cout << log << endl;
	cout << "insert database end" << endl;
}
