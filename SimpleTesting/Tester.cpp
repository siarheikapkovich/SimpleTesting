#include <algorithm>
#include "Tester.h"

const string g_Key = "siarheikapkovich";
int g_Ball = 0;
const string g_Alphabet = " 0@1#2$3%4^5&6*7=8-9+АаБбВвГгДдЕеЁёЖжЗзИиКкЛлМмНнОоПпРрСсТтУуФфХхЪъЦцЧчЬьШшЩщЫыЭэЮюЯяЙйAaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";

string Cryptor(string code, string text, bool sage)
{
	int shift  = 0;
	int orig   = 0;
	int ref    = 0;
	int longer = 0;
	int couch  = 0;
	string str = "";
	string::size_type i_cod;
	string::size_type i_text;

	longer = (int)code.size() - 1;
	couch = (int)g_Alphabet.size() - 1;
	for(int i = 0; i < (int)text.size(); i++)
	{
		i_text = g_Alphabet.find(text[i]);
		i_cod = g_Alphabet.find(code[ref]);
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
			str += g_Alphabet[shift];
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
	//___ Режим не определен
	m_State = TPS_NULL; 
	//___ Первый тест
	m_CurrentTest = 0;
	//___ Первый вопрос
	m_CurQuwest = 0;
	m_StrStatistik = "";
}
/*
//***
//_ Функция извлекает из файла служебную информацию
//_ Принимает имя файла
//_ В случае неудачи, возвращает false.
//***
bool MyC_Tester::GetTestInfo(const char *file, MyS_Info *info)
{
	//___ Локальные переменные
	ifstream FileStream;				// Фаиловый поток
	string TempStr;
	string SubStr;
	string::size_type idx;
	//___ Открываем файл
	FileStream.open(file);
	if(FileStream.is_open())
	{
		while(getline(FileStream, TempStr))
		{
			//___ Ищем спецсимволы
			idx = TempStr.find('#'); // Интересно, какова вероятность ложного символа?
			//___ Если нашлись 
			if(idx != string::npos)
			{
				//___ Извлекаем маркер
				SubStr = SubStr = TempStr.substr(0, idx);
				if(SubStr == "TEST")
				{
					//___ Запишем заголовок
					*info->m_Name = TempStr.substr(idx + 1);
				}
				if(SubStr == "QUWESTCOUNT")
				{
					//___ Количество вопросов в билете
					*info->m_QuwCount = atoi(TempStr.substr(idx + 1).c_str());
				}
				//___ ДВ
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
		//___ Ошибка при открытии
		return false;
	}
	//___ Закрываем файл
	FileStream.close();
	return true;
}
*/
//***
//_ Версия 2. Более медленная. Первая слишком критична к формату файла, если есть отклонения идет в разнос.
//_ Загрузка файла теста. Не криптованного.
//_ Принимает имя файла (путь), номер билета, количество вопросов при случайном формировании, флаг случайного формирования.
//_ В случае удачной загрузки, возвращает "OK"
//_ В случае неудачи, возвращает строку c описанием ошибки либо "UNKNOW".
//***
bool MyC_Tester::LoadTest(const char *file)
{
	//___ Локальные переменные
	ifstream FileStream;				// Фаиловый поток
	MyS_Test TempTest;					// Временный объект теста
	MyS_Quwest TempQw;					// Временный объект вопроса
	string TempStr;						// Извлечение строки из файла
	string SubStr;						// Работа с подстроками извлеченной строки
	string::size_type idx;				// Позиция символа в строке
	vector<string> FileStr;				// Сохранение строк файла для дальнейшего анализа
	vector<string>::iterator pos;		// Итератор доступа

	//___ Открываем файл
	FileStream.open(file);
	//___ Проверяем на корректность
	if(FileStream.is_open())
	{
		while(getline(FileStream, TempStr))
		{
			TempStr = Cryptor("Капкович Сергей Николаевич", TempStr, 1);
			//___ Ищем спецсимволы (и избавляемся от мусора)
			idx = TempStr.find('#'); // Интересно, какова вероятность ложного символа?
			//___ Если нашлись 
			if(idx != string::npos)
			{
				FileStr.push_back(TempStr);
			}
		}
		FileStream.close();
	}
	else
	{
		//___ Сообщаем
		SubStr = "Не удалось открыть указанный файл";
		return false;
	}
	//___ Теперь найдем параметры теста
	pos = FileStr.begin();
	while(pos != FileStr.end())
	{
		TempStr = *pos;
		pos++;
		//___ Ищем позицию спецсимвола
		idx = TempStr.find('#'); 
		//___ Лучше перестраховаться
		if(idx != string::npos)
		{
			//___ Извлекаем маркер
			SubStr = SubStr = TempStr.substr(0, idx);
			if(SubStr == "TEST")
			{
				//___ Запишем заголовок
				TempTest.m_Info.m_Name = TempStr.substr(idx + 1);
			}
			if(SubStr == "QUWESTCOUNT")
			{
				//___ Количество вопросов в билете
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
	//___ Вопросы
	pos = FileStr.begin();
	while(pos != FileStr.end())
	{
		TempStr = *pos;
		pos++;
		//___ Ищем позицию спецсимвола
		idx = TempStr.find('#'); 
		//___ Лучше перестраховаться
		if(idx != string::npos)
		{
			//___ Извлекаем маркер
			SubStr = TempStr.substr(0, idx);
			if(SubStr == "MQUWEST" && !TempTest.m_Info.m_MultiQ) 
				SubStr = "";
			//___ Обрабатываем вопросы с учетом запрета
			if(SubStr == "SQUWEST" || SubStr == "MQUWEST")
			{
				//___ Содержание вопроса
				TempQw.m_Quwest = TempStr.substr(idx + 1);
				//___ Ответы на вопрос
				int i = 0;
				while(i < 8)
				{
					if(pos == FileStr.end()) break;
					TempStr = *pos;
					//___ Ищем позицию спецсимвола
					idx = TempStr.find('#');
					if(idx != string::npos)
					{
						//___ Извлекаем баллы ответа
						SubStr = TempStr.substr(0, idx);
						//___ Максимум трехзначное число
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
				//___ Сохраняем вопрос
				TempTest.m_AllQuwests.push_back(TempQw);
			}
		}
		else
		{
			//___ ERROR
			break;
		}
	}
	
	//___ Эту часть переписать
	m_Tests.push_back(TempTest);
	m_CurrentTest = 1;
	m_State = TPS_TEST;
	//___ Приступаем к формированию теста
	GenerateBilet();
	return true;
}
//***
//_ Функция генерирует новый случайный билет
//_ Принимает имя файла
//_ В случае неудачи, возвращает false.
//***
void MyC_Tester::GenerateBilet()
{
	vector<int> Checker;				// Заносятся номера вопросов, для контроля эксклюзива
	int max_rnd = static_cast<int>(m_Tests[m_CurrentTest - 1].m_AllQuwests.size());
	int rnd = 0;
	int count_q = 0;
	
	//___ Проверим количество вопросов
	if(m_Tests[m_CurrentTest - 1].m_Info.m_QuwCount <= 0)
	{
		//___ Значение по умолчанию
		m_Tests[m_CurrentTest - 1].m_Info.m_QuwCount = 3;
	}
	count_q = m_Tests[m_CurrentTest - 1].m_Info.m_QuwCount;
	//___ Подготовка
	m_Tests[m_CurrentTest - 1].m_CyrrentBilet.clear();
	m_Tests[m_CurrentTest - 1].m_CyrrentBilet.resize(count_q);
	Checker.resize(count_q);
	fill(Checker.begin(), Checker.end(), -1);
	//___ Заполняем билет так, чтоб небыло совпадений
	while(count_q != 0)
	{
		//___ Генерируем число, не большее количества вопросов
		rnd = rand() % max_rnd;
		//___ Проверяем, использовался этот вопрос или нет
		if(0 == count(Checker.begin(), Checker.end(), rnd))
		{
			//___ Если нет, теперь уже не использовать
			Checker[count_q - 1] = rnd;
			//___ Заносим вопрос в билет
			m_Tests[m_CurrentTest - 1].m_CyrrentBilet[count_q - 1] = m_Tests[m_CurrentTest - 1].m_AllQuwests[rnd];
			//___ Уменьшаем количество необработанных
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
		//___ Получить информацию
		*param = m_Tests[m_CurrentTest - 1].m_Info;
	}
	else
	{
		//___ Записать информацию
		m_Tests[m_CurrentTest - 1].m_Info = *param;
		this->Restart();
	}
}
//***
//_ Основная функция
//_ В режиме создания (редактирования), принимает вопрос и варианты ответа.
//_ В режиме тестирования принимает вариант ответа, заполняет структуру следующим вопросом.
//_ В случае неудачи, возвращает false.
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
			// Режим одного теста
			if(m_CurQuwest <= 1 + (int)m_Tests[m_CurrentTest - 1].m_CyrrentBilet.size()) //======================
			{
				//___ Нужно проверить ответ
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
						m_StrStatistik += "\nВопрос №";
						_itoa_s(m_CurQuwest - 1, szBuf, 10);
						m_StrStatistik += szBuf;
						m_StrStatistik += ": ";
						_itoa_s(tmp, szBuf, 10);
						m_StrStatistik += szBuf;
						m_StrStatistik += "% - верно";
						m_StrStatistik += '\n' + m_Tests[m_CurrentTest - 1].m_CyrrentBilet[m_CurQuwest - 2].m_Quwest;
						m_StrStatistik += '\n';
					}
					else
					{
						m_StrStatistik += "\nВопрос №";
						_itoa_s(m_CurQuwest - 1, szBuf, 10);
						m_StrStatistik += szBuf;
						m_StrStatistik += ": ";
						m_StrStatistik += "- неверно";
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
					//___ Тест закончен вывести информацию
					// Не для DV m_StrStatistik += '\n' + g_TempStr;
					string temp = m_StrStatistik;
					g_Ball = g_Ball / 10;
					_itoa_s(g_Ball, szBuf, 10);
					m_StrStatistik = "Ваш результат - ";
					m_StrStatistik += szBuf;
					m_StrStatistik += "%.\n";
					m_StrStatistik += temp;
					m_CurQuwest = 0;
					return false;
				}
			}
			else
			{
				//___ Тест закончен вывести информацию
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
	//___ Режим теста
	m_State = TPS_TEST; 
	//___ Первый тест
	m_CurrentTest = (this->IsValid())?1:0;
	//___ Первый вопрос
	m_CurQuwest = 0;
	//___ Обнуляем статистику
	m_StrStatistik = "";
	//___ Генерируем новый билет
	this->GenerateBilet();
}

void MyC_Tester::Reset()
{
	//___ Режим не определен
	m_State = TPS_NULL; 
	//___ Первый тест
	m_CurrentTest = 0;
	//___ Первый вопрос
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
