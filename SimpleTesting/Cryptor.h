#pragma once
#include <string>
using std::string;

const string g_DefKey = "siarheikapkovich";

class CCryptor
{
public:
	static CCryptor &Instance()
	{
		static CCryptor _instance;
		return _instance;
	}
	string &Crypt(const string inString, const string inKey = g_DefKey);
	string &Decrypt(const string inString, const string inKey = g_DefKey);
private:
	string m_TempStr;
	const string g_Alphabet = " 0@1#2$3%4^5&6*7=8-9+АаБбВвГгДдЕеЁёЖжЗзИиКкЛлМмНнОоПпРрСсТтУуФфХхЪъЦцЧчЬьШшЩщЫыЭэЮюЯяЙйAaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
};