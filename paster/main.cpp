#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include "SendKeys.h"
#include <time.h>
#include <sstream>

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:main")

LPCTSTR g_head_begin = _T("\n//* Login-Name       :  My Username\n//******************************************************************************\n//* Rueckgabe        :  \n//******************************************************************************\n//* Uebergabe        :  \n//******************************************************************************\n//* Beschreibung     :  \n//**********************************FUNKTION************************************\n");
LPCTSTR g_head_end = _T("//******************************************************************************\n//* Erstellungsdatum :  ");

using namespace std;

std::wstring create_text()
{
	const int BUFLEN = 16;
	char szTime[BUFLEN];
	time_t t = time(0);
	strftime(szTime, BUFLEN, "%d.%m.%Y", localtime(&t));

	wstringstream s;
	s << g_head_end;
	s <<  szTime;
	s << g_head_begin;
	return s.str();
}

int main(int argc, _TCHAR* argv[])
{
	HWND h;
	CSendKeys *sender;

	Sleep(1000);
	
	h = GetForegroundWindow();
	sender = new CSendKeys();
	if ( h > 0 )
	{
		std::wstring text = create_text();
		sender->AppActivate(h);
		sender->SendKeys(text.c_str()	, true );
		Sleep(1000);
		sender->SendKeys(_T("{DOWN}{DOWN}{DOWN}{DOWN}{DOWN}{DOWN}{DOWN}{DOWN}{DOWN}{DOWN}{END}{ENTER}"), true );
	}

	return 0;
}
