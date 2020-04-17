#include <string>
#include <vector>
#include <fstream>

using namespace std;

enum MyE_TPS {TPS_NULL, TPS_TEST, TPS_MULTITEST, TPS_ONEQUWEST, TPS_CREATE, TPS_DEBUG}; // Test Parameter Set

struct MyS_Quwest
{
	string m_Quwest;										// Вопрос
	string m_Otvet[8];										// Ответы
	int    m_Valid[8];										// Флаг правильности ответа или количество баллов
};

struct MyS_Info
{
	string m_Name;											// Имя теста (название предмета)
	int m_QuwCount;											// Количество вопросов в билете, при случайном формировании
	int m_Time;												// Время на один вопрос в секундах
	int m_BiletCount;										// Количество билетов
	bool m_RandBilet;										// Флаг случайного формирования билета
	bool m_MultiQ;											// Загружать или нет вопросы с множественным ответом (ДВ)
};

struct MyS_Test
{
	MyS_Info m_Info;										// Информация о тесте
	vector<MyS_Quwest> m_AllQuwests;						// Все вопросы
	vector<MyS_Quwest> m_CyrrentBilet;						// Активный билет
};

class MyC_Tester
{
	//___ Закрытые члены класса
	//string m_Error;
	MyE_TPS m_State;										// Режим работы
	int m_CurrentTest;										// Номер активного теста
	int m_CurQuwest;										// Текущий вопрос
	string m_StrStatistik;									// Сюда сохраняем результаты
	vector<MyS_Test> m_Tests;								// Хранилище тестов
	//___ Закрытые методы класса
	void GenerateBilet(void);
public:
	string Uncrypt(string Text);
	string Crypt(string Text);

	MyC_Tester();											// Конструктор по умолчанию
	bool LoadTest(const char *file);						// Загрузка теста
	bool NextQuwest(MyS_Quwest *param);						// Получить следующий вопрос с ответами
	void Reset(void);										// Сброс всех параметров
	void Restart(void);										// Тот же тест, но с новыми вопросами
	bool IsValid(void);										// Проверка на готовность (тесты загружены, билеты сформированы и т.д.)
	void TestParam(MyS_Info *param, bool getset = true);	// Получение/установка параметров загруженного теста
	string GetStatistic(void);								// Вывод статистики
	//int GetTestCount(void);
	//bool GetTestInfo(const char *file, MyS_Info *info);	// Упрощенная функция загрузки файла.
};