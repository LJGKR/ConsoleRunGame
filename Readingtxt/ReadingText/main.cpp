#include <iostream>
#include <fstream>
#include <string>
#include <codecvt>

int main()
{
    std::ifstream infile("C:\\�����ذ�ɷ�\\�����ذ�ɷ�.txt", std::ios::in | std::ios::binary);
    if (infile)
    {
        // ���� �б�
        std::string line;
        while (std::getline(infile, line))
        {
            std::cout << line << std::endl;
        }
        infile.close();
    }
    else
    {
        std::cerr << "������ �� �� �����ϴ�." << std::endl;
    }
}