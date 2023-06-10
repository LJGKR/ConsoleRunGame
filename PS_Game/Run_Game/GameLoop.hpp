#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <thread>
#include "G_Util.hpp"
#include "G_Manager.hpp"
#include <conio.h>
#include <algorithm>

using namespace std;


namespace Run_Game {

	bool isGameRunning = false;
	bool ispaused = false;
	bool isGameOver = false;
	GameManager gamemanager;
	Object Player;
	Object Obstacle;
	Object Heart;
	Scene Cloud;
	Scene AirPlane;
	Scene Mountain;

	struct RankingInfo
	{
		string playerName;
		int score;
	};
	vector<RankingInfo> rankings;

	void AddToRanking(int score)
	{
		RankingInfo playerInfo;
		playerInfo.playerName = "유한인";
		playerInfo.score = score;
		rankings.push_back(playerInfo);
	}

	void SortRanking()
	{
		sort(rankings.begin(), rankings.end(), [](const RankingInfo& a, const RankingInfo& b) {return a.score > b.score; });
	}

	void PrintRanking()
	{
		SortRanking();
		cout << "Ranking: " << endl;
		for (int i = 0; i < rankings.size(); i++)
		{
			cout << i + 1 << ". " << rankings[i].playerName << " - " << rankings[i].score << " 점" << endl;
		}
	}

	void ShowRanking()
	{
		Obstacle.RenderGameOver(15, 8);
		PrintRanking();
	}

	int keyCon()
	{
		if (_kbhit())
		{
			char temp = _getch();
			if (temp == -32)
			{
				temp = _getch();
				switch (temp)
				{
				case 72:
					return 1;
				case 80:
					return 2;
				}
			}
			else if (temp == ' ')
			{
				return 3;
			}
		}
	}

	int MenuDraw(int x, int y)
	{
		GotoXY(x - 2, y);
		printf(">   Start Game");
		GotoXY(x - 2, y + 1);
		printf("    Exit Game");
		while (true)
		{
			int n = keyCon();
			switch (n)
			{
			case 1:
				if (y > 14)
				{
					GotoXY(x - 2, y);
					printf(" ");
					GotoXY(x - 2, --y);
					printf(">");
				}
				break;
			case 2:
				if (y < 15)
				{
					GotoXY(x - 2, y);
					printf(" ");
					GotoXY(x - 2, ++y);
					printf(">");
				}
				break;
			case 3:
				return y - 14;
			}
		}
	}

	void Initialize()
	{
		Player.initPlayer();
		Mountain.InitMountain();
		Obstacle.initObstacle();
		Obstacle.initData();
		srand((int)time(NULL));
		Heart.initHeart();
		AirPlane.InitAirPlane();
		Cloud.InitCloud();
	}

	void Input()
	{
		
		if (!ispaused)
			{
				Heart.heart.x -= 1;
				Mountain.ActiveMountain();
				Mountain.mountain.x -= Mountain.mountain.speed;
				if (Mountain.mountain.x<= 0)
				{
					Mountain.mountain.isactive = false;
				}
				Cloud.ActiveCloud();
				Cloud.cloud.x -= Cloud.cloud.speed;
				if (Cloud.cloud.x <= 0)
				{
					Cloud.cloud.isactive = false;
				}

				Obstacle.ActiveObstacle();
				Obstacle.obstacle.x -= Obstacle.obstacle.speed;
				if (Obstacle.obstacle.x <= 0)
				{
					Obstacle.obstacle.isactive = false;
				}
				if (Player.player.legstate == false)
				{
					Player.player.legstate = true;
				}
				else
				{
					Player.player.legstate = false;
				}

				AirPlane.ActiveAirPlane();
				AirPlane.airplane.x -= AirPlane.airplane.speed;
				if (AirPlane.airplane.x <= 0)
				{
					AirPlane.airplane.isactive = false;
				}

			}
		

		if (GetAsyncKeyState(VK_SPACE) && Player.player.isBottom == true)
		{
			if (!ispaused)
			{
				Player.player.isJumping = true;
				Player.player.isBottom = false;
			}
		}

		if (GetAsyncKeyState(VK_ESCAPE))
		{
			if (ispaused)
			{
				ispaused = false;
			}
			else {
				ispaused = true;
			}
		}
	}
	void Update()
	{
		if (Obstacle.obstacle.isactive)
		{
			if ((Obstacle.obstacle.x + 2 < Player.player.x + 3) && (Obstacle.obstacle.x + 2 > Player.player.x) && (Obstacle.obstacle.y < Player.player.y + 3) && (Obstacle.obstacle.y > Player.player.y) || (Obstacle.obstacle.x + 2 < Player.player.x + 3) && (Obstacle.obstacle.x + 2 > Player.player.x) && (Obstacle.obstacle.y + 3 <= Player.player.y + 3) && (Obstacle.obstacle.y + 3 >= Player.player.y))
			{
				Obstacle.obstacle.isactive = false;
				ispaused = true;
				isGameOver = true;
				AddToRanking(Obstacle.gamemanager.score);
			}
		}

		if (Heart.heart.isactive)
		{
			if ((Heart.heart.x < Player.player.x + 3) && (Heart.heart.x > Player.player.x) && (Heart.heart.y >= Player.player.y))
			{
				Heart.heart.isactive = false;
				Obstacle.gamemanager.score += 50;
				if (Obstacle.gamemanager.score >= 300)
				{
					Obstacle.SpeedUp();
				}
			}
		}

	}
	void Render()
	{
		while (!isGameRunning)
		{
			system("cls");
			GotoXY(15, 8);
			printf("--------------------------------");
			GotoXY(15, 9);
			printf("-- 준형이의 모험 (Feat. 진규) --");
			GotoXY(15, 10);
			printf("--------------------------------\n");
			int option = MenuDraw(23, 14);

			switch (option)
			{
			case 0:
				ispaused = false;
				isGameOver = false;
				isGameRunning = true;
				Clear();
				break;
			case 1:
				exit(0);
				break;
			}

		}

			int randX = rand() % 30 + 25;
			int randY = rand() % 3 + 12;

			Clear();

			GotoXY(50, 1);
			printf("Press ESC >> PAUSE");

		if (isGameOver)
		{
			ShowRanking();
			GotoXY(10, 6);
			printf("Press R to return to the main menu");

			if (GetAsyncKeyState('R') && 0x8001)
			{
				isGameRunning = false;  // 메인 화면으로 돌아가기 위해 게임 실행 루프를 재시작
				isGameOver = false;     // 게임 오버 상태 초기화
				Obstacle.gamemanager.score = 0;
			}
		}
		else
		{
			Mountain.RenderMountain();
			Player.RenderPlayer(Player.player.x, Player.player.y);
			Obstacle.RenderObstacle();
			Cloud.RenderCloud();
			Player.JBPlayer();
			Obstacle.RenderData();
			Heart.ActiveHeart(randX, randY);
			Heart.RenderHeart();
			AirPlane.RenderAirPlane();
			if (!ispaused)
			{
				Heart.MoveHeart();
			}
		}
		Sleep(50);
	}
	void Release()
	{
		if (isGameOver)  // 게임 오버 상태일 때만 화면 지우고 커서 이동
		{
			system("cls");
			GotoXY(0, 0);
		}
	}
	class GameLoop
	{
	public:
		GameLoop() {}
		~GameLoop() {}

		void Run()
		{
			Obstacle.gamemanager.GameState = 1;
			Initialize();

			while (Obstacle.gamemanager.GameState != 2)
			{
				Input();
				Update();
				Render();

				if (ispaused)
				{
					continue;
				}
			}
			Release();
		}
	};
}