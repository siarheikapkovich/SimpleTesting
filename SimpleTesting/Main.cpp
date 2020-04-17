#define WIN32_LEAN_AND_MEAN

//#pragma comment(linker,"/MERGE:.rdata=.text")
//#pragma comment(linker,"/FILEALIGN:512 /SECTION:.text,EWRX /IGNORE:4078")
//#pragma comment(linker,"/ENTRY:New_WinMain")
//#pragma comment(linker,"/NODEFAULTLIB")

#pragma comment (lib, "comctl32.lib")
#include <stdio.h>
#include <windows.h>
#include <commctrl.h>
#include <richedit.h>
#include <commdlg.h>
#include "Tester.h"
/***********************************************************/
// ���������� ���������
/***********************************************************/
const int COUNT_SWND = 13;	// ���������� ���� ��� ������ ������������
const int COUNT_TWND = 17;	// ���������� ���� ��� ������������
/***********************************************************/
// ������������
/***********************************************************/
enum ge_StartWnd {wnd_PSel, wnd_PSelTest, wnd_SelTest, wnd_OneTest, wnd_OneRQ, wnd_OneRB, wnd_PFIO, wnd_FIO, wnd_ChekRand, wnd_ERQC, wnd_URQC, wnd_OnTime, wnd_Start};
enum ge_TestWnd {wnd_PTextOut, wnd_TextOut, wnd_PInfo, wnd_PITime, wnd_PITest, wnd_PIBilet, wnd_PIQuwest, wnd_ChecGroup, wnd_Otv1, wnd_Otv2, wnd_Otv3, wnd_Otv4, wnd_Otv5, wnd_Otv6, wnd_Otv7, wnd_Otv8, wnd_Next};
enum ge_ID {ID_SelTest = 120, ID_OneTest, ID_OneRQ, ID_OneRB, ID_Bilety, ID_ChekRand, ID_URQC, ID_OnTime, ID_Start, ID_Next, ID_Otv1, ID_Otv2, ID_Otv3, ID_Otv4, ID_Otv5, ID_Otv6, ID_Otv7, ID_Otv8, ID_OkStart};
/***********************************************************/
// ���������� �������
/***********************************************************/
HWND	ga_SelWnd[COUNT_SWND];											// �������� ���������� � ������ ������
HWND	ga_TestWnd[COUNT_TWND];											// �������� ���������� � ������ ������������
LPCSTR	ga_OtvNum[8] = {"1", "2", "3", "4", "5", "6", "7", "8"};		// ������� ������� �������
/***********************************************************/
// ���������� ����������
/***********************************************************/
HWND g_About;				// ���� ������� ����� � ���������� �����
HWND gh_Wnd;
HWND gh_Start;

MyS_Quwest g_Quwest;
MyC_Tester g_Test;
string g_StrStat;
int g_CurQuwest = 0;
int g_QuwestCount = 0;
bool g_RButton = false;
bool g_LButton = false;
/***********************************************************/
// ���������� �������
/***********************************************************/
void HideAll(void);
void ShowStart(void);

