#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <vector>

using namespace std;

void Clear(void)
{
	system("cls");
}

void GotoXY(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}



void SetCursor(BOOL bShow)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = bShow;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void SetConsoleSize(int x, int y)
{
	char modeCmd[128];
	sprintf_s(modeCmd, sizeof(modeCmd), "mode con cols=%d line=%d", x, y);
	system(modeCmd);
	system("color 70");
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = false;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void SetConsoleSize(int x, int y);
void HideCursor();
void GotoXY(int x, int y);
