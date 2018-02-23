//data class
#ifndef _DATA_H_
#define _DATA_H_
#include <unistd.h>
#include <iostream>
using namespace std;

struct MLogRec
{
	char logname[32];//log name 
	char logip[32];  //log ip
	pid_t pid;       //log pid
	long logintime;  //log in time
	long logouttime; //log out time
	long durations;  //log durations
	friend ostream& operator<<(ostream& os, MLogRec const& log)
	{
		return os << log.logname << ',' 
				<< log.logip << ',' 
				<< log.pid   << ','
				<< log.logintime << ',' 
				<< log.logouttime << ','
				<< log.durations;
	}
};


#endif// __DATA_H
