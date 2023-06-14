#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <vector>
#include "G_Util.hpp"
#define GRAVITY 2

using namespace std;

namespace Run_Game {
	class GameManager {
	public :
		int score = 0;
		int level;
		int life;
		int GameState;

		enum GameState {
			Reset,   //Scene 로드 시 초기화
			Start,   //게임 시작 시
			GameOver //게임 종료 시
		};

		GameManager() {
			GameState = Reset;
		}
		~GameManager() {

		}

		void ResetScore() {
			score = 0;
		}

		void GetScore() {
			score += 50;
		}

	};

	class Scene {
	public:
		struct Cloud
		{
			int x;
			int y;
			float speed;
			bool isactive;
		}cloud;

		void InitCloud()
		{
			cloud.x = 20;
			cloud.y = 5;
			cloud.speed = 0.75f;
			cloud.isactive = false;
		}

		void ActiveCloud()
		{
			if (cloud.isactive == false)
			{
				cloud.x = 40;
				cloud.isactive = true;
			}
		}

		void RenderCloud() {  //오브젝트의 형태
			if (cloud.isactive == true)
			{
				GotoXY(cloud.x, cloud.y);
				printf("   \033[38m⊙   ⊙⊙  ");
				GotoXY(cloud.x, cloud.y + 1);
				printf(" ⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙  ");
				GotoXY(cloud.x, cloud.y + 2);
				printf("  ⊙⊙⊙⊙⊙⊙⊙⊙⊙  ");
				GotoXY(cloud.x, cloud.y + 3);
				printf("   ⊙⊙⊙  ⊙\033[30m    ");
			}
		}

		struct AirPlane
		{
			int x;
			int y;
			float speed;
			bool isactive;
		}airplane;

		void InitAirPlane()
		{
			airplane.x = 40;
			airplane.y = 3;
			airplane.speed = 1.4f;
			airplane.isactive = false;
		}

		void ActiveAirPlane()
		{
			if (airplane.isactive == false)
			{
				airplane.x = 40;
				airplane.isactive = true;
			}
		}

		void RenderAirPlane() {  //오브젝트의 형태
			if (airplane.isactive == true)
			{
				GotoXY(airplane.x, airplane.y);
				printf("           \033[31m●●●\033[30m");
				GotoXY(airplane.x, airplane.y + 1);
				printf(" ●●●     \033[34m●●●●\033[30m ");
				GotoXY(airplane.x, airplane.y + 2);
				printf("●●●●●●●●●●●");
				GotoXY(airplane.x, airplane.y + 3);
				printf("         \033[34m●●●●\033[30m");
				GotoXY(airplane.x, airplane.y + 4);
				printf("           \033[31m●●●\033[30m");
			}
		}

		struct Mountain
		{
			int x;
			int y;
			float speed;
			bool isactive;
		}mountain;

		void InitMountain()
		{
			mountain.x = 40;
			mountain.y = 15;
			mountain.speed = 0.8f;
			mountain.isactive = false;
		}

		void ActiveMountain()
		{
			if (mountain.isactive == false)
			{
				mountain.x = 40;
				mountain.isactive = true;
			}
		}

		void RenderMountain() {  //오브젝트의 형태
			if (mountain.isactive == true)
			{
				GotoXY(mountain.x, mountain.y);
				printf("          \033[32m⊙⊙⊙");
				GotoXY(mountain.x, mountain.y + 1);
				printf("        ⊙⊙⊙⊙⊙⊙⊙");
				GotoXY(mountain.x, mountain.y + 2);
				printf("      ⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙");
				GotoXY(mountain.x, mountain.y + 3);
				printf("    ⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙");
				GotoXY(mountain.x, mountain.y + 4);
				printf("  ⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙\033[30m");
			}
		}

		void RenderMainScreen()
		{
			system("cls");
			GotoXY(15, 8);
			printf(" \033[33m-------------------------------");
			GotoXY(15, 9);
			printf("｜        \033[36m그림이의 모험\033[33m        ｜");
			GotoXY(15, 10);
			printf(" -------------------------------\n");
			printf("\n");
			GotoXY(10, 12);
			printf("Press 'Space Bar' to select and move character");
		}
	};

	class Object {
	public:
		Object() {}
		virtual ~Object(){}

