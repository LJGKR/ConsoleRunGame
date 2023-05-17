#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
    std::string filename = "C:\\문제해결능력\\문제해결능력.txt";
    std::ifstream infile(filename);
    if (infile)
    {
        std::vector<std::string> names;
        std::vector<int> scores;
        std::vector<char> grades;

        std::string line;
        while (std::getline(infile, line))
        {
            std::cout << "기존에 있던 텍스트 : " << line << std::endl;
        }
        infile.close();

        std::cout << "이름, 점수, 성적을 입력하세요. 입력을 종료하려면 stop을 입력하세요." << std::endl;
        while (true)
        {
            std::string name;
            int score;
            char grade;
            std::cin >> name;
            if (name == "stop")
                break;
            std::cin >> score >> grade;
            names.push_back(name);
            scores.push_back(score);
            grades.push_back(grade);
        }

        std::ofstream outfile(filename, std::ios::app); 
        if (outfile)
        {
            for (size_t i = 0; i < names.size(); ++i)
            {
                outfile << "내 이름은 " << names[i] << "이고 이번학기 점수는 " << scores[i] << "점이고 성적은 " << grades[i] << "를 받았습니다.\n";
            }
            outfile.close();
            std::cout << "파일이 성공적으로 수정되었습니다." << std::endl;
        }
        else
        {
            std::cerr << "파일을 열 수 없습니다." << std::endl;
        }
    }
    else
    {
        std::cerr << "파일을 열 수 없습니다." << std::endl;
    }

    return 0;
}
