#include "CommonUtils.h"


CommonUtils::CommonUtils()
{
}


CommonUtils::~CommonUtils()
{
}

CDuiString CommonUtils::StringToDuiString(string str)
{
	UINT codePage = CP_ACP;
	LCID lcid = GetSystemDefaultLangID();
	if (lcid == 0x404 || lcid == 0x0c04 || lcid == 0x1404)
	{
		codePage = 936;
	}

	CDuiString dstr;
	int iLen = (int)str.length();
	LPWSTR lpText = new WCHAR[iLen + 1];
	::ZeroMemory(lpText, (iLen + 1) * sizeof(WCHAR));
	::MultiByteToWideChar(codePage, 0, str.c_str(), -1, (LPWSTR)lpText, iLen);
	dstr = lpText;
	delete[] lpText;
	return dstr;
}