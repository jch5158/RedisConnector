#include "stdafx.h"
#include "CRedisConnector.h"
#include "CTLSRedisConnector.h"

CTLSRedisConnector redisLibrary;

unsigned __stdcall WorkerThread(void* pParam)
{
	redisLibrary.Connect();

	std::string str;

	for (;;)
	{
		redisLibrary.Set("1", "2");
	
		redisLibrary.GetString("1", str);

		std::cout << str << "\n";

		Sleep(100);
	}

	redisLibrary.Disconnect();

	return 1;
}


int main()
{
	_beginthreadex(nullptr, 0, (_beginthreadex_proc_type)WorkerThread, nullptr, 0, nullptr);
	_beginthreadex(nullptr, 0, (_beginthreadex_proc_type)WorkerThread, nullptr, 0, nullptr);
	_beginthreadex(nullptr, 0, (_beginthreadex_proc_type)WorkerThread, nullptr, 0, nullptr);

	Sleep(INFINITE);

	return 1;
}