/***********************************************************/
// ������� �������
/***********************************************************/
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{ 
	//OPENFILENAME opparam;
	//char szFile[256];
	//char szFileTitle[256];
	//char szCustomFilter[256];
	char szFilter[256] = "����� ������\0*.tst\0";

	switch (uMsg) 
    { 
        case WM_DESTROY:
			//KillTimer(hwnd, MyTimer);
            PostQuitMessage(0);
            return 0;

		case WM_RBUTTONDOWN:
			g_RButton = true;
			return 0;

		case WM_RBUTTONUP:
			g_RButton = false;
			return 0;

		case WM_LBUTTONDOWN:
			g_LButton = true;
			return 0;

		case WM_LBUTTONUP:
			g_LButton = false;
			return 0;

		case WM_MOUSEMOVE:
			return 0;

		case WM_COMMAND:
			switch(wParam)
			{
				
				/*
				case IDM_OPEN:
					//___ �������� ������������� �����
					ZeroMemory(&opparam, sizeof(opparam));
					opparam.lStructSize = sizeof(OPENFILENAME);
					opparam.hwndOwner = hwnd;
					opparam.nFilterIndex = 1;
					opparam.lpstrFile = szFile;
					opparam.nMaxFile = sizeof(szFile);
					opparam.lpstrFileTitle = szFileTitle;
					opparam.nMaxFileTitle = sizeof(szFileTitle);
					opparam.lpstrCustomFilter = szCustomFilter;
					opparam.Flags = OFN_EXPLORER | OFN_CREATEPROMPT;
					opparam.lpstrFilter = szFilter;
					szFileTitle[0] = '\0';
					szFile[0] = '\0';
					GetOpenFileName(&opparam);
					// ����� �������� ��������� �������������, �.�. UpdateMain() ������� ������
					return 0;

				case IDM_START:
					HANDLE hFind;
					WIN32_FIND_DATA FindData;

					g_Test.Reset();
					HideAll();
					SendMessage(ga_SelWnd[wnd_SelTest], LB_RESETCONTENT, NULL, NULL);
					//___ � �� ������ �������� ������ ���� �����
					SendMessage(ga_SelWnd[wnd_OneTest], BM_SETCHECK, BST_CHECKED, NULL);
					hFind = FindFirstFile("*.tst", &FindData);
					if(hFind != INVALID_HANDLE_VALUE)
					{
						SendMessage(ga_SelWnd[wnd_SelTest], LB_ADDSTRING, NULL, (LPARAM)FindData.cFileName);
						while(FindNextFile(hFind, &FindData))
						{
							SendMessage(ga_SelWnd[wnd_SelTest], LB_ADDSTRING, NULL, (LPARAM)FindData.cFileName);
						}
						FindClose(hFind);
					}
					else
					{
						MessageBox(gh_Wnd, "�� ���������� �� ������ �����!", "��������!", MB_OK | MB_ICONEXCLAMATION);
						return 0;
					}
					for(int i = 0; i < COUNT_SWND; i++)
					{
						if(ga_SelWnd[i])
							ShowWindow(ga_SelWnd[i], SW_NORMAL);
					}
					EnableMenuItem(GetMenu(gh_Wnd), IDM_START, MF_BYCOMMAND | MF_GRAYED);
					EnableMenuItem(GetMenu(gh_Wnd), IDM_Restart, MF_BYCOMMAND | MF_GRAYED);
					DrawMenuBar(gh_Wnd);
					return 0;

				case IDM_Restart:
					g_Test.Restart();
					g_CurQuwest = 0;
					ShowStart();
					EnableMenuItem(GetMenu(gh_Wnd), IDM_START, MF_BYCOMMAND | MF_GRAYED);
					EnableMenuItem(GetMenu(gh_Wnd), IDM_Restart, MF_BYCOMMAND | MF_GRAYED);
					DrawMenuBar(gh_Wnd);
					return 0;
					*/
				default:
					switch(LOWORD(wParam))
					{
					case ID_SelTest:
						if(HIWORD(wParam) == LBN_DBLCLK)
							// �������� ������ ����� !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						return 0;
					//___ ������ �����
					case ID_Start:
						if(HIWORD(wParam) == BN_CLICKED)
						{
							if((BOOL)SendMessage(ga_SelWnd[wnd_OneTest], BM_GETCHECK, NULL, NULL))
							{
								//___ �������� ������ ����������� �����
								int file = (int)SendMessage(ga_SelWnd[wnd_SelTest], LB_GETCURSEL, NULL, NULL);
								if(LB_ERR == file)
								{
									MessageBox(gh_Wnd, "�������� ����", "���������", MB_OK|MB_ICONEXCLAMATION);
									return 0;
								}
								else
								{
									char tstr[255];
									GetWindowText(ga_SelWnd[wnd_FIO], tstr, 32);
									g_StrStat = tstr;
									if(g_StrStat == "")
									{
										MessageBox(gh_Wnd, "������� ��� ������������", "���������", MB_OK | MB_ICONEXCLAMATION);
										return 0;
									}
									g_StrStat += '\n';
									//___ ������� ��� �����
									SendMessage(ga_SelWnd[wnd_SelTest], LB_GETTEXT, file, (LPARAM)&tstr);
									if(!g_Test.LoadTest(tstr))
									{
										//___ ������� ������
										HideAll();
										SetWindowText(g_About, "������ �������� �����");
										if(g_About)
											ShowWindow(g_About, SW_NORMAL);
										return 0;
									}
								}
							}
							else
							{
								// ���� ��� �������������� ������
								if(SendMessage(ga_SelWnd[wnd_SelTest], LB_GETSELCOUNT, NULL, NULL) < 2)
								{
									MessageBox(gh_Wnd, "�������� ��������� ��������� ������\n��������� ������� Shift.\n��� �������� ����� - ��������� ����.", "���������", MB_OK|MB_ICONEXCLAMATION|MB_APPLMODAL);
									return 0;
								}
								else
								{
									// ������� ����� ������ � ������
								}
							}
							g_CurQuwest = 0;
							//___ ������� ��������� ���������� � �����
							ShowStart();
						}
						return 0;
					//___ ������� ������ "�����"
					case ID_Next:
						if(HIWORD(wParam) == BN_CLICKED)
						{
							int ctr = 0;
							char szBuf[32];
							//MyS_Info info;
							string str;
							//ZeroMemory(&g_Quwest, sizeof(MyS_Quwest));
							for(int i = 0; i < 8; i++)
							{
								if((BOOL)SendMessage(ga_TestWnd[wnd_Otv1 + i], BM_GETCHECK, NULL, NULL))
								{
									g_Quwest.m_Valid[i] = 1;
									ctr++;
								}
								else
								{
									g_Quwest.m_Valid[i] = 0;
								}
							}
							if(ctr == 0 && g_CurQuwest > 0)
							{
								MessageBox(hwnd, "�� �� ������� ������� ������", "���������", MB_OK | MB_APPLMODAL | MB_ICONEXCLAMATION);
								return 0;
							}
							else
							{
								for(int i = 0; i < 8; i++)
								{
									SendMessage(ga_TestWnd[wnd_Otv1 + i], BM_SETCHECK, (WPARAM)BST_UNCHECKED, NULL);
								}
								if(g_Test.NextQuwest(&g_Quwest) && g_CurQuwest != g_QuwestCount)
								{
                                    g_CurQuwest++;
									_itoa_s(g_CurQuwest, szBuf, 10);
									str = "������... ";
									str += szBuf;
									_itoa_s(g_QuwestCount, szBuf, 10);
									str += " �� ";
									str += szBuf;
									SetWindowText(ga_TestWnd[wnd_PIQuwest], str.c_str());
									//___ ��������� ����� �������
									str = '\n' + g_Quwest.m_Quwest + "\n\n";
									//___ ������ �������� �������
									for(int i = 0; i < 8; i++)
									{
										if(g_Quwest.m_Otvet[i] != "")
										{
											str += "����� �";
											str += ga_OtvNum[i];
											str += ":";
											str += " ";
											str += g_Quwest.m_Otvet[i];
											str += '\n';
											str += '\n';
											EnableWindow(ga_TestWnd[wnd_Otv1 + i], true);
										}
										else
										{
											EnableWindow(ga_TestWnd[wnd_Otv1 + i], false);
										}
									}
									SendMessage(ga_TestWnd[wnd_TextOut], WM_SETTEXT, 0, (LPARAM)str.c_str());
								}
								else
								{
									//___ ���� �������� ������� ����������
									str = g_StrStat;
									str += g_Test.GetStatistic();
									SetWindowText(g_About, str.c_str());
									g_CurQuwest = 0;
									HideAll();
									ShowWindow(g_About, SW_NORMAL);
									//EnableMenuItem(GetMenu(gh_Wnd), IDM_Restart, MF_BYCOMMAND | MF_ENABLED);
									//EnableMenuItem(GetMenu(gh_Wnd), IDM_START, MF_BYCOMMAND | MF_ENABLED);
									//DrawMenuBar(gh_Wnd);
								}
							}
						}
						return 0;
					case ID_OkStart:
						HANDLE hFind;
						WIN32_FIND_DATA FindData;

						g_Test.Reset();
						HideAll();
						SendMessage(ga_SelWnd[wnd_SelTest], LB_RESETCONTENT, NULL, NULL);
						//___ � �� ������ �������� ������ ���� �����
						SendMessage(ga_SelWnd[wnd_OneTest], BM_SETCHECK, BST_CHECKED, NULL);
						hFind = FindFirstFile("*.tst", &FindData);
						if (hFind != INVALID_HANDLE_VALUE)
						{
							SendMessage(ga_SelWnd[wnd_SelTest], LB_ADDSTRING, NULL, (LPARAM)FindData.cFileName);
							while (FindNextFile(hFind, &FindData))
							{
								SendMessage(ga_SelWnd[wnd_SelTest], LB_ADDSTRING, NULL, (LPARAM)FindData.cFileName);
							}
							FindClose(hFind);
						}
						else
						{
							MessageBox(gh_Wnd, "�� ���������� �� ������ �����!", "��������!", MB_OK | MB_ICONEXCLAMATION);
							return 0;
						}
						for (int i = 0; i < COUNT_SWND; i++)
						{
							if (ga_SelWnd[i])
								ShowWindow(ga_SelWnd[i], SW_NORMAL);
						}
						//EnableMenuItem(GetMenu(gh_Wnd), IDM_START, MF_BYCOMMAND | MF_GRAYED);
						//EnableMenuItem(GetMenu(gh_Wnd), IDM_Restart, MF_BYCOMMAND | MF_GRAYED);
						DrawMenuBar(gh_Wnd);
						return 0;
					}
					return 0;
			}
			return 0;
 
        default: 
            return DefWindowProc(hwnd, uMsg, wParam, lParam); 
    } 
    return 0; 
} 

