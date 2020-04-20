#include "Cryptor.h"

string &CCryptor::Crypt(const string inString, const string inKey = g_DefKey)
{
	TwoModeFun(inString, inKey, false);
	return m_TempStr;
	//str
}

string &CCryptor::Decrypt(const string inString, const string inKey = g_DefKey)
{
	//m_TempStr.clear();
	TwoModeFun(inString, inKey);
	return m_TempStr;
}

void CCryptor::TwoModeFun(const string inString, const string inKey = g_DefKey, bool inSage = true)
{
	int shift = 0;
	int orig = 0;
	int ref = 0;
	size_t longer = 0;
	size_t couch = 0;
	string::size_type i_cod;
	string::size_type i_text;
	m_TempStr.clear();

	longer = inKey.size() - 1;
	couch = g_Alphabet.size() - 1;
	for (size_t i = 0; i < inString.size(); ++i)
	{
		i_text = g_Alphabet.find(inString[i]);
		i_cod = g_Alphabet.find(inKey[ref]);
		if (i_text != string::npos && i_cod != string::npos)
		{
			if (inSage)
				shift = i_cod;
			else
				shift = couch - i_cod;
			orig = i_text;
			shift += orig;
			if (shift > couch - 1)
				shift -= couch;
			m_TempStr += g_Alphabet[shift];
		}
		else
			m_TempStr += inString[i];
		if (ref == longer)
			ref = 0;
		else
			ref++;
	}
}