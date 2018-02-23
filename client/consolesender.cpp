//implementation console log sender interface class
#include "consolesender.h"
#include <iostream>
using namespace std;
//send log
void ConsoleSender::sendlog(list<MLogRec>& logs) throw ()
{
	cout << "send log begin..." << endl;
	//traverse match log record
	for(list<MLogRec>::iterator it = logs.begin();it != logs.end();++it)
	{
		cout << *it << endl;
	}
	cout << "send log finish" << endl;
}

