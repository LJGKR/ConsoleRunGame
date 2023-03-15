#include <iostream>
#include <unordered_map>
#include<stdio.h>
#include<conio.h>

using namespace std;
bool isGameRunning = false;

namespace Problem_solving
{
	void exitg() {
		isGameRunning = false;
	}
	int romanToCardinal(string romanNumeral) {
		unordered_map<char, int> romanValues = {
			{'I', 1},
			{'V', 5},
			{'X', 10},
			{'L', 50},
			{'C', 100},
			{'D', 500},
			{'M', 1000}
		};

		int result = 0;
		int prevValue = 0;

		for (int i = romanNumeral.length() - 1; i >= 0; i--) {
			char currentChar = romanNumeral[i];
			int currentValue = romanValues[currentChar];

			if (currentValue < prevValue) {
				result -= currentValue;
			}
			else {
				result += currentValue;
			}

			prevValue = currentValue;
		}

		return result;
	}
	void Initialize()
	{

	}
	void Input()
	{
		try
		{
			char a;
			string romanNumeral;
			cout << "���ڸ� �Է��ϼ��� : ";

			if (_kbhit())// Ű�Է��� ������ TRUE ������ FALSE ��ȯ

			{

				if (!(a = _getch()))// �Էµ� Ű�� ����ڸ� getch()�� FALSE ��ȯ

					a = _getch();


				if (a == 27)// �Էµ� Ű�� ESC�̸� TRUE
					exitg();



			}
			cin >> romanNumeral;
			int cardinal = romanToCardinal(romanNumeral);

			cout << "�Է��� ���� : " << romanNumeral << endl;
			cout << "��ȯ�� ���� : " << cardinal << endl;
		}
		catch (const std::exception&)
		{
			cout << "���ڸ� �߸� �Է��ϼ̽��ϴ�.";
		}
	}

	void Update()
	{
			
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