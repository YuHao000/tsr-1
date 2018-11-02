// cvter.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include "loader.hpp"

int main(int argc, char* argv[])
{
	if (argc < 4)
	{
		std::cout << "Usage: cvter -d jpg txt" << std::endl;
		std::cout << "Usage: cvter -e txt jpg" << std::endl;
		return -1;
	}

	if (2 != strlen(argv[1]))
	{
		std::cout << "Usage: cvter -d jpg txt" << std::endl;
		std::cout << "Usage: cvter -e txt jpg" << std::endl;
		return -1;
	}

	if ('-' != argv[1][0])
	{
		std::cout << "Usage: cvter -d jpg txt" << std::endl;
		std::cout << "Usage: cvter -e txt jpg" << std::endl;
		return -1;
	}

	return 0;
}

