//implementation log reader class
#include "logreader.h"
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;
//log reader 
		//constructor
LogReader::LogReader(string const& logFile,    //log file
		  string const& loginsFile):m_logFile(logFile),m_loginsFile(loginsFile){} // logins file
//read log
list<MLogRec>& LogReader::readLog(void)throw(ClientException)
{
	cout << "read log file begin..." << endl;
	//backup log file
	backup();
	//read logins file
	readLoginsFile();
	//read backup file
	readBackupFile();
	//match login and logout
	match();
	//save login record
	saveLoginsFile();
	cout << "read log file end" << endl;
	return m_logs;
}
		  
//back up log file
void LogReader::backup(void)throw(BackupException)
{
	cout << "backup log file begin..." << endl;
	//generate backup file name
	time_t now = time(NULL);
	tm* local = localtime(&now);
	ostringstream oss;
	oss << m_logFile << "." << setfill('0') 
		<< setw(4) << local->tm_year + 1900 
		<< setw(2) << local->tm_mon + 1
		<< setw(2) << local->tm_mday
		<< setw(2) << local->tm_hour
		<< setw(2) << local->tm_min
		<< setw(2) << local->tm_sec;
	m_backupFile = oss.str();
#ifdef _DEBUG
	cout << "backupfile" << m_backupFile << endl;
#endif //_DEBUG
	//generate backup command
	string cmd("./backup.sh ");
	cmd += m_logFile;
	cmd += " ";
	cmd += m_backupFile;
#ifdef _DEBUG
	cout << "backup commond" << cmd << endl;
#endif //_DEBUG
	//execute commmand 
	int status = system(cmd.c_str());
	if(WEXITSTATUS(status) == 1)
		throw BackupException("back up error");
	if(WEXITSTATUS(status) == 2)
		throw BackupException("clear error");
	cout << "backup log file end" << endl;
}
//read login file
void LogReader::readLoginsFile(void)throw(ReadException)
{
	cout << "read logins file begin..." << endl;
	ifstream ifs(m_loginsFile.c_str(),ios::binary);
	if(ifs)
	{
		LogRec log;
		while(ifs.read((char*)&log,sizeof(log)))
			m_logins.push_back(log);
		if(!ifs.eof())
			throw ReadException();
		ifs.close();
		unlink(m_loginsFile.c_str());
	}
#ifdef _DEBUG
	cout << "login records number: " << m_logins.size() << endl;
#endif
	cout << "read logins file end" << endl;
}
//read backup file
void LogReader::readBackupFile(void)throw(ReadException)
{
	cout << "read backup file begin..." << endl;
	//open backup file
	ifstream ifs(m_backupFile.c_str(),ios::binary);
	if(!ifs)
		throw ReadException("backup file cannot read");
	//calculate number of record
	struct stat st;
	if(stat(m_backupFile.c_str(),&st) == -1)
		throw ReadException("cannot get backup file size");
	int records = st.st_size / 372;
	//read record turn by turn
	for(int i = 0;i < records;++i)
	{
		//login name
		ifs.seekg(i*372,ios::beg);
		char logname[32];
		ifs.read(logname,32);
		ifs.seekg(36,ios::cur);
		pid_t pid;
		ifs.read((char*)&pid,sizeof(pid));
		pid = ntohl(pid);//log file multiple byte integer using network endian
		//log type: 7 means login, 8 means logout
		short type;
		ifs.read((char*)&type,sizeof(type));
		type = ntohs(type);
		//log time
		ifs.seekg(6,ios::cur);
		int logtime;
		ifs.read((char*)&logtime,sizeof(logtime));
		logtime = ntohl(logtime);
		//log ip length
		ifs.seekg(28,ios::cur);
		short len;
		ifs.read((char*)&len,sizeof(len));
		len = ntohs(len);
		//log ip or host name 
		char logip[len + 1];
		ifs.read(logip,len);
		logip[len] = '\0';
#ifdef _DEBUG
		cout << logname << ','
			 << pid     << ','
			 << type << ','
			 << logtime << ','
			 << len << ','
			 <<logip << endl;
#endif //_DEBUG
		if(logname[0] != '.')
		{
			LogRec log;
			strcpy(log.logname,logname);
			strcpy(log.logip,logip);
			log.pid = pid;
			log.logtime = logtime;
			if(type == 7)
				m_logins.push_back(log);
			else if(type == 8)
				m_logouts.push_back(log);
		}
	}
	ifs.close();
#ifdef _DEBUG
	cout << "logins records: " << m_logins.size() << endl;
	cout << "logout records: " << m_logouts.size() << endl;
#endif //_DEBUT
	cout << "read backup file endl"  << endl;
}
//match login and mogout
void LogReader::match(void)
{
	cout << "match begin..." << endl;
	//for each record in logouts to match
	for(list<LogRec>::iterator oit = m_logouts.begin();oit != m_logouts.end();++oit)
	{
		//in logins to find the match
		for(list<LogRec>::iterator iit = m_logins.begin();iit != m_logins.end();++iit)
		{
			if(!strcmp(iit->logname,oit->logname) &&
			   !strcmp(iit->logip, oit->logip) &&
			   iit->pid == oit->pid)
			{
				MLogRec log = { "","",0,0,0,0};
				strcpy(log.logname, oit->logname);
				strcpy(log.logip , oit->logip);
				log.pid = oit->pid;
				log.logintime = iit->logtime;
				log.logouttime = oit->logtime;
				log.durations = log.logouttime - log.logintime;
				m_logs.push_back(log);
				m_logins.erase(iit);
				break;
			}
		}

	}
#ifdef _DEBUG
	cout << "match records: " << m_logs.size() << endl;
#endif //_DEBUG
	cout << "match end" << endl;
}
//save logins file{}
void LogReader::saveLoginsFile(void)throw(SaveException)
{
	cout << "save logins file begin..." << endl;
	if(!m_logins.empty())
	{
		ofstream ofs(m_loginsFile.c_str(),ios::binary);
		if(!ofs)
			throw SaveException();
		while(!m_logins.empty())
		{
			ofs.write((const char*)&m_logins.front(),sizeof(LogRec));
			m_logins.pop_front();
			
		}
		ofs.close();
	}
	cout << "save logsins file end" << endl;
}


