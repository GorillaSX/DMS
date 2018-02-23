//declare log reader class
#ifndef _LOGREADER_H
#define _LOGREADER_H
#include <string>
#include <list>
using namespace std;
#include "data.h"
#include "except.h"

//log reader 
class LogReader
{
	public:
		//constructor
		LogReader(string const& logfile,    //log file
				  string const& loginsFile); // logins file
		//read log
		list<MLogRec>& readLog(void)throw(ClientException);
				  
	private:
		//back up log file
		void backup(void)throw(BackupException);
		//read login file
		void readLoginsFile(void)throw(ReadException);
		//read backup file
		void readBackupFile(void)throw(ReadException);
		//match login and mogout
		void match(void);
		//save logins file;
		void saveLoginsFile(void)throw(SaveException);

		string        m_logFile;    //log file
		string        m_loginsFile; // login file
		string        m_backupFile; //backup file
		list<LogRec>  m_logins;  //login record
		list<LogRec>  m_logouts; //logout record
		list<MLogRec> m_logs;   //match log record

};

#endif //_LOGREADER_H

