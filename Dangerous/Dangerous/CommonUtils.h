#pragma once
#include "UIlib.h"
using namespace DuiLib;
#include<string>
using namespace std;

class CommonUtils
{
public:
	CommonUtils();
	~CommonUtils();
public:
	static CDuiString StringToDuiString(string str);
	static CDuiString IntToDuiString(int para)
	{
		CDuiString dstr;
		char c[10];
		_itoa_s(para, c, 10);
		dstr = StringToDuiString(string(c));
		return dstr;
	}

	static string DuiStringToString(CDuiString dstr)
	{

		UINT codePage = CP_ACP;
		LCID lcid = GetSystemDefaultLangID();
		if (lcid == 0x404 || lcid == 0x0c04 || lcid == 0x1404)
		{
			codePage = 936;
		}
		char* pszDst;
		int nLen = WideCharToMultiByte(codePage, 0, dstr.GetData(), -1, NULL, 0, NULL, NULL);
		pszDst = new char[nLen];
		WideCharToMultiByte(codePage, 0, dstr.GetData(), -1, pszDst, nLen, NULL, NULL);
		pszDst[nLen - 1] = 0;
		//strcpy_s(str->c_str(),pszDst);
		string str = string(pszDst);
		delete[] pszDst;
		return str;
	}

	static int DuiStringToInt(CDuiString dstr)
	{
		string str = DuiStringToString(dstr);
		int sb = atoi(str.c_str());
		return sb;
	}

	//UTF-8转Unicode 
	static std::wstring Utf82Unicode(const std::string& utf8string)
	{
		int widesize = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, NULL, 0);
		if (widesize == ERROR_NO_UNICODE_TRANSLATION)
		{
			throw std::exception("Invalid UTF-8 sequence.");
		}
		if (widesize == 0)
		{
			throw std::exception("Error in conversion.");
		}
		std::vector<wchar_t> resultstring(widesize);
		int convresult = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, &resultstring[0], widesize);
		if (convresult != widesize)
		{
			throw std::exception("La falla!");
		}
		return std::wstring(&resultstring[0]);
	}

	//unicode 转为 ascii 
	static string WideByte2Acsi(wstring& wstrcode)
	{
		int asciisize = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, NULL, 0, NULL, NULL);
		if (asciisize == ERROR_NO_UNICODE_TRANSLATION)
		{
			throw std::exception("Invalid UTF-8 sequence.");
		}
		if (asciisize == 0)
		{
			throw std::exception("Error in conversion.");
		}
		std::vector<char> resultstring(asciisize);
		int convresult = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, &resultstring[0], asciisize, NULL, NULL);
		if (convresult != asciisize)
		{
			throw std::exception("La falla!");
		}
		return std::string(&resultstring[0]);
	}

	//utf-8 转 ascii 
	static string UTF_82ASCII(string& strUtf8Code)
	{
		string strRet("");
		//先把 utf8 转为 unicode 
		wstring wstr = Utf82Unicode(strUtf8Code);
		//最后把 unicode 转为 ascii 
		strRet = WideByte2Acsi(wstr);
		return strRet;
	}

	//ascii 转 Unicode 
	static wstring Acsi2WideByte(string& strascii)
	{
		int widesize = MultiByteToWideChar(CP_ACP, 0, (char*)strascii.c_str(), -1, NULL, 0);
		if (widesize == ERROR_NO_UNICODE_TRANSLATION)
		{
			throw std::exception("Invalid UTF-8 sequence.");
		}
		if (widesize == 0)
		{
			throw std::exception("Error in conversion.");
		}
		std::vector<wchar_t> resultstring(widesize);
		int convresult = MultiByteToWideChar(CP_ACP, 0, (char*)strascii.c_str(), -1, &resultstring[0], widesize);
		if (convresult != widesize)
		{
			throw std::exception("La falla!");
		}
		return std::wstring(&resultstring[0]);
	}

	//Unicode 转 Utf8 
	static std::string Unicode2Utf8(const std::wstring& widestring)
	{
		int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);
		if (utf8size == 0)
		{
			throw std::exception("Error in conversion.");
		}
		std::vector<char> resultstring(utf8size);
		int convresult = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);
		if (convresult != utf8size)
		{
			throw std::exception("La falla!");
		}
		return std::string(&resultstring[0]);
	}

	//ascii 转 Utf8 
	static string ASCII2UTF_8(string& strAsciiCode)
	{
		string strRet("");
		//先把 ascii 转为 unicode 
		wstring wstr = Acsi2WideByte(strAsciiCode);
		//最后把 unicode 转为 utf8 
		strRet = Unicode2Utf8(wstr);
		return strRet;
	}

};

