#include <algorithm>
#include "Tester.h"

//string g_TempStr = "";
int g_Ball = 0;
string alphabet = " 0@1#2$3%4^5&6*7=8-9+�����������娸����������������������������������������������������AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";

string Cryptor(string code, string text, bool sage)
{
	int shift = 0;
	int orig = 0;
	int ref = 0;
	int longer = 0;
	int couch = 0;
	string str = "";
	string::size_type i_cod;
	string::size_type i_text;

	longer = (int)code.size() - 1;
	couch = (int)alphabet.size() - 1;
	for(int i = 0; i < (int)text.size(); i++)
	{
		i_text = alphabet.find(text[i]);
		i_cod = alphabet.find(code[ref]);
		if(i_text != string::npos && i_cod != string::npos)
		{
			if(sage)
				shift = (int)i_cod;
			else
				shift = couch - (int)i_cod;
            orig = (int)i_text;
			shift += orig;
			if (shift > couch - 1) 
				shift -= couch;
			str += alphabet[shift];
		}
		else
			str += text[i];
		if (ref == longer) 
			ref = 0;
		else 
			ref++;		
	}
	return str;
}
MyC_Tester::MyC_Tester()
{
	//___ ����� �� ���������
	m_State = TPS_NULL; 
	//___ ������ ����
	m_CurrentTest = 0;
	//___ ������ ������
	m_CurQuwest = 0;
	m_StrStatistik = "";
}
/*
//***
//_ ������� ��������� �� ����� ��������� ����������
//_ ��������� ��� �����
//_ � ������ �������, ���������� false.
//***
bool MyC_Tester::GetTestInfo(const char *file, MyS_Info *info)
{
	//___ ��������� ����������
	ifstream FileStream;				// �������� �����
	string TempStr;
	string SubStr;
	string::size_type idx;
	//___ ��������� ����
	FileStream.open(file);
	if(FileStream.is_open())
	{
		while(getline(FileStream, TempStr))
		{
			//___ ���� �����������
			idx = TempStr.find('#'); // ���������, ������ ����������� ������� �������?
			//___ ���� ������� 
			if(idx != string::npos)
			{
				//___ ��������� ������
				SubStr = SubStr = TempStr.substr(0, idx);
				if(SubStr == "TEST")
				{
					//___ ������� ���������
					*info->m_Name = TempStr.substr(idx + 1);
				}
				if(SubStr == "QUWESTCOUNT")
				{
					//___ ���������� �������� � ������
					*info->m_QuwCount = atoi(TempStr.substr(idx + 1).c_str());
				}
				//___ ��
				if(SubStr == "MOTVETS")
				{
					if(TempStr.substr(idx + 1) == "TRUE")
						*info->m_MultiQ = true;
					else
						*info->m_MultiQ = false;
				}
			}
		}
		FileStream.close();
	}
	else
	{
		//___ ������ ��� ��������
		return false;
	}
	//___ ��������� ����
	FileStream.close();
	return true;
}
*/
//***
//_ ������ 2. ����� ���������. ������ ������� �������� � ������� �����, ���� ���� ���������� ���� � ������.
//_ �������� ����� �����. �� �������������.
//_ ��������� ��� ����� (����), ����� ������, ���������� �������� ��� ��������� ������������, ���� ���������� ������������.
//_ � ������ ������� ��������, ���������� "OK"
//_ � ������ �������, ���������� ������ c ��������� ������ ���� "UNKNOW".
//***
bool MyC_Tester::LoadTest(const char *file)
{
	//___ ��������� ����������
	ifstream FileStream;				// �������� �����
	MyS_Test TempTest;					// ��������� ������ �����
	MyS_Quwest TempQw;					// ��������� ������ �������
	string TempStr;						// ���������� ������ �� �����
	string SubStr;						// ������ � ����������� ����������� ������
	string::size_type idx;				// ������� ������� � ������
	vector<string> FileStr;				// ���������� ����� ����� ��� ����������� �������
	vector<string>::iterator pos;		// �������� �������

	//___ ��������� ����
	FileStream.open(file);
	//___ ��������� �� ������������
	if(FileStream.is_open())
	{
		while(getline(FileStream, TempStr))
		{
			TempStr = Cryptor("�������� ������ ����������", TempStr, 1);
			//___ ���� ����������� (� ����������� �� ������)
			idx = TempStr.find('#'); // ���������, ������ ����������� ������� �������?
			//___ ���� ������� 
			if(idx != string::npos)
			{
				FileStr.push_back(TempStr);
			}
		}
		FileStream.close();
	}
	else
	{
		//___ ��������
		SubStr = "�� ������� ������� ��������� ����";
		return false;
	}
	//___ ������ ������ ��������� �����
	pos = FileStr.begin();
	while(pos != FileStr.end())
	{
		TempStr = *pos;
		pos++;
		//___ ���� ������� �����������
		idx = TempStr.find('#'); 
		//___ ����� ����������������
		if(idx != string::npos)
		{
			//___ ��������� ������
			SubStr = SubStr = TempStr.substr(0, idx);
			if(SubStr == "TEST")
			{
				//___ ������� ���������
				TempTest.m_Info.m_Name = TempStr.substr(idx + 1);
			}
			if(SubStr == "QUWESTCOUNT")
			{
				//___ ���������� �������� � ������
				TempTest.m_Info.m_QuwCount = atoi(TempStr.substr(idx + 1).c_str());
			}
			if(SubStr == "MOTVETS")
			{
				if(TempStr.substr(idx + 1) == "TRUE")
					TempTest.m_Info.m_MultiQ = true;
				else
					TempTest.m_Info.m_MultiQ = false;
			}
		}
		else
		{
		}
	}
	//___ �������
	pos = FileStr.begin();
	while(pos != FileStr.end())
	{
		TempStr = *pos;
		pos++;
		//___ ���� ������� �����������
		idx = TempStr.find('#'); 
		//___ ����� ����������������
		if(idx != string::npos)
		{
			//___ ��������� ������
			SubStr = TempStr.substr(0, idx);
			if(SubStr == "MQUWEST" && !TempTest.m_Info.m_MultiQ) 
				SubStr = "";
			//___ ������������ ������� � ������ �������
			if(SubStr == "SQUWEST" || SubStr == "MQUWEST")
			{
				//___ ���������� �������
				TempQw.m_Quwest = TempStr.substr(idx + 1);
				//___ ������ �� ������
				int i = 0;
				while(i < 8)
				{
					if(pos == FileStr.end()) break;
					TempStr = *pos;
					//___ ���� ������� �����������
					idx = TempStr.find('#');
					if(idx != string::npos)
					{
						//___ ��������� ����� ������
						SubStr = TempStr.substr(0, idx);
						//___ �������� ����������� �����
						if(SubStr.size() <= 3)
						{
							TempQw.m_Otvet[i] = TempStr.substr(idx + 1);
							TempQw.m_Valid[i] = atoi(SubStr.c_str());
							pos++;
						}
						else
						{
							while(i < 8)
							{
                                TempQw.m_Otvet[i] = "";
								TempQw.m_Valid[i] = 0;
								i++;
							}
							break;
						}
					}
					else
					{
						//___ ERROR
						break;
					}
					i++;
				}
				//if(SubStr != "OK") break;
				//___ ��������� ������
				TempTest.m_AllQuwests.push_back(TempQw);
			}
		}
		else
		{
			//___ ERROR
			break;
		}
	}
	
	//___ ��� ����� ����������
	m_Tests.push_back(TempTest);
	m_CurrentTest = 1;
	m_State = TPS_TEST;
	//___ ���������� � ������������ �����
	GenerateBilet();
	return true;
}
//***
//_ ������� ���������� ����� ��������� �����
//_ ��������� ��� �����
//_ � ������ �������, ���������� false.
//***
void MyC_Tester::GenerateBilet()
{
	vector<int> Checker;				// ��������� ������ ��������, ��� �������� ����������
	int max_rnd = static_cast<int>(m_Tests[m_CurrentTest - 1].m_AllQuwests.size());
	int rnd = 0;
	int count_q = 0;
	
	//___ �������� ���������� ��������
	if(m_Tests[m_CurrentTest - 1].m_Info.m_QuwCount <= 0)
	{
		//___ �������� �� ���������
		m_Tests[m_CurrentTest - 1].m_Info.m_QuwCount = 3;
	}
	count_q = m_Tests[m_CurrentTest - 1].m_Info.m_QuwCount;
	//___ ����������
	m_Tests[m_CurrentTest - 1].m_CyrrentBilet.clear();
	m_Tests[m_CurrentTest - 1].m_CyrrentBilet.resize(count_q);
	Checker.resize(count_q);
	fill(Checker.begin(), Checker.end(), -1);
	//___ ��������� ����� ���, ���� ������ ����������
	while(count_q != 0)
	{
		//___ ���������� �����, �� ������� ���������� ��������
		rnd = rand() % max_rnd;
		//___ ���������, ������������� ���� ������ ��� ���
		if(0 == count(Checker.begin(), Checker.end(), rnd))
		{
			//___ ���� ���, ������ ��� �� ������������
			Checker[count_q - 1] = rnd;
			//___ ������� ������ � �����
			m_Tests[m_CurrentTest - 1].m_CyrrentBilet[count_q - 1] = m_Tests[m_CurrentTest - 1].m_AllQuwests[rnd];
			//___ ��������� ���������� ��������������
			count_q--;
		}
	}
	m_CurQuwest = 1;

	g_Ball = 0;
	m_StrStatistik = "";
}
void MyC_Tester::TestParam(MyS_Info *param, bool getset)
{
	if(getset)
	{
		//___ �������� ����������
		*param = m_Tests[m_CurrentTest - 1].m_Info;
	}
	else
	{
		//___ �������� ����������
		m_Tests[m_CurrentTest - 1].m_Info = *param;
		this->Restart();
	}
}
//***
//_ �������� �������
//_ � ������ �������� (��������������), ��������� ������ � �������� ������.
//_ � ������ ������������ ��������� ������� ������, ��������� ��������� ��������� ��������.
//_ � ������ �������, ���������� false.
//***
bool MyC_Tester::NextQuwest(MyS_Quwest *param)
{
	char szBuf[32];
	MyS_Quwest temp;

	if(!this->IsValid())
	{
		return false;
	}

	if(m_CurQuwest == 0)
	{
		return false;
	}

	switch(m_State)
	{
		case TPS_CREATE:
			return false;
		case TPS_TEST:
			// ����� ������ �����
			if(m_CurQuwest <= 1 + (int)m_Tests[m_CurrentTest - 1].m_CyrrentBilet.size()) //======================
			{
				//___ ����� ��������� �����
				if(m_CurQuwest != 0 && m_CurQuwest != 1)
				{
					int tmp;
					tmp = 0;
					for(int i = 0; i < 8; i++)
					{
						if((m_Tests[m_CurrentTest - 1].m_CyrrentBilet[m_CurQuwest - 2].m_Valid[i] != 0) && (param->m_Valid[i] != 0))
						{
							tmp += m_Tests[m_CurrentTest - 1].m_CyrrentBilet[m_CurQuwest - 2].m_Valid[i];
						}
						else
						{
							if((m_Tests[m_CurrentTest - 1].m_CyrrentBilet[m_CurQuwest - 2].m_Valid[i] == 0) && (param->m_Valid[i] != 0))
							{
								tmp = 0;
								i = 8;
							}
						}
					}
					if(tmp != 0)
					{
						tmp = (tmp == 99) ? 100 : tmp;
						g_Ball += tmp;
						m_StrStatistik += "\n������ �";
						_itoa_s(m_CurQuwest - 1, szBuf, 10);
						m_StrStatistik += szBuf;
						m_StrStatistik += ": ";
						_itoa_s(tmp, szBuf, 10);
						m_StrStatistik += szBuf;
						m_StrStatistik += "% - �����";
						m_StrStatistik += '\n' + m_Tests[m_CurrentTest - 1].m_CyrrentBilet[m_CurQuwest - 2].m_Quwest;
						m_StrStatistik += '\n';
					}
					else
					{
						m_StrStatistik += "\n������ �";
						_itoa_s(m_CurQuwest - 1, szBuf, 10);
						m_StrStatistik += szBuf;
						m_StrStatistik += ": ";
						m_StrStatistik += "- �������";
						m_StrStatistik += '\n' + m_Tests[m_CurrentTest - 1].m_CyrrentBilet[m_CurQuwest - 2].m_Quwest;
						m_StrStatistik += '\n';
					}
				}
				if(m_CurQuwest != 1 + (int)m_Tests[m_CurrentTest - 1].m_CyrrentBilet.size())
				{
                    *param = m_Tests[m_CurrentTest - 1].m_CyrrentBilet[m_CurQuwest - 1];
					m_CurQuwest++;
					return true;
				}
				else
				{
					//___ ���� �������� ������� ����������
					// �� ��� DV m_StrStatistik += '\n' + g_TempStr;
					string temp = m_StrStatistik;
					g_Ball = g_Ball / 10;
					_itoa_s(g_Ball, szBuf, 10);
					m_StrStatistik = "��� ��������� - ";
					m_StrStatistik += szBuf;
					m_StrStatistik += "%.\n";
					m_StrStatistik += temp;
					m_CurQuwest = 0;
					return false;
				}
			}
			else
			{
				//___ ���� �������� ������� ����������
				m_CurQuwest = 0;
				return false;
			}
			break;
		default:
			break;
	}
	return false;
}



void MyC_Tester::Restart()
{
	if(!this->IsValid()) return;
	//___ ����� �����
	m_State = TPS_TEST; 
	//___ ������ ����
	m_CurrentTest = (this->IsValid())?1:0;
	//___ ������ ������
	m_CurQuwest = 0;
	//___ �������� ����������
	m_StrStatistik = "";
	//___ ���������� ����� �����
	this->GenerateBilet();
}

void MyC_Tester::Reset()
{
	//___ ����� �� ���������
	m_State = TPS_NULL; 
	//___ ������ ����
	m_CurrentTest = 0;
	//___ ������ ������
	m_CurQuwest = 0;
	
	m_StrStatistik = "";
	m_Tests.clear();
}

string MyC_Tester::GetStatistic(void)
{
	return m_StrStatistik;
}

bool MyC_Tester::IsValid(void)
{
	if(!m_Tests.empty() && !m_Tests[m_CurrentTest - 1].m_CyrrentBilet.empty()) return true;
	return false;
}

string MyC_Tester::Crypt(string Text)
{
    return Text;
}

string MyC_Tester::Uncrypt(string Text)
{
	return Text;
}
