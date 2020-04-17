#include <string>
#include <vector>
#include <fstream>

using namespace std;

enum MyE_TPS {TPS_NULL, TPS_TEST, TPS_MULTITEST, TPS_ONEQUWEST, TPS_CREATE, TPS_DEBUG}; // Test Parameter Set

struct MyS_Quwest
{
	string m_Quwest;							// ������
	string m_Otvet[8];							// ������
	int    m_Valid[8];							// ���� ������������ ������ ��� ���������� ������
};

struct MyS_Info
{
	string m_Name;								// ��� ����� (�������� ��������)
	int m_QuwCount;								// ���������� �������� � ������, ��� ��������� ������������
	int m_Time;									// ����� �� ���� ������ � ��������
	int m_BiletCount;							// ���������� �������
	bool m_RandBilet;							// ���� ���������� ������������ ������
	bool m_MultiQ;								// ��������� ��� ��� ������� � ������������� ������� (��)
};

struct MyS_Test
{
	MyS_Info m_Info;							// ���������� � �����
	vector<MyS_Quwest> m_AllQuwests;			// ��� �������
	vector<MyS_Quwest> m_CyrrentBilet;			// �������� �����
};

class MyC_Tester
{
	//___ �������� ����� ������
	//string m_Error;
	MyE_TPS m_State;										// ����� ������
	int m_CurrentTest;										// ����� ��������� �����
	int m_CurQuwest;										// ������� ������
	string m_StrStatistik;									// ���� ��������� ����������
	vector<MyS_Test> m_Tests;								// ��������� ������
	//___ �������� ������ ������
	void GenerateBilet(void);
public:
	string Uncrypt(string Text);
	string Crypt(string Text);

	MyC_Tester();																		// ����������� �� ���������
	bool LoadTest(const char *file);						// �������� �����
	bool NextQuwest(MyS_Quwest *param);												// �������� ��������� ������ � ��������
	void Reset(void);																	// ����� ���� ����������
	void Restart(void);																	// ��� �� ����, �� � ������ ���������
	bool IsValid(void);																	// �������� �� ���������� (����� ���������, ������ ������������ � �.�.)
	void TestParam(MyS_Info *param, bool getset = true);								// ���������/��������� ���������� ������������ �����
	string GetStatistic(void);															// ����� ����������
	//int GetTestCount(void);
	//bool GetTestInfo(const char *file, MyS_Info *info);									// ���������� ������� �������� �����.
};