#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <thread>
#include "GameLoop.hpp"
#include "G_Manager.hpp"
#include "G_Util.hpp"


int main()
{
	Run_Game::GameLoop gameloop;

	SetConsoleSize(100, 30);
	HideCursor();
	SetConsoleTitle(TEXT("그림이의 모험"));

	gameloop.Run();
}