void ShowStart(void)
{
	char szBuf[32];
	MyS_Info info;
	string str;

	g_Test.TestParam(&info);
	//___ �������� �����
	SetWindowText(ga_TestWnd[wnd_PTextOut], info.m_Name.c_str());
	//___ ��������������
	str = "\n\t����� ��������� ����������� ��� ������ �������\n";
	str += "���������� �������� ���� ������������ �����, � ������ �� ����� ������� ���� ���� ������������ ���������� ���������� �����\n";
	if(info.m_MultiQ)
	{
		str += "��������:\n� ����� ������������ �������, �� ������� ���� ��������� ���������� ��������� ������.\n";
	}
	if(info.m_RandBilet)
	{
		str += "������� ���������� ��������� �������\n";
	}
	str += "\n\t��� ��������� ������� ������� ������� ������ - ";
	str += '"';
	str += "������";
	str += '"';
	SetWindowText(ga_TestWnd[wnd_TextOut], str.c_str());
	//___ ������� ������ ����������
	g_QuwestCount = info.m_QuwCount;
	_itoa_s(g_CurQuwest, szBuf, 10);
	str = "������... ";
	str += szBuf;
	_itoa_s(g_QuwestCount, szBuf, 10);
	str += " �� ";
	str += szBuf;
	SetWindowText(ga_TestWnd[wnd_PIQuwest], str.c_str());
	for(int i = 0; i < 8; i++)
		EnableWindow(ga_TestWnd[wnd_Otv1 + i], false);
	//___ ���������� ������
	HideAll();
	for(int i = 0; i < COUNT_TWND; i++)
	{
		if(ga_TestWnd[i])
			ShowWindow(ga_TestWnd[i], SW_NORMAL);
	}
}

