// cvter.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include <string>
#include "loader.hpp"

void Pic2RgbProc(int argc, char* argv[])
{
    tsr::CBitmap    bitmap;
    tsr::CPicLoader loader(argv[2], bitmap);
    loader.load();
    bitmap.Save(argv[3]);
}

void Pic2HsvProc(int argc, char* argv[])
{
    tsr::CBitmap    bitmap;
    tsr::CPicLoader loader(argv[2], bitmap);
    loader.load();
    bitmap.Rgb2Hsv();
    bitmap.SaveAsHsv(argv[3]);
}

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        std::cout << "Invalid parameter!" << std::endl;
        return -1;
    }

    if (0 == strcmp(argv[1], "pic2rgb")) {
        Pic2RgbProc(argc, argv);
    }
    else if (0 == strcmp(argv[1], "pic2hsv")) {
        Pic2HsvProc(argc, argv);
    }

	return 0;
}

