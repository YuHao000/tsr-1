// cvter.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include <string>
#include "loader.hpp"
#include "CFilter.hpp"
#include "CDetect.hpp"

void Pic2RgbProc(int argc, char* argv[])
{
    tsr::CBitmap    bitmap;
    tsr::CPicLoader loader(argv[2], bitmap);
    loader.Load();
    bitmap.Save(argv[3]);
}

void Pic2HsvProc(int argc, char* argv[])
{
    tsr::CBitmap    bitmap;
    tsr::CPicLoader loader(argv[2], bitmap);
    loader.Load();
    bitmap.Rgb2Hsv();
    bitmap.SaveAsHsv(argv[3]);
}

void PicFilterRedProc(int argc, char* argv[])
{
    tsr::CBitmap    bitmap;
    tsr::CPicLoader loader(argv[2], bitmap);
    loader.Load();

    bitmap.Rgb2Hsv();
    tsr::CFilter filter(bitmap);
    tsr::CBitmap dst;

    filter.FilterRed(dst);
    
    loader.Set(argv[3], dst);
    loader.SaveAsJpg(argv[3]);
}

void PicFilterGreenProc(int argc, char* argv[])
{
    tsr::CBitmap    bitmap;
    tsr::CPicLoader loader(argv[2], bitmap);
    loader.Load();

    bitmap.Rgb2Hsv();
    tsr::CFilter filter(bitmap);
    tsr::CBitmap dst;

    filter.FilterGreen(dst);

    loader.Set(argv[3], dst);
    loader.SaveAsJpg(argv[3]);
}

void PicFilterColorProc(int argc, char* argv[])
{
    tsr::CBitmap    bitmap;
    tsr::CPicLoader loader(argv[2], bitmap);
    loader.Load();

    bitmap.Rgb2Hsv();
    tsr::CFilter filter(bitmap);
    tsr::CBitmap dst;

    filter.FilterGreenAndRed(dst);

    tsr::CDetect detect(dst, bitmap);
    detect.FindRects();
    detect.RemoveRects(10); //移除小的矩形
    detect.MergeRects();
    detect.FindLights();
    detect.MarkRects();

    loader.Set(argv[3], dst);
    loader.SaveAsJpg(argv[3]);

    std::string name = argv[3];
    name += ".edge.jpg";
    loader.Set(argv[3], dst);
    loader.SaveAsJpg(name.c_str());

    std::vector<tsr::CPointSet>& pss = detect.GetPss();

    //int i = 0;
    std::string tmp;
    for (auto& ps : pss) {
        tsr::CBitmap bmp;
        bitmap.Cut(ps.GetRect(), bmp);
        loader.Set((char *)"..", bmp);
        tmp = argv[3] + std::string(".") + std::to_string(ps.GetRect().GetX()) +
            "." + std::to_string(ps.GetRect().GetY()) + "." + std::to_string(ps.GetType());
        name = tmp + ".jpg";
        loader.SaveAsJpg(name.c_str());
        
        tsr::CBitmap edge;
        bmp.Canny(edge);
        name = tmp + ".edge.jpg";
        loader.Set((char *)"..", edge);
        loader.SaveAsJpg(name.c_str());
    }

}

void PicGaussBlurProc(int argc, char* argv[])
{
    tsr::CBitmap    bitmap;
    tsr::CPicLoader loader(argv[2], bitmap);
    loader.Load();

    bitmap.Rgb2Hsv();
    tsr::CFilter filter(bitmap);
    tsr::CBitmap dst;

    float sigma = atof(argv[4]);
    bitmap.GaussBlur(sigma, dst);

    loader.Set(argv[3], dst);
    loader.SaveAsJpg(argv[3]);
}

void PicSobelProc(int argc, char* argv[])
{
    tsr::CBitmap    bitmap;
    tsr::CPicLoader loader(argv[2], bitmap);
    loader.Load();

    bitmap.Rgb2Hsv();
    tsr::CFilter filter(bitmap);
    tsr::CBitmap dst;

    bitmap.Sobel(dst);

    loader.Set(argv[3], dst);
    loader.SaveAsJpg(argv[3]);
}

void Rgb2HsvProc(int argc, char* argv[])
{
    int  r = atoi(argv[2]);
    int  g = atoi(argv[3]);
    int  b = atoi(argv[4]);

    tsr::CColor color(r, g, b);
    color.Rgb2Hsv();

    std::cout << "HSV1:" << color.GetH() << " " << color.GetS() << " " << color.GetV() << std::endl;
    std::cout << "HSV2:" << color.GetHi() << " " << color.GetSi() << " " << color.GetVi() << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        std::cout << "Invalid parameter!" << std::endl;
        return -1;
    }

    std::cout << "Input file:" << argv[2] << std::endl;
    std::cout << "Output file:" << argv[3] << std::endl;

    if (0 == strcmp(argv[1], "pic2rgb")) {
        Pic2RgbProc(argc, argv);
    }
    else if (0 == strcmp(argv[1], "pic2hsv")) {
        Pic2HsvProc(argc, argv);
    }
    else if (0 == strcmp(argv[1], "fltred")) {
        PicFilterRedProc(argc, argv);
    }
    else if (0 == strcmp(argv[1], "fltcolor")) {
        PicFilterColorProc(argc, argv);
    }
    else if (0 == strcmp(argv[1], "fltgreen")) {
        PicFilterGreenProc(argc, argv);
    }
    else if (0 == strcmp(argv[1], "rgb2hsv")) {
        Rgb2HsvProc(argc, argv);
    }
    else if (0 == strcmp(argv[1], "gaussblur")) {
        PicGaussBlurProc(argc, argv);
    }
    else if (0 == strcmp(argv[1], "sobel")) {
        PicSobelProc(argc, argv);
    }

	return 0;
}

