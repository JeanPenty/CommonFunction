#ifndef __COMMON_FUNCTIONS_H__
#define __COMMON_FUNCTIONS_H__
#include <string>

std::string WstringToString(std::wstring wstrSrc)
{
	//TODO:
	int nlen = WideCharToMultiByte(CP_ACP, 0, wstrSrc.c_str(), -1, NULL, 0, NULL, NULL);
	if (nlen <= 0)
	{
		return "";
	}

	char* buffer = new char[nlen];
	if (NULL == buffer)
	{
		return "";
	}

	WideCharToMultiByte(CP_ACP, 0, wstrSrc.c_str(), -1, buffer, nlen, NULL, NULL);

	std::string strDes = buffer;
	delete []buffer;
	return strDes;
}

std::wstring StringToWstring(std::string strSrc)
{
	//TODO:
	int len;
	int slen = (int)strSrc.length()+1;
	len = MultiByteToWideChar(CP_ACP, 0, strSrc.c_str(), slen, 0,0);
	if (len <= 0)
	{
		return _T("");
	}

	wchar_t* buffer = new wchar_t[len];
	if (NULL == buffer)
	{
		return _T("");
	}

	MultiByteToWideChar(CP_ACP, 0, strSrc.c_str(), slen, buffer, len);

	std::wstring wstrDes = buffer;
	delete[] buffer;
	return wstrDes;
}

void Utf16ToUtf8(const std::wstring& wstrUtf16, std::string& strUtf8)
{
	//TODO:
	int len = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)wstrUtf16.c_str(), -1, NULL, 0, NULL, NULL); 
	char *pszUtf8=new char[len + 1];
	memset(pszUtf8, 0, len + 1);
	WideCharToMultiByte (CP_UTF8, 0, (LPCWSTR)wstrUtf16.c_str(), -1, pszUtf8, len, NULL,NULL);

	strUtf8 = pszUtf8;
	delete[] pszUtf8;
}

void Utf8ToUtf16(const std::string& strUtf8, std::wstring& wstrUtf16)
{
	//TODO:
	int len=MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)strUtf8.c_str(), -1, NULL,0);
	wchar_t * pUtf16 = new wchar_t[len+1];
	memset(pUtf16, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)strUtf8.c_str(), -1, (LPWSTR)pUtf16, len);

	wstrUtf16 = pUtf16;
	delete[] pUtf16;
}

void GBKToUtf8(std::string& strGBKUtf8)
{
	//TODO: GBK->utf16, utf16->utf8
	int len=MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strGBKUtf8.c_str(), -1, NULL,0);
	wchar_t * pUtf16 = new wchar_t[len+1];
	memset(pUtf16, 0, len * 2 + 2);
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strGBKUtf8.c_str(), -1, (LPWSTR)pUtf16, len);

	len = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)pUtf16, -1, NULL, 0, NULL, NULL); 
	char *pUtf8=new char[len + 1];
	memset(pUtf8, 0, len + 1);
	WideCharToMultiByte (CP_UTF8, 0, (LPCWSTR)pUtf16, -1, pUtf8, len, NULL,NULL);

	strGBKUtf8 = pUtf8;
	delete[] pUtf8;
	delete[] pUtf16;
}

void Utf8ToGBK(std::string& strUtf8GBK)
{
	//TODO:utf8->utf16, utf16->GBK
	int len=MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)strUtf8GBK.c_str(), -1, NULL,0);
	wchar_t * pUtf16 = new wchar_t[len+1];
	memset(pUtf16, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)strUtf8GBK.c_str(), -1, (LPWSTR)pUtf16, len);

	len = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pUtf16, -1, NULL, 0, NULL, NULL); 
	char *pGBK=new char[len + 1];
	memset(pGBK, 0, len + 1);
	WideCharToMultiByte (CP_ACP, 0, (LPCWSTR)pUtf16, -1, pGBK, len, NULL,NULL);

	strUtf8GBK = pGBK;
	delete[] pGBK;
	delete[] pUtf16;
}

unsigned char ToHex(unsigned char x)
{
	//TODO:
	return  x > 9 ? x + 55 : x + 48; 
}

unsigned char FromHex(unsigned char x)   
{   
	//TOOD:
	unsigned char y;  
	if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;  
	else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;  
	else if (x >= '0' && x <= '9') y = x - '0';  
	else assert(0);  
	return y;  
}

std::string UrlEncode(const std::string& str)  
{  
	//TODO:
	std::string strTemp = "";  
	size_t length = str.length();  
	for (size_t i = 0; i < length; i++)  
	{  
		if (isalnum((unsigned char)str[i]) ||   
			(str[i] == '-') ||  
			(str[i] == '_') ||   
			(str[i] == '.') ||
			(str[i] == '/') ||
			(str[i] == ':') ||
			(str[i] == '&') ||
			(str[i] == '?') ||
			(str[i] == '=') ||
			(str[i] == '~'))  
			strTemp += str[i];  
		else if (isspace(str[i]))  
			strTemp += "%20";  
		else  
		{  
			strTemp += '%';  
			strTemp += ToHex((unsigned char)str[i] >> 4);  
			strTemp += ToHex((unsigned char)str[i] % 16);  
		}  
	}  
	return strTemp;  
}

std::string UrlDecode(const std::string& str)  
{  
	//TODO:
	std::string strTemp = "";  
	size_t length = str.length();  
	for (size_t i = 0; i < length; i++)  
	{  
		if (str[i] == '+') strTemp += ' ';  
		else if (str[i] == '%')  
		{  
			assert(i + 2 < length);  
			unsigned char high = FromHex((unsigned char)str[++i]);  
			unsigned char low = FromHex((unsigned char)str[++i]);  
			strTemp += high*16 + low;  
		}  
		else strTemp += str[i];  
	}  
	return strTemp;  
} 

/*
@	split string by char or other string
@	add by yangjinpeng
@	time: 2016-12-29
*/
std::list<std::string> StrSplit(std::string strSrc, std::string separator)  
{  
	std::list<std::string> result_list;  
	int cutAt;  
	while( (cutAt = strSrc.find_first_of(separator)) != strSrc.npos )  
	{  
		if(cutAt > 0)  
		{  
			result_list.push_back(strSrc.substr(0, cutAt));  
		}  
		strSrc = strSrc.substr(cutAt + 1);  
	}  
	if(strSrc.length() > 0)  
	{  
		result_list.push_back(strSrc);  
	}  
	return result_list;  
}

#endif