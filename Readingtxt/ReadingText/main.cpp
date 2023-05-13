#include <iostream>
#include <fstream>
#include <string>
#include <codecvt>

int main()
{
    std::ifstream infile("C:\\문제해결능력\\문제해결능력.txt", std::ios::in | std::ios::binary);
    if (infile)
    {
        // 파일 읽기
        std::string line;
        while (std::getline(infile, line))
        {
            std::cout << line << std::endl;
        }
        infile.close();
    }
    else
    {
        std::cerr << "파일을 열 수 없습니다." << std::endl;
    }
}