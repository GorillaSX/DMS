#include "logreader.h"
#include "logsender.h"
#include <cstring>
#include "consolesender.h"
#include "socketsender.h"
#include "client.h"

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		try
		{
			LogReader reader("./wtmpx","./logins.dat");
			//ConsoleSender sender;
			SocketSender sender("./fail.dat",8888);
			Client client(reader,sender);
			client.dataMine();
		}
		catch(exception& ex)
		{
			cout << ex.what() << endl;
			return -1;
		}
	}
	else if(!strcmp(argv[1],"-g"))
	{
		cout << "GUI not available!" << endl;
	}
	else
	{
		cerr << "usage:" << argv[0] << "[-g]" << endl;
		return -1;
	}
	return 0;

}
