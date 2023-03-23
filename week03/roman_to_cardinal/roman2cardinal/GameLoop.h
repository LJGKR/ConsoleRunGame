#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unordered_map>
#include <Windows.h>
#include <thread>
#include <string>

using namespace std;
bool isGameRunning = false;

void ExitFunction() {
	while (1) {
		if (GetAsyncKeyState(VK_ESCAPE)) {
			cout << endl;
			cout << "����Ű�� �Է��ϼ̽��ϴ�." << endl;
			exit(0);
		}
	}
}

char r[10] = { 'I','V','X','L','C','D','M' };

int romanToInt(string s) {

	unordered_map<char, int> roman = {
		{'I', 1},
		{'V', 5},
		{'X', 10},
		{'L', 50},
		{'C', 100},
		{'D', 500},
		{'M', 1000}
	};

	int result = 0;
	int prev = 0;

	for (char c : s) {
		int current = roman[c];

		if (current > prev) {
			result += current - 2 * prev;
		}
		else {
			result += current;
		}

		prev = current;
	}

	return result;
}

namespace Problem_solving
{

	void Initialize()
	{

	}
	void Input()
	{

	}

	void Update()
	{
		thread t(ExitFunction);

		int i;
		string roma;
		bool isFound = false;

		while (true)
		{
			cout << "�θ� ���ڸ� �Է��ϼ��� : ";
			cin >> roma;

			i = romanToInt(roma);
			for (int i = 0; i < roma.length(); i++) {
				for (int k = 0; k < 7; k++) {
					if (roma[i] == r[k]) {
						isFound = true;
						break;
					}
				}
			}

			if (isFound) {
				cout << "��ȯ �� ���� : " << i << endl;
			}
			else {
				cout << "���ڸ� �ٽ� �Է����ּ���" << endl;
			}
		}
	}

	void Render()
	{

	}
	void Release()
	{

	}
	class GameLoop
	{
	public:


		GameLoop() {}
		~GameLoop() {}

		void Run()
		{
			isGameRunning = true;

			Initialize();

			while (isGameRunning)
			{
				Input();
				Update();
				Render();

			}
			Release();
		}
	};
}
