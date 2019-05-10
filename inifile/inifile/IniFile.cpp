
#include "stdafx.h"
#define _DLL_EXPORTS
#include "IniFile.h"
#include <iostream>
#include <fstream>
#include"lock.h"


using namespace::std;
CIniFile::CIniFile()
{
}


CIniFile::~CIniFile()
{
}

bool CIniFile::SetFileName(LPCTSTR lpFileName)
{
	int ret = false;
	ifstream inf;
	ofstream ouf;
	inf.open(lpFileName, ios::out);
	if (!inf)
	{
		inf.close();
		wcout << _T("not file name as ") << lpFileName << _T(" in this path ,create file now." )<< endl;
		ouf.open(lpFileName);
		if (ouf)
		{
			wcout << _T("Created successfully!" )<< endl;
			ret = true;
		}
		ouf.close();
	}
	else
	{
		inf.close();
		ret = true;
	}
	if (ret)
	{
		AutoLock lock;
		_tcscpy_s(chFile,1024,lpFileName);
	}
	return ret;
}

void CIniFile::GetFileName(TCHAR* chName)
{
	AutoLock lock;

	_tcscpy_s(chName, 1024, chFile);

}

bool CIniFile::SetString(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpString)
{
	AutoLock lock;
	return WritePrivateProfileString(lpAppName, lpKeyName, lpString, chFile);
}

bool CIniFile::SetInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, int iData)
{
	AutoLock lock;
	TCHAR chTmp[1024];
	wsprintf(chTmp, _T("%d"), iData);
	return WritePrivateProfileString(lpAppName, lpKeyName, chTmp, chFile);
}


bool CIniFile::SetDouble(LPCTSTR lpAppName, LPCTSTR lpKeyName, double dbData)
{
	AutoLock lock;
	TCHAR chTmp[1024];
#ifdef UNICODE
	swprintf_s(chTmp, 100,_T("%lf"), dbData);
#else
	sprintf_s(chTmp,100, _T("%lf"), dbData);
#endif // UNICODE

	
	return WritePrivateProfileString(lpAppName, lpKeyName, chTmp, chFile);
}

bool CIniFile::SetBool(LPCTSTR lpAppName, LPCTSTR lpKeyName, bool bData)
{
	AutoLock lock;
	TCHAR chTmp[10];
	wsprintf(chTmp, _T("%d"), bData);
	return WritePrivateProfileString(lpAppName, lpKeyName, chTmp, chFile);
}

unsigned int CIniFile::GetInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, int iDefault)
{
	AutoLock lock;
	unsigned int iTmp = GetPrivateProfileInt(lpAppName, lpKeyName, iDefault, chFile);
	if (iTmp == iDefault)
		this->SetInt(lpAppName, lpKeyName, iDefault);
	return iTmp;
}

void CIniFile::GetString(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPTSTR lpString, LPCTSTR lpDefault)
{
	AutoLock lock;
	GetPrivateProfileString(lpAppName, lpKeyName, lpDefault, lpString, 1024, chFile);
}

double CIniFile::GetDouble(LPCTSTR lpAppName, LPCTSTR lpKeyName, double dbDefault)
{
	double dbGet;
#ifdef UNICODE
	WCHAR chGet[100];
	WCHAR chDef[100];
	swprintf_s(chDef,100, _T("%lf"), dbDefault);
	GetString(lpAppName, lpKeyName, chGet, chDef);
	dbGet = _wtof(chGet);
#else
	char chGet[100];
	char chDef[100];
	sprintf_s(chDef, 100,_T("%lf"), dbDefault);
	GetString(lpAppName, lpKeyName, chGet, chDef);
	dbGet = atof(chGet);
#endif

	
	if (abs(dbGet- dbDefault)<=0.001)
	{
		SetDouble(lpAppName, lpKeyName, dbDefault);
	}
	return dbGet;
}

bool CIniFile::GetBool(LPCTSTR lpAppName, LPCTSTR lpKeyName, bool bDefault)
{
	return GetInt(lpAppName, lpKeyName, bDefault);
}


