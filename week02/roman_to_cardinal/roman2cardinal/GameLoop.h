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
			cout << "문자를 입력하세요 : ";

			if (_kbhit())// 키입력이 있으면 TRUE 없으면 FALSE 반환

			{

				if (!(a = _getch()))// 입력된 키가 제어문자면 getch()는 FALSE 반환

					a = _getch();


				if (a == 27)// 입력된 키가 ESC이면 TRUE
					exitg();



			}
			cin >> romanNumeral;
			int cardinal = romanToCardinal(romanNumeral);

			cout << "입력한 문자 : " << romanNumeral << endl;
			cout << "변환된 숫자 : " << cardinal << endl;
		}
		catch (const std::exception&)
		{
			cout << "문자를 잘못 입력하셨습니다.";
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