		struct Player
		{
			int x, y;
			bool isactive;
			bool legstate;
			bool isJumping;
			bool isBottom;
		}player;

		void initPlayer()
		{
			player.x = 5;
			player.y = 18;
			player.isactive = false;
			player.legstate = false;
			player.isJumping = false;
			player.isBottom = true;
		}

		void RenderPlayer(int x, int y)
		{
			GotoXY(x, y);
			printf(" ○ ");
			GotoXY(x, y + 1);
			printf("┏▲┚");
			GotoXY(x, y + 2);
			if (player.legstate == true)
			{
				printf(" ┚＼");
			}
			else
			{
				printf("／┛");
			}
		}
		
		void JBPlayer()
		{
			if (player.isJumping)
			{
				player.y -= GRAVITY;
			}
			else
			{
				player.y += GRAVITY;
			}
			if (player.y <= 10)
			{
				player.isJumping = false;
			}
			else if (player.y >= 18)
			{
				player.y = 18;
				player.isBottom = true;
			}
		}

		GameManager gamemanager;
		Scene scene;



		void initData()
		{
			gamemanager.life = 3;
			gamemanager.GameState = 0;
			gamemanager.score = 0;
		}

		void RenderData()
		{
			GotoXY(1, 1);
			printf("Player's life : %d\t Score : %d", gamemanager.life, gamemanager.score);
		}

		void RenderGameOver(int x, int y)
		{
				GotoXY(x, y);
				printf("=====================");
				GotoXY(x, y + 1);
				printf("==                 ==");
				GotoXY(x, y + 2);
				printf("== G A M E O V E R ==");
				GotoXY(x, y + 3);
				printf("==                 ==");
				GotoXY(x, y + 4);
				printf("=====================");
				GotoXY(x, y + 5);
				printf("==   SCORE : %3d   ==\n", gamemanager.score);
		}

		void SpeedUp()
		{ 
				obstacle.speed += 0.001f;
				heart.speed += 0.001f;
				scene.cloud.speed += 0.001f;
				scene.mountain.speed += 0.001f;
				scene.airplane.speed += 0.001f;
		}


		struct Obstacle
		{
			int x, y;
			float speed;
			bool isactive;
		}obstacle;

		void initObstacle()
		{
			obstacle.x = 40;
			obstacle.y = 18;
			obstacle.speed = 1.5f;
			obstacle.isactive = false;
		}

		void initObstacle2()
		{
			obstacle.x = 40;
			obstacle.y = 18;
			obstacle.speed = 1.5f;
			obstacle.isactive = false;
		}

		void ActiveObstacle()
		{
			if (obstacle.isactive == false)
			{
				obstacle.x = 40;
				obstacle.isactive = true;
			}
		}

		void ActiveObstacle2()
		{
			if (obstacle.isactive == false)
			{
				obstacle.x = 40;
				obstacle.isactive = true;
			}
		}

		void RenderObstacle() {  //오브젝트의 형태
			if (obstacle.isactive == true)
			{
					GotoXY(obstacle.x, obstacle.y);
					printf("  \033[31m▲\033[30m  ");
					GotoXY(obstacle.x, obstacle.y + 1);
					printf("  ■  ");
					GotoXY(obstacle.x, obstacle.y + 2);
					printf("  ■  ");
					GotoXY(obstacle.x, obstacle.y + 3);
					printf("\033[32m-----\033[30m");
			}
		}

		void RenderObstacle2()
		{
			GotoXY(obstacle.x, obstacle.y);
			printf("\033[31m◀\033[30m");
		}

		struct Heart
		{
			int x, y;
			float speed;
			bool isactive;
		}heart;

		void initHeart()
		{
			heart.x = 0;
			heart.y = 0;
			heart.speed = 1.0f;
			heart.isactive = false;
		}

		void ActiveHeart(int x, int y)
		{
			if (heart.isactive == false)
			{
				heart.isactive = true;
				heart.x = x;
				heart.y = y;
			}
		}

		void RenderHeart()
		{
			if (heart.isactive == true)
			{
				GotoXY(heart.x, heart.y);
				printf("\033[31m♥\033[30m");
			}
		}

		void MoveHeart()
		{
			if (heart.isactive == true)
			{
				heart.x -= heart.speed;
				if (heart.x <= 1)
				{
					heart.isactive = false;
				}
			}
		}
	};
}