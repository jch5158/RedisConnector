#pragma once

#include "CRedisConnector.h"

class CTLSRedisConnector
{
public:

	CTLSRedisConnector(void)
		:mTLSIndex(UINT_MAX)
	{
		CRedisConnector::CallWSAStartup();

		setTLSIndex();
	}

	~CTLSRedisConnector(void)
	{
		freeTLSIndex();

		CRedisConnector::CallWSACleanup();
	}

	CTLSRedisConnector(const CTLSRedisConnector&) = delete;
	CTLSRedisConnector& operator=(const CTLSRedisConnector&) = delete;

	void Connect(void)
	{	
		getRedisLibrary()->Connect();

		return;
	}

	bool Connect(wchar_t* pConnectIP, unsigned short connectPort)
	{
		CRedisConnector* pRedisConnector = getRedisLibrary();

		if (pRedisConnector->Connect(pConnectIP, connectPort) == false)
			return false;

		return true;
	}

	void Disconnect(void)
	{
		getRedisLibrary()->Disconnect();

		return;
	}

	bool Set(const char* pKey, const char* pValue)
	{
		CRedisConnector* pRedisConnector = getRedisLibrary();
		
		if (pRedisConnector->Set(pKey, pValue) == false)
			return false;

		return true;
	}

	bool SetEx(const char* pKey, long long seconds, const char* pValue)
	{
		CRedisConnector* pRedisConnector = getRedisLibrary();

		if (pRedisConnector->SetEx(pKey, seconds, pValue) == false)
			return false;

		return true;
	}


	bool Set(const char* pKey, long long value)
	{
		CRedisConnector* pRedisConnector = getRedisLibrary();

		if (pRedisConnector->Set(pKey, value) == false)
			return false;

		return true;
	}

	bool SetEx(const char* pKey, long long seconds, long long value)
	{
		CRedisConnector* pRedisConnector = getRedisLibrary();

		if (pRedisConnector->SetEx(pKey, seconds, value) == false)
			return false;

		return true;
	}


	bool Set(long long key, long long value)
	{
		CRedisConnector* pRedisConnector = getRedisLibrary();

		if (pRedisConnector->Set(key, value) == false)
			return false;

		return true;
	}

	bool SetEx(long long key, long long seconds, long long value)
	{
		CRedisConnector* pRedisConnector = getRedisLibrary();

		if (pRedisConnector->SetEx(key, seconds, value) == false)
			return false;

		return true;
	}



	bool Set(long long key, const char* pValue)
	{
		CRedisConnector* pRedisConnector = getRedisLibrary();

		if (pRedisConnector->Set(key, pValue) == false)
			return false;

		return true;
	}


	bool SetEx(long long key, long long seconds, const char* pValue)
	{
		CRedisConnector* pRedisConnector = getRedisLibrary();

		if (pRedisConnector->SetEx(key, seconds, pValue) == false)
			return false;

		return true;
	}



	bool GetValue(const char* pKey, long long *pValue)
	{
		if (getRedisLibrary()->GetValue(pKey, pValue) == false)
			return false;

		return true;
	}


	bool GetValue(long long key, long long* pValue)
	{
		if (getRedisLibrary()->GetValue(key, pValue) == false)
			return false;

		return true;
	}

	bool RemoveKey(long long key)
	{
		if (getRedisLibrary()->RemoveKey(key) == false)
			return false;

		return true;
	}

	bool RemoveKey(const char* pKey)
	{
		if (getRedisLibrary()->RemoveKey(pKey) == false)
			return false;

		return true;
	}

	bool GetString(const char* pKey, std::string &value)
	{
		if (getRedisLibrary()->GetString(pKey, value) == false)
			return false;

		return true;
	}

	bool GetString(long long key, std::string &value)
	{
		if (getRedisLibrary()->GetString(key, value) == false)
			return false;

		return true;
	}

	bool GetConnectFlag(void)
	{
		getRedisLibrary()->GetConnectFlag();
	}


	bool CompareToken(long long key, const std::string &token)
	{
		return getRedisLibrary()->CompareToken(key, token);
	}

	bool CompareToken(const char* pKey, const std::string &token)
	{	
		return getRedisLibrary()->CompareToken(pKey, token);
	}

private:

	void setTLSIndex(void)
	{
		if (mTLSIndex != UINT_MAX)
			return;

		mTLSIndex = TlsAlloc();
		if (mTLSIndex == TLS_OUT_OF_INDEXES)
		{
			CSystemLog::GetInstance()->Log(true, CSystemLog::eLogLevel::LogLevelError, L"CTLSRedisConnector", L"[setTLSIndex] GetLastError : %d", GetLastError());

			CCrashDump::Crash();
		}

		return;
	}

	void freeTLSIndex(void)
	{
		if (mTLSIndex == UINT_MAX)
			return;

		if (TlsFree(mTLSIndex) == false)
		{
			CSystemLog::GetInstance()->Log(true, CSystemLog::eLogLevel::LogLevelError, L"CTLSRedisConnector", L"[freeTLSIndex] GetLastError : %d", GetLastError());

			CCrashDump::Crash();
		}

		return;
	}

	CRedisConnector* getRedisLibrary(void)
	{
		CRedisConnector* pRedisConnector = (CRedisConnector*)TlsGetValue(mTLSIndex);
		if (pRedisConnector == nullptr)
		{
			pRedisConnector = new CRedisConnector;

			TlsSetValue(mTLSIndex, (void*)pRedisConnector);
		}

		return pRedisConnector;
	}

	unsigned int mTLSIndex;
};

