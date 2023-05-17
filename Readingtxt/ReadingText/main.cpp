#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
    std::string filename = "C:\\�����ذ�ɷ�\\�����ذ�ɷ�.txt";
    std::ifstream infile(filename);
    if (infile)
    {
        std::vector<std::string> names;
        std::vector<int> scores;
        std::vector<char> grades;

        std::string line;
        while (std::getline(infile, line))
        {
            std::cout << "������ �ִ� �ؽ�Ʈ : " << line << std::endl;
        }
        infile.close();

        std::cout << "�̸�, ����, ������ �Է��ϼ���. �Է��� �����Ϸ��� stop�� �Է��ϼ���." << std::endl;
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
                outfile << "�� �̸��� " << names[i] << "�̰� �̹��б� ������ " << scores[i] << "���̰� ������ " << grades[i] << "�� �޾ҽ��ϴ�.\n";
            }
            outfile.close();
            std::cout << "������ ���������� �����Ǿ����ϴ�." << std::endl;
        }
        else
        {
            std::cerr << "������ �� �� �����ϴ�." << std::endl;
        }
    }
    else
    {
        std::cerr << "������ �� �� �����ϴ�." << std::endl;
    }

    return 0;
}
