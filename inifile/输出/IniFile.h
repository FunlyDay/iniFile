#pragma once

#ifdef _DLL_EXPORTS
#define DLL_API _declspec(dllexport)
#else
#define DLL_API _declspec(dllimport)
#endif
class DLL_API CIniFile
{
public:
	CIniFile();
	virtual ~CIniFile();
private:

	TCHAR chFile[1024];

public:
	bool			SetInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, int iData);
	bool			SetString(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpString);
	bool			SetDouble(LPCTSTR lpAppName, LPCTSTR lpKeyName, double dbData);
	bool			SetBool(LPCTSTR lpAppName, LPCTSTR lpKeyName, bool bData);

	unsigned int	GetInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, int iDefault=0);
	void			GetString(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPTSTR lpString, LPCTSTR lpDefault=_T(""));
	double			GetDouble(LPCTSTR lpAppName, LPCTSTR lpKeyName, double dbDefault=0);
	bool			GetBool(LPCTSTR lpAppName, LPCTSTR lpKeyName, bool bDefault=false);
public:
	bool		SetFileName(LPCTSTR lpFileName);
	void		GetFileName(TCHAR* chName);

};