void HideAll(void)
{
	//___ ��������� ����������
	int iter; // �������� �������
	//___
	if(g_About)
		ShowWindow(g_About, SW_HIDE);
	if(gh_Start)
		ShowWindow(gh_Start, SW_HIDE);
	//___ 
	for(iter = 0; iter < COUNT_SWND; iter++)
	{
		if(ga_SelWnd[iter])
			ShowWindow(ga_SelWnd[iter], SW_HIDE);
	}
	//___
	for(iter = 0; iter < COUNT_TWND; iter++)
	{
		if(ga_TestWnd[iter])
			ShowWindow(ga_TestWnd[iter], SW_HIDE);
	}
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
    WNDCLASS wc; 
	MSG msg;
	//___ ����� �������� ����
    wc.style = CS_SAVEBITS; 
    wc.lpfnWndProc = (WNDPROC) MainWndProc; 
    wc.cbClsExtra = 0; 
    wc.cbWndExtra = 0; 
    wc.hInstance = hInstance; 
    wc.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION)); 
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); 
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE+1); 
    wc.lpszMenuName =  NULL; 
    wc.lpszClassName = "MainWindowClass";
	
	if(!RegisterClass(&wc))
	{
		MessageBox(NULL, "RegisterClass", "ERROR", MB_OK);
        return FALSE; 
	}
	
	hWnd = CreateWindow("MainWindowClass", "����", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);
	if(!hWnd)
		return FALSE;

	gh_Wnd = hWnd;
	srand((unsigned)GetTickCount());
	
	HMODULE hm = LoadLibrary("Riched20.dll");
	
	INITCOMMONCONTROLSEX initcontrol;
	initcontrol.dwSize = sizeof(initcontrol);
	initcontrol.dwICC = ICC_UPDOWN_CLASS;
	InitCommonControlsEx(&initcontrol);
	
	
	string about;
	about = "\n��������� �������� ��������-����������������.\n";
	about += "������ ������ �� �������� �����������";
	//___ ������� �������� ���������� ���������� ����
	g_About = CreateWindowEx(NULL, RICHEDIT_CLASS, "� ���������", WS_CHILD | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOVSCROLL | ES_READONLY | SS_CENTER, 10, 10, 615, 210, hWnd, NULL, hInstance, NULL);
	SendMessage(g_About, EM_SETBKGNDCOLOR, NULL, GetSysColor(COLOR_BTNFACE));
	SendMessage(g_About, EM_SETMARGINS, EC_LEFTMARGIN, 5);
	SetWindowText(g_About, about.c_str()); 
	ShowWindow(g_About, SW_NORMAL);
	gh_Start = ga_SelWnd[wnd_Start] = CreateWindow("BUTTON", "�����", WS_CHILD | BS_FLAT, 250, 395, 100, 25, hWnd, (HMENU)ID_OkStart, hInstance, NULL);
	ShowWindow(gh_Start, SW_NORMAL);
	//___ �������� ���������� ������ ������
	ga_SelWnd[wnd_PSel] = CreateWindow("STATIC", "����� ����� � ������ ������������", WS_CHILD | SS_CENTER, 10, 5, 615, 15, hWnd, NULL, hInstance, NULL);
	ga_SelWnd[wnd_PSelTest] = CreateWindow("STATIC", "������ ��������� ������", WS_CHILD | SS_CENTER, 10, 30, 300, 15, hWnd, NULL, hInstance, NULL);
	ga_SelWnd[wnd_SelTest] = CreateWindow("LISTBOX", "NULL", WS_CHILD | WS_BORDER | LBS_STANDARD, 10, 50, 300, 380, hWnd, (HMENU)ID_SelTest, hInstance, NULL);
	ga_SelWnd[wnd_OneTest] = CreateWindow("BUTTON", "��������� ����", WS_CHILD | WS_GROUP | WS_TABSTOP | BS_AUTORADIOBUTTON | BS_FLAT, 350, 60, 260, 15, hWnd, NULL, hInstance, NULL);
	ga_SelWnd[wnd_OneRQ] = CreateWindow("BUTTON", "�� ������ ������� �� ���������", WS_CHILD | WS_DISABLED | BS_AUTORADIOBUTTON | BS_FLAT, 350, 80, 260, 15, hWnd, NULL, hInstance, NULL);
	ga_SelWnd[wnd_OneRB] = CreateWindow("BUTTON", "�� ������ ������ �� ���������", WS_CHILD | WS_DISABLED | BS_AUTORADIOBUTTON | BS_FLAT, 350, 100, 260, 15, hWnd, NULL, hInstance, NULL);
	ga_SelWnd[wnd_PFIO] = CreateWindow("STATIC", "��� ������������", WS_CHILD | SS_CENTER, 350, 130, 260, 15, hWnd, NULL, hInstance, NULL);
	ga_SelWnd[wnd_FIO] = CreateWindow("EDIT", NULL, WS_CHILD | WS_BORDER, 350, 150, 260, 20, hWnd, NULL, hInstance, NULL);
	ga_SelWnd[wnd_ChekRand] = CreateWindow("BUTTON", "��������� ������������ ������", WS_CHILD | WS_DISABLED | BS_AUTOCHECKBOX | BS_FLAT, 350, 200, 260, 15, hWnd, NULL, hInstance, NULL);
	ga_SelWnd[wnd_ERQC] = CreateWindow("EDIT", NULL, WS_CHILD | WS_BORDER | WS_DISABLED, 350, 220, 50, 20, hWnd, NULL, hInstance, NULL);
	ga_SelWnd[wnd_URQC] = CreateUpDownControl(WS_CHILD | WS_DISABLED | UDS_WRAP | UDS_ARROWKEYS | UDS_SETBUDDYINT, 400, 220, 0, 20, hWnd, NULL, hInstance, ga_SelWnd[wnd_ERQC], 15, 1, 3);
	ga_SelWnd[wnd_OnTime] = CreateWindow("BUTTON", "���� �� �����", WS_CHILD | WS_DISABLED | BS_AUTOCHECKBOX | BS_FLAT, 350, 260, 260, 15, hWnd, NULL, hInstance, NULL);
	ga_SelWnd[wnd_Start] = CreateWindow("BUTTON", "�����", WS_CHILD | BS_FLAT, 525, 395, 100, 25, hWnd, (HMENU)ID_Start, hInstance, NULL);
	//___ �������� ���������� ������ ������������
	ga_TestWnd[wnd_PTextOut] = CreateWindow("STATIC", "TEXT", WS_CHILD | SS_CENTER, 10, 5, 615, 15, hWnd, NULL, hInstance, NULL);
	ga_TestWnd[wnd_TextOut] = CreateWindowEx(NULL, RICHEDIT_CLASS, NULL, WS_CHILD | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOVSCROLL | ES_READONLY, 10, 20, 615, 300, hWnd, NULL, hInstance, NULL);
	SendMessage(ga_TestWnd[wnd_TextOut], EM_SETBKGNDCOLOR, NULL, GetSysColor(COLOR_BTNFACE));
	SendMessage(ga_TestWnd[wnd_TextOut], EM_SETMARGINS, EC_LEFTMARGIN, 5);
	ga_TestWnd[wnd_PInfo] = CreateWindow("BUTTON", "����������", WS_CHILD | BS_GROUPBOX | BS_CENTER | BS_FLAT, 10, 325, 220, 95, hWnd, NULL, hInstance, NULL);
	ga_TestWnd[wnd_PITime] = CreateWindow("STATIC", "�������� ������� - 00:00", WS_CHILD | WS_DISABLED, 15, 345, 210, 15, hWnd, NULL, hInstance, NULL);
	ga_TestWnd[wnd_PITest] = CreateWindow("STATIC", "����......... 1 �� 1", WS_CHILD, 15, 362, 210, 15, hWnd, NULL, hInstance, NULL);
	ga_TestWnd[wnd_PIBilet] = CreateWindow("STATIC", "�����...... ��������", WS_CHILD, 15, 379, 210, 15, hWnd, NULL, hInstance, NULL);
	ga_TestWnd[wnd_PIQuwest] = CreateWindow("STATIC", "������... ", WS_CHILD, 15, 396, 210, 15, hWnd, NULL, hInstance, NULL);
	ga_TestWnd[wnd_ChecGroup] = CreateWindow("BUTTON", "�������� ���������� �����", WS_CHILD | BS_GROUPBOX | BS_CENTER | BS_FLAT, 240, 325, 385, 95, hWnd, NULL, hInstance, NULL);
	for(int i = 0; i < 8; i++)
	{
        ga_TestWnd[wnd_Otv1 + i] = CreateWindow("BUTTON", ga_OtvNum[i], WS_CHILD | WS_DISABLED | BS_AUTOCHECKBOX | BS_LEFTTEXT | BS_FLAT, 260 + (i * 45), 350, 30, 15, hWnd, (HMENU)ID_Otv1 + i, hInstance, NULL);
	}
	ga_TestWnd[wnd_Next] = CreateWindow("BUTTON", "������", WS_CHILD | BS_CENTER | BS_DEFPUSHBUTTON | BS_FLAT, 330, 380, 200, 25, hWnd, (HMENU)ID_Next, hInstance, NULL);
	
	SendMessage(ga_SelWnd[wnd_FIO], EM_SETLIMITTEXT, 32, NULL);

	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	FreeLibrary(hm);

	return (int)msg.wParam;
